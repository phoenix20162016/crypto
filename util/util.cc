#include "util/util.h"
#include <sstream>
#include <cstring>
#include <random>
#include <array>
#include "uuid.h"

namespace crypto {
void str_split(const std::string& str,
               std::vector<std::string>* v,
               char delimiter) {
  std::stringstream ss(str);
  while (ss.good()) {
    std::string substr;
    std::getline(ss, substr, delimiter);
    v->push_back(substr);
  }
}
std::string GenerateUUID(bool remove_sep) {
  std::random_device rd;
  auto seed_data = std::array<int, std::mt19937::state_size> {};
  std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
  std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
  std::mt19937 generator(seq);
  uuids::uuid_random_generator gen{generator};
  const uuids::uuid id = gen();
  auto uuid_str = uuids::to_string(id);
  if (remove_sep) {
    uuid_str.erase(
      std::remove_if(
        uuid_str.begin(), uuid_str.end(), [](char ch) {return ch == '-';}),
      uuid_str.end());
  }
  return uuid_str;
}
}  // namespace crypto