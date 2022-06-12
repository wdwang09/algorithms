#pragma once

#include <algorithm>
#include <iostream>
#include <random>
#include <stdexcept>

#include "common.h"

std::vector<int> random_int_vector(int upper_bound = 100) {
  std::random_device r;
  std::default_random_engine e(r());
  std::uniform_int_distribution<int> uniform_dist(0, upper_bound);
  std::vector<int> v(uniform_dist(e));
  std::generate(v.begin(), v.end(),
                [&uniform_dist, &e] { return uniform_dist(e); });
  return v;
}

template <typename T>
void assert_vector_eq(const std::vector<T>& a, const std::vector<T>& b) {
  if (a == b) {
    return;
  }
  std::cout << "=== FAIL EQ ===" << std::endl;
  std::cout << common::join(" ", a.begin(), a.end()) << std::endl;
  std::cout << common::join(" ", b.begin(), b.end()) << std::endl;
  std::cout << "===============" << std::endl;
  throw std::runtime_error("NOT EQUAL");
}
