#include "crypto/padding.h"
#include <string>
#include <cstring>
#include <string_view>
#include <memory>
#include <stdexcept>
#include <glog/logging.h>

namespace crypto {
std::string Padding(const std::string_view msg,
                    int block_size, PaddingType style) {
  if (style == PaddingType::PKCS7) {
    return PKCS7Padding(msg, block_size);
  } else {
    throw std::invalid_argument("Unsupported padding type.");
  }
}
std::string Padding(const std::string& msg, int block_size, PaddingType style) {
  std::string_view msg_sv(msg.data(), msg.length());
  return Padding(msg_sv, block_size, style);
}

std::string PKCS7Padding(const std::string_view msg, int block_size) {
  size_t data_len = msg.size();
  int padding_len = block_size - (data_len % block_size);
  auto buf = std::make_unique<char[]>(padding_len);
  memset(buf.get(), static_cast<int8_t>(padding_len), padding_len);
  std::string padded_data;
  padded_data.reserve(data_len);
  padded_data.append(msg);
  padded_data.append(buf.get(), padding_len);
  return padded_data;
}
std::string PKCS7Padding(const std::string& msg, int block_size) {
  std::string_view msg_sv(msg.data(), msg.length());
  return PKCS7Padding(msg_sv, block_size);
}

std::string UnPadding(const std::string& msg,
                      int block_size, PaddingType style) {
  std::string_view msg_sv(msg.data(), msg.length());
  return UnPadding(msg_sv, block_size, style);
}

std::string UnPadding(const std::string_view msg,
                      int block_size, PaddingType style) {
  if (style == PaddingType::PKCS7) {
    return PKCS7UnPadding(msg, block_size);
  } else {
    throw std::invalid_argument("Unsupported padding type.");
  }
}

std::string PKCS7UnPadding(const std::string& msg, int block_size) {
  std::string_view msg_sv(msg.data(), msg.length());
  return PKCS7UnPadding(msg_sv, block_size);
}

std::string PKCS7UnPadding(const std::string_view msg, int block_size) {
  if (msg.empty()) {
    throw std::invalid_argument("Data is empty.");
  }
  size_t data_len = msg.length();
  int padding_size = static_cast<int>(msg[data_len-1]);
  LOG(INFO) << "padding_size: " << padding_size;
  if (padding_size > block_size || padding_size == 0) {
    throw std::invalid_argument("Invalid padding size.");
  }
  for (size_t i = data_len - 1; i >= data_len - padding_size; --i) {
    if (msg[i] != padding_size) {
      throw std::invalid_argument("Invalid padding.");
    }
  }
  std::string unpadding_data(msg.data(), data_len-padding_size);
  return unpadding_data;
}
}  // namespace crypto