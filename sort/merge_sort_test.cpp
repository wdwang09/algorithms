#include "merge_sort.h"

#include <functional>
#include <random>
#include <vector>

#include "common.h"
#include "vector.h"

struct Element {
  int to_sort_ = 0;
  int other_el_ = 0;

  Element(int to_sort, int other_el) : to_sort_(to_sort), other_el_(other_el) {}
  Element(const Element& other) = default;

  Element& operator=(const Element& other) = default;

  bool operator==(const Element& other) const {
    return to_sort_ == other.to_sort_ && other_el_ == other.other_el_;
  }

  bool operator<(const Element& other) const {
    return to_sort_ < other.to_sort_;
  }
};

int main() {
  for (int i = 0; i < 10; ++i) {
    std::vector<int> v1 = random_int_vector();
    std::vector<int> v_gt = v1;
    merge_sort(v1);
    std::stable_sort(v_gt.begin(), v_gt.end());
    assert_vector_eq(v1, v_gt);
  }
  for (int i = 0; i < 10; ++i) {
    std::vector<int> v1 = random_int_vector();
    std::vector<int> v_gt = v1;
    merge_sort(v1, std::greater<>());
    std::stable_sort(v_gt.begin(), v_gt.end(), std::greater<>());
    assert_vector_eq(v1, v_gt);
  }

  std::random_device r;
  std::default_random_engine e(r());
  std::uniform_int_distribution<int> rnd1(0, 15);
  std::uniform_int_distribution<int> rnd2(0, 100);
  for (int i = 0; i < 20; ++i) {
    std::vector<Element> el_v1;
    el_v1.reserve(50);
    for (int j = 0; j < 50; ++j) {
      el_v1.emplace_back(rnd1(e), rnd2(e));
    }
    std::vector<Element> el_v_gt = el_v1;
    merge_sort(el_v1);
    std::stable_sort(el_v_gt.begin(), el_v_gt.end());
    for (int j = 0; j < el_v1.size(); ++j) {
      MY_ASSERT(el_v1.at(j) == el_v_gt.at(j));
    }
  }
  return 0;
}
