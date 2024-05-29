#ifndef CRYPTO_PADDING_H_
#define CRYPTO_PADDING_H_
#include <string>

namespace crypto {
enum class PaddingType{
  ZeroPadding = 0,
  PKCS7,
  ISO7816,
  X923
};
std::string Padding(const std::string& msg,
                    int block_size,
                    PaddingType style = PaddingType::PKCS7);
std::string Padding(const std::string_view msg,
                    int block_size,
                    PaddingType style = PaddingType::PKCS7);
std::string PKCS7Padding(const std::string& msg,
                         int block_size);
std::string PKCS7Padding(const std::string_view msg,
                         int block_size);

std::string UnPadding(const std::string& msg,
                      int block_size,
                      PaddingType style = PaddingType::PKCS7);
std::string UnPadding(const std::string_view msg,
                      int block_size,
                      PaddingType style = PaddingType::PKCS7);
std::string PKCS7UnPadding(const std::string& msg,
                           int block_size);
std::string PKCS7UnPadding(const std::string_view msg,
                           int block_size);
}  // namespace crypto
#endif  // CRYPTO_PADDING_H_
