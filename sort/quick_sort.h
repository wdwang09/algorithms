// https://en.wikipedia.org/wiki/Quicksort

#pragma once

#include <functional>
#include <vector>

namespace {

template <typename T, class Compare>
std::size_t _q_partition(std::vector<T>& v, std::size_t begin, std::size_t end,
                         const Compare& cmp) {
  std::size_t low = begin, high = end - 1;
  auto pivot = v[high];
  do {
    while (low < high && cmp(v[low], pivot)) ++low;
    if (low < high) {
      v[high] = v[low];
      --high;
    }
    while (low < high && cmp(pivot, v[high])) --high;
    if (low < high) {
      v[low] = v[high];
      ++low;
    }
  } while (low < high);
  v[low] = pivot;
  return low;
}

template <typename T, class Compare>
void _q_sort(std::vector<T>& v, std::size_t begin, std::size_t end,
             const Compare& cmp) {
  if (begin >= end) return;
  std::size_t idx = _q_partition(v, begin, end, cmp);
  _q_sort(v, begin, idx, cmp);
  _q_sort(v, idx + 1, end, cmp);
}

template <typename T, class Compare = std::less<>>
void quick_sort(std::vector<T>& v, const Compare& cmp = std::less<>()) {
  _q_sort(v, 0, v.size(), cmp);
}

}  // namespace

namespace quick_sort_2 {

template <typename T, class Compare>
std::size_t _q_partition(std::vector<T>& v, std::size_t begin, std::size_t end,
                         const Compare& cmp) {
  std::size_t low = begin;
  for (auto high = begin; high < end - 1; ++high) {
    if (cmp(v[high], v[end - 1])) {
      std::swap(v[low], v[high]);
      ++low;
    }
  }
  std::swap(v[low], v[end - 1]);
  return low;
}

template <typename T, class Compare>
void _q_sort(std::vector<T>& v, std::size_t begin, std::size_t end,
             const Compare& cmp) {
  if (begin >= end) return;
  std::size_t idx = _q_partition(v, begin, end, cmp);
  _q_sort(v, begin, idx, cmp);
  _q_sort(v, idx + 1, end, cmp);
}

template <typename T, class Compare = std::less<>>
void quick_sort(std::vector<T>& v, const Compare& cmp = std::less<>()) {
  _q_sort(v, 0, v.size(), cmp);
}

}  // namespace quick_sort_2
