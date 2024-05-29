#ifndef UTIL_UTIL_H_
#define UTIL_UTIL_H_
#include <vector>
#include <string>
namespace crypto {
void str_split(const std::string& str,
               std::vector<std::string>* v,
               char delimiter);
std::string GenerateUUID(bool remove_sep = false);
}  // namespace crypto
#endif  // UTIL_UTIL_H_
