// https://en.wikipedia.org/wiki/Merge_sort

#pragma once

#include <functional>
#include <vector>

namespace {

template <typename T, class Compare>
void _merge(std::vector<T>& v, std::vector<T>& helper, std::size_t begin,
            std::size_t mid, std::size_t end, const Compare& cmp) {
  for (auto i = begin; i < end; ++i) {
    helper.at(i) = v.at(i);
  }
  std::size_t left = begin, right = mid;
  for (auto i = begin; i < end; ++i) {
    if (left < mid &&
        (right >= end || !cmp(helper.at(right), helper.at(left)))) {
      v.at(i) = helper.at(left);
      ++left;
    } else {
      v.at(i) = helper.at(right);
      ++right;
    }
  }
}

template <typename T, class Compare>
void _m_sort(std::vector<T>& v, std::vector<T>& helper, std::size_t begin,
             std::size_t end, const Compare& cmp) {
  if (begin + 1 >= end) return;
  std::size_t mid = begin + (end - begin) / 2;
  _m_sort(v, helper, begin, mid, cmp);
  _m_sort(v, helper, mid, end, cmp);
  _merge(v, helper, begin, mid, end, cmp);
}

// less rather than less_equal
template <typename T, class Compare = std::less<>>
void merge_sort(std::vector<T>& v, const Compare& cmp = std::less<>()) {
  std::vector<T> helper(v);
  _m_sort(v, helper, 0, v.size(), cmp);
}

}  // namespace
