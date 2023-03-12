// https://en.wikipedia.org/wiki/Binary_search_algorithm

#pragma once

#include <vector>

template <typename T>
signed long long binary_search(const std::vector<T> &v, T target) {
  std::size_t begin = 0, end = v.size(), mid;  // exclude "end"
  while (begin < end) {
    mid = begin + (end - begin) / 2;
    if (v[mid] == target) {
      return mid;  // NOLINT
    }
    if (v[mid] > target) {
      end = mid;
    } else {
      begin = mid + 1;
    }
  }
  return -1;
}

template <typename T>
signed long long lower_bound(const std::vector<T> &v, T target) {
  std::size_t begin = 0, end = v.size(), mid;  // exclude "end"
  while (begin < end) {
    mid = begin + (end - begin) / 2;
    if (v[mid] >= target) {
      end = mid;
    } else {
      begin = mid + 1;
    }
  }
  if (begin == v.size() || v[begin] != target) {
    return -1;
  }
  return begin;  // NOLINT
}

template <typename T>
signed long long upper_bound(const std::vector<T> &v, T target) {
  std::size_t begin = 0, end = v.size(), mid;  // exclude "end"
  while (begin < end) {
    mid = begin + (end - begin) / 2;
    if (v[mid] > target) {
      end = mid;
    } else {
      begin = mid + 1;
    }
  }
  if (begin == 0 || v[begin - 1] != target) {
    return -1;
  }
  return begin - 1;  // NOLINT
}
