#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <memory>
#include "crypto/rsa_util.h"
#include "crypto/aes_util.h"
#include "util/util.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <glog/logging.h>

std::string ReadData(const std::string& file_path) {
  std::ifstream f_in_stream(file_path);
  std::string file_contents((std::istreambuf_iterator<char>(f_in_stream)),
                        std::istreambuf_iterator<char>());
  if (file_contents.empty()) {
    std::cout << "please check, path: " << file_path << " \n";
    return std::string();
  }
  return file_contents;

}

int main() {
  // std::string prv_key_path = "cert/prive_key.pem";
  // std::string pub_key_path = "cert/pub_key.pem";
  // std::string origin_data_path = "data/data.csv";
  // std::string cipher_text_path = "data/enc_out.bin";
  // auto plain_text = ReadData(origin_data_path);
  // if (plain_text.empty()) {
  //   std::cout << "file: " << origin_data_path << " is empty\n";
  //   return -1;
  // }
  // auto cipher_text = crypto::Public_RsaEncrypt(plain_text, pub_key_path);
  // std::string enc_data_path = "data/enc_data.bin";
  // std::ofstream fout(enc_data_path, std::ios::binary);
  // fout.write(cipher_text.c_str(), cipher_text.size());
  // std::cout << "cipher_text len: " << cipher_text.size() << "\n";
  // auto decrpted_data = crypto::Private_RsaDecrypt(cipher_text, prv_key_path);
  // std::cout << decrpted_data;

  // aes cbc encrypt test
  std::string szBuffer = "hello lyshark";
  std::string key_iv = crypto::GenerateKeyIv();
  key_iv = "6e698f3d59ab81606d66b292c29cd8a9|0071b3580b41ca429a5674270f988f3e";
  LOG(INFO) << "key_iv: " << key_iv << "\n";
  // AES加密
  auto cipher_text = crypto::aes_cbc_encrypt(szBuffer, key_iv);
  // AES解密
  // std::string file_name{"result.bin"};
  // struct stat file_info;
  // ::stat(file_name.c_str(), &file_info);
  // size_t file_size = file_info.st_size;
  // std::ifstream fin(file_name, std::ios::binary  | std::ios::in);
  // auto buf = std::make_unique<char[]>(file_size);
  // fin.read(buf.get(), file_size);
  // std::string cipher_text(buf.get(), file_size);
  auto plain_text = crypto::aes_cbc_decrypt(cipher_text, key_iv);
  LOG(INFO) << "解密内容: " << plain_text;
  return 0;
}
