// https://en.wikipedia.org/wiki/Insertion_sort

#pragma once

#include <functional>
#include <vector>

template <typename T, class Compare = std::less<>>
void insertion_sort(std::vector<T>& v, const Compare& cmp = std::less<>()) {
  for (std::size_t i = 1; i < v.size(); ++i) {
    T current_num = v[i];
    std::size_t j = i - 1;
    bool insert_to_zero = false;  // j is unsigned
    while (cmp(current_num, v[j])) {
      v[j + 1] = v[j];
      if (j == 0) {
        insert_to_zero = true;
        break;
      }
      --j;
    }
    if (insert_to_zero) {
      v[0] = current_num;
    } else {
      v[j + 1] = current_num;
    }
  }
}
