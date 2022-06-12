// https://en.wikipedia.org/wiki/Disjoint-set_data_structure

#pragma once

#include <vector>

class DisjointSet {  // or Union-Find
 public:
  explicit DisjointSet(unsigned long n) : parent_(n, -1) {}

  bool is_same_group(std::size_t id1, std::size_t id2) {
    return find(id1) == find(id2);
  }

  bool merge(std::size_t id1, std::size_t id2) {  // union is a keyword
    std::size_t p_id1 = find(id1);
    std::size_t p_id2 = find(id2);
    if (p_id1 == p_id2) return false;
    if ((-parent_.at(p_id1)) < (-parent_.at(p_id2))) {
      parent_[p_id2] += parent_[p_id1];
      parent_[p_id1] = p_id2;  // NOLINT
    } else {
      parent_[p_id1] += parent_[p_id2];
      parent_[p_id2] = p_id1;  // NOLINT
    }
    return true;
  }

 private:
  std::size_t find(std::size_t x) {
    // if (parent_.at(x) < 0) return x;
    // parent_[x] = find(parent_[x]);  // NOLINT
    // return parent_[x];

    // `bottom` is original node
    std::size_t bottom = x;
    while (parent_.at(x) >= 0) {
      x = parent_[x];
    }
    // now `x` is the top node
    while (bottom != x) {
      std::size_t current_parent = parent_[bottom];
      parent_[bottom] = x;  // NOLINT
      bottom = current_parent;
    }
    return x;
  }

  std::vector<long long> parent_;
};
