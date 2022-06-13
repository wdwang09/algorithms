#include "heap_sort.h"

#include <functional>
#include <vector>

#include "vector.h"

int main() {
  for (int i = 0; i < 10; ++i) {
    std::vector<int> v1 = random_int_vector();
    std::vector<int> v_gt = v1;
    heap_sort(v1);
    std::sort(v_gt.begin(), v_gt.end());
    assert_vector_eq(v1, v_gt);
  }
  for (int i = 0; i < 10; ++i) {
    std::vector<int> v1 = random_int_vector();
    std::vector<int> v_gt = v1;
    heap_sort(v1, std::greater<>());
    std::sort(v_gt.begin(), v_gt.end(), std::greater<>());
    assert_vector_eq(v1, v_gt);
  }
  return 0;
}
