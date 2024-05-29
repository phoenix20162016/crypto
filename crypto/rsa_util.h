#ifndef CRYPTO_RSA_UTIL_H_
#define CRYPTO_RSA_UTIL_H_
#include <string>
namespace crypto {
std::string Private_RsaDecrypt(const std::string& cipher_text,
                               const std::string& prv_key_path);
std::string Public_RsaEncrypt(const std::string& plain_text,
                              const std::string& pub_key_path);
}  // namespace crypto
#endif  // CRYPTO_RSA_UTIL_H_
