#pragma once

#include <sstream>
#include <string>

namespace common {

template <class RandomIt>
std::string join(const std::string& s, RandomIt first, RandomIt last) {
  std::stringstream res;
  for (auto it = first; it != last; ++it) {
    if (it != first) {
      res << s;
    }
    res << *it;
  }
  return res.str();
}

}  // namespace common
