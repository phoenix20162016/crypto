#ifndef CRYPTO_AES_UTIL_H_
#define CRYPTO_AES_UTIL_H_
#include <openssl/aes.h>
#include <string>
#include <vector>
#include <string_view>
namespace crypto {
std::string aes_cbc_encrypt(const std::string& plain_text, const std::string& key);
std::string aes_cbc_decrypt(const std::string& cipher_text, const std::string& key);
void InitKeyIv(const std::string& key_iv, unsigned char* key, unsigned char* iv);
std::string GenerateKeyIv(int key_bit_len = 128);

uint8_t FromHex(char ch);

}  // namespace crypto
#endif  // CRYPTO_AES_UTIL_H_
