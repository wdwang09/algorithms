// https://en.wikipedia.org/wiki/Quicksort

#pragma once

#include <vector>

using std::size_t;
using std::vector;

namespace {

template <typename T>
void q_sort(vector<T> &v, size_t begin, size_t end);

template <typename T>
size_t q_partition(vector<T> &v, size_t begin, size_t end);

template <typename T>
void quick_sort(vector<T> &v) {
  q_sort(v, 0, v.size());
}

template <typename T>
void q_sort(vector<T> &v, size_t begin, size_t end) {
  if (begin >= end) return;
  size_t idx = q_partition(v, begin, end);
  q_sort(v, begin, idx);
  q_sort(v, idx + 1, end);
}

template <typename T>
size_t q_partition(vector<T> &v, size_t begin, size_t end) {
  size_t low = begin, high = end - 1;
  auto pivot = v[high];
  do {
    while (low < high && v[low] <= pivot) ++low;
    if (low < high) {
      v[high] = v[low];
      --high;
    }
    while (low < high && v[high] >= pivot) --high;
    if (low < high) {
      v[low] = v[high];
      ++low;
    }
  } while (low < high);
  v[low] = pivot;
  return low;
}

}  // namespace

namespace quick_sort_2 {

template <typename T>
void q_sort(vector<T> &v, size_t begin, size_t end);

template <typename T>
size_t q_partition(vector<T> &v, size_t begin, size_t end);

template <typename T>
void quick_sort(vector<T> &v) {
  q_sort(v, 0, v.size());
}

template <typename T>
void q_sort(vector<T> &v, size_t begin, size_t end) {
  if (begin >= end) return;
  size_t idx = q_partition(v, begin, end);
  q_sort(v, begin, idx);
  q_sort(v, idx + 1, end);
}

template <typename T>
size_t q_partition(vector<T> &v, size_t begin, size_t end) {
  size_t low = begin;
  for (size_t high = begin; high < end - 1; ++high) {
    if (v[high] <= v[end - 1]) {
      std::swap(v[low], v[high]);
      ++low;
    }
  }
  std::swap(v[low], v[end - 1]);
  return low;
}

}  // namespace quick_sort_2
