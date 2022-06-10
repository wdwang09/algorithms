// https://en.cppreference.com/w/cpp/container/priority_queue

#pragma once

#include <array>
#include <functional>
#include <vector>

template <class T, class Compare = std::less<>>
class priority_queue {
 public:
  priority_queue() = default;

  const T& top() const { return heap_.at(0); }

  void push(const T& value) {
    std::size_t idx = size();
    heap_.push_back(value);
    while (idx > 0) {
      std::size_t parent_idx = (idx - 1) / 2;
      if (!cmp_(heap_.at(idx), heap_.at(parent_idx))) {
        std::swap(heap_.at(idx), heap_.at(parent_idx));
        idx = parent_idx;
      } else {
        break;
      }
    }
  }

  void pop() {
    std::swap(heap_.at(0), heap_.back());
    heap_.pop_back();
    if (size() == 0) {
      return;
    }
    std::size_t idx = 0;
    while (idx < size() / 2) {
      std::size_t child_idx = idx * 2 + 1;
      if (child_idx + 1 < size() &&
          cmp_(heap_.at(child_idx), heap_.at(child_idx + 1))) {
        ++child_idx;
      }
      if (cmp_(heap_.at(idx), heap_.at(child_idx))) {
        std::swap(heap_.at(idx), heap_.at(child_idx));
        idx = child_idx;
      } else {
        break;
      }
    }
  }

  std::size_t size() const { return heap_.size(); }

  bool empty() const { return heap_.empty(); }

 private:
  std::vector<T> heap_;  // Start from 0, i -> 2i+1 | 2i+2;
  Compare cmp_;
};
