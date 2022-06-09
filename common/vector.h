#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>

std::vector<int> random_int_vector() {
  std::random_device r;
  std::default_random_engine e(r());
  std::uniform_int_distribution<int> uniform_dist(0, 100);
  std::vector<int> v(uniform_dist(e));
  std::generate(v.begin(), v.end(),
                [&uniform_dist, &e] { return uniform_dist(e); });
  return v;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
  os << '[';
  for (auto it = v.begin(); it != v.end(); ++it) {
    if (it != v.begin()) {
      os << ' ';
    }
    os << *it;
  }
  os << ']';
  return os;
}

template <typename T>
bool test_eq(const std::vector<T>& a, const std::vector<T>& b) {
  if (a == b) {
    return true;
  }
  std::cout << "=== FAIL EQ ===" << std::endl;
  std::cout << a << std::endl;
  std::cout << b << std::endl;
  std::cout << "===============" << std::endl;
  return false;
}
