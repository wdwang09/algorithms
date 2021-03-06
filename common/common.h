#pragma once

#include <random>
#include <sstream>
#include <stdexcept>
#include <string>

#define MY_ASSERT(b) common::assert_name_line(b, __FILE__, __LINE__)

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

void assert_name_line(bool b, const std::string& file_name, int file_line) {
  if (!b) {
    std::stringstream ss;
    ss << "Assertion with False: " << file_name << " " << file_line;
    throw std::runtime_error(ss.str());
  }
}

int randint(int min_included, int max_included) {
  std::random_device r;
  std::default_random_engine e(r());
  std::uniform_int_distribution<int> uniform_dist(min_included, max_included);
  return uniform_dist(e);
}

}  // namespace common
