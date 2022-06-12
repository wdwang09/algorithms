#include "priority_queue.h"

#include <queue>
#include <vector>

#include "vector.h"

template <typename T>
std::vector<int> get_int_queue(T& q) {
  std::vector<int> res;
  while (!q.empty()) {
    res.push_back(q.top());
    q.pop();
  }
  return res;
}

int main() {
  for (int i = 0; i < 10; ++i) {
    const std::vector<int> v = random_int_vector();

    priority_queue<int> pq_less;
    for (auto n : v) pq_less.push(n);
    auto res_less = get_int_queue(pq_less);

    std::priority_queue<int> stl_pq_less(v.begin(), v.end());
    auto stl_res_less = get_int_queue(stl_pq_less);

    assert_vector_eq(res_less, stl_res_less);

    // ===

    priority_queue<int, std::greater<>> pq_greater;
    for (auto n : v) pq_greater.push(n);
    auto res_greater = get_int_queue(pq_greater);

    std::priority_queue<int, std::vector<int>, std::greater<>> stl_pq_greater(
        v.begin(), v.end());
    auto stl_res_greater = get_int_queue(stl_pq_greater);

    assert_vector_eq(res_greater, stl_res_greater);
  }
}
