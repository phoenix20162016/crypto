#include "crypto/rsa_util.h"
#include <openssl/err.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/crypto.h>
#include <memory>
#include <iostream>
#include <vector>
#include <cstring>

namespace crypto {
#define RSA_PADDING_TYPE RSA_PKCS1_PADDING
// #define RSA_PADDING_TYPE RSA_PKCS1_OAEP_PADDING
auto rsa_deleter = [](RSA* rsa) {
  if (rsa) {
    RSA_free(rsa);
  }
};
auto file_deleter = [](FILE* file) {
  fclose(file);
};

std::string Private_RsaDecrypt(const std::string& cipher_text,
                               const std::string& prv_key_path) {
  int ret = 0;
  FILE* file_raw = fopen(prv_key_path.c_str(), "r");
  if (file_raw == nullptr) {
    return std::string();
  }

  std::unique_ptr<FILE, decltype(file_deleter)> file(file_raw, file_deleter);
  auto rsa_raw = PEM_read_RSAPrivateKey(file.get(), NULL, NULL, NULL);
  if (rsa_raw == nullptr) {
    ERR_print_errors_fp(stdout);
    return std::string();
  }
  file.reset();
  std::unique_ptr<RSA, decltype(rsa_deleter)> rsa(rsa_raw, rsa_deleter);

  int rsa_size = RSA_size(rsa.get());
  std::cout << "RSA_size : " << rsa_size << "\n";
  auto plaintext_ptr = std::make_unique<unsigned char[]>(rsa_size);
  auto plaintext = plaintext_ptr.get();
  // memset(plaintext, 0, rsa_size);
  std::vector<int> block_info;
  size_t block_num = cipher_text.length() / rsa_size;
  for (size_t i = 0; i < block_num; i++) {
    block_info.push_back(rsa_size);
  }
  size_t rem_len = cipher_text.length() % rsa_size;
  if (rem_len != 0) {
    block_info.push_back(rem_len);
  }
  std::string result;
  result.reserve(rsa_size*block_info.size());
  auto data_ptr = (unsigned char*)cipher_text.c_str();
  size_t offset = 0;
  for (const auto& cipher_len : block_info) {
    auto ptr = data_ptr + offset;
    ret = RSA_private_decrypt(cipher_len, ptr,
                              plaintext, rsa.get(), RSA_PADDING_TYPE);
    if (ret < 0) {
      ERR_print_errors_fp(stdout);
      return std::string();
    }
    std::cout << "ret len: " << ret << "\n";
    offset += cipher_len;
    result.append((char*)plaintext, ret);
  }
  return result;
}

std::string Public_RsaEncrypt(const std::string& plain_text,
                              const std::string& pub_key_path) {
  // char* ciphertext = NULL;
  int ret = 0;

  FILE* file_raw = fopen(pub_key_path.c_str(), "r");
  if (file_raw == nullptr) {
    return std::string();
  }
  std::unique_ptr<FILE, decltype(file_deleter)> file(file_raw, file_deleter);
  RSA* rsa_raw = PEM_read_RSA_PUBKEY(file.get(), NULL, NULL, NULL);
  if (rsa_raw == nullptr) {
    ERR_print_errors_fp(stdout);
    return std::string();
  }
  file.reset();
  std::unique_ptr<RSA, decltype(rsa_deleter)> rsa(rsa_raw, rsa_deleter);
  int cipher_size = RSA_size(rsa.get());
  auto ciphertext_ptr = std::make_unique<unsigned char[]>(cipher_size);
  auto ciphertext = ciphertext_ptr.get();
  if (ciphertext == nullptr) {
    return std::string();
  }
  memset(ciphertext, 0, cipher_size);

  int block_size = 190;
  std::vector<int> block_info;
  int block_num = plain_text.size() / block_size;
  for (int i = 0; i < block_num; i++) {
    block_info.push_back(block_size);
  }
  int rem_size = plain_text.size() % block_size;
  if (rem_size != 0) {
    block_info.push_back(rem_size);
  }
  auto plaintext_buf = (unsigned char*)plain_text.c_str();
  size_t offset{0};
  std::string cipher_data;
  cipher_data.reserve(block_info.size() * cipher_size);
  for (const auto data_len : block_info) {
    auto ptr = plaintext_buf + offset;
    ret = RSA_public_encrypt(data_len, ptr, ciphertext, rsa.get(), RSA_PADDING_TYPE);
    if (ret < 0) {
      ERR_print_errors_fp(stdout);
      return std::string();
    }
    cipher_data.append((char*)ciphertext, ret);
    offset += data_len;
  }
  return cipher_data;
}
}  // namespace crypto