#include "crypto/aes_util.h"
#include <iostream>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/crypto.h>
#include <openssl/pem.h>
#include <glog/logging.h>
#include <cstring>
#include <memory>
#include <array>
#include "util/util.h"
#include "crypto/padding.h"
namespace crypto {
#define BIT_LEN 128
// CBC模式加密
std::string aes_cbc_encrypt(const std::string& plain_text,
                            const std::string& key_iv){
  if (plain_text.empty() || key_iv.empty()) {
    return 0;
  }
  unsigned char iv[AES_BLOCK_SIZE];
  unsigned char key[AES_BLOCK_SIZE];
  InitKeyIv(key_iv, key, iv);
  AES_KEY aes;
  if (AES_set_encrypt_key(key, BIT_LEN, &aes) < 0) {
    return 0;
  }

  auto padded_data = Padding(plain_text, AES_BLOCK_SIZE);
  auto in = reinterpret_cast<const unsigned char*>(padded_data.c_str());
  int len = padded_data.size();
  std::string cipher_text(len, '\0');
  auto out = reinterpret_cast<unsigned char*>(&cipher_text[0]);
  AES_cbc_encrypt(in, out, len, &aes, iv, AES_ENCRYPT);
  return cipher_text;
}

// CBC模式解密
std::string aes_cbc_decrypt(const std::string& cipher_text,
                            const std::string& key_iv) {
  if (cipher_text.empty() || key_iv.empty()) {
    return std::string();
  }
  // 加密的初始化向量
  unsigned char iv[AES_BLOCK_SIZE];
  unsigned char key[AES_BLOCK_SIZE];
  InitKeyIv(key_iv, key, iv);
  AES_KEY aes;
  if (AES_set_decrypt_key(key, BIT_LEN, &aes) < 0) {
    return 0;
  }
  int len = cipher_text.size();
  auto out = std::make_unique<unsigned char[]>(len);
  auto in = reinterpret_cast<const unsigned char*>(cipher_text.c_str());
  AES_cbc_encrypt(in, out.get(), len, &aes, iv, AES_DECRYPT);
  std::string_view msg_sv(reinterpret_cast<char*>(out.get()), len);
  return UnPadding(msg_sv, AES_BLOCK_SIZE);
}

void InitKeyIv(const std::string& key_iv,
               unsigned char* key, unsigned char* iv) {
  std::vector<std::string> info;
  str_split(key_iv, &info, '|');
  auto& key_str = info[0];
  auto& iv_str = info[1];
  VLOG(5) << "key_str: " << key_str << "\n";
  VLOG(5) << "iv_str: " << iv_str << "\n";
  for (int i = 0; i < AES_BLOCK_SIZE; i++) {
    int j = i * 2;
    key[i] = (FromHex(key_str[j]) << 4) & 0xF0 | FromHex(key_str[j+1]) & 0x0F;
    iv[i] = (FromHex(iv_str[j]) << 4) & 0xF0 | FromHex(iv_str[j+1]) & 0x0F;
  }
}

std::string GenerateKeyIv(int key_bit_len) {
  LOG(INFO) << "key_bit_len: " << key_bit_len;
  if (key_bit_len != 128 && key_bit_len != 192 && key_bit_len != 256) {
    LOG(ERROR) << "key bit len must be one of [128, 192, 256]";
    return std::string();
  }
  bool rm_sep{true};
  std::string key = GenerateUUID(rm_sep);
  if (key_bit_len == 192) {
    auto tmp_key = GenerateUUID(rm_sep);
    key.append(tmp_key.data(), tmp_key.size()/2);
  } else if (key_bit_len == 256) {
    auto tmp_key = GenerateUUID(rm_sep);
    key.append(tmp_key);
  }
  std::string iv = GenerateUUID(rm_sep);
  return key + '|' + iv;
}


uint8_t FromHex(char ch) {
  int8_t value;
  if (ch >= '0' && ch <= '9') {
    value = ch - '0';
  } else if (ch >= 'a' && ch <= 'f') {
    value = 10 + ch - 'a';
  } else if (ch >= 'A' && ch <= 'F') {
    value = 10 + ch - 'A';
  } else {
    throw std::invalid_argument("Invalid character in hex string.");
  }
  return value;
}


}  // namespace crypto
