#include "quick_sort.h"

#include <vector>

#include "vector.h"

int main() {
  for (int i = 0; i < 10; ++i) {
    std::vector<int> v1 = random_int_vector();
    std::vector<int> v2 = v1;
    std::vector<int> v_gt = v1;
    quick_sort(v1);
    quick_sort_2::quick_sort(v2);
    std::sort(v_gt.begin(), v_gt.end());
    assert_vector_eq(v1, v_gt);
    assert_vector_eq(v2, v_gt);
  }
  return 0;
}
