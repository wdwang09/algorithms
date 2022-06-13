// https://en.wikipedia.org/wiki/Heapsort

#pragma once

#include <functional>
#include <vector>

namespace {

template <typename T, class Compare>
void _heap_down(std::vector<T>& v, std::size_t idx, std::size_t heap_size,
                const Compare& cmp) {
  while (idx < heap_size / 2) {
    std::size_t child_idx = idx * 2 + 1;
    if (child_idx + 1 < heap_size &&
        cmp(v.at(child_idx), v.at(child_idx + 1))) {
      ++child_idx;
    }
    if (cmp(v.at(idx), v.at(child_idx))) {
      std::swap(v.at(idx), v.at(child_idx));
      idx = child_idx;
    } else {
      break;
    }
  }
}

template <typename T, class Compare = std::less<>>
void heap_sort(std::vector<T>& v, const Compare& cmp = std::less<>()) {
  if (v.size() <= 1) return;

  // build heap
  std::size_t idx = v.size() / 2;
  while (true) {
    _heap_down(v, idx, v.size(), cmp);
    if (idx == 0) {  // unsigned
      break;
    } else {
      --idx;
    }
  }

  // pop
  idx = v.size() - 1;
  while (true) {
    std::swap(v.at(0), v.at(idx));
    _heap_down(v, 0, idx, cmp);
    if (idx == 0) {  // unsigned
      break;
    } else {
      --idx;
    }
  }
}

}  // namespace
