#include "binary_search_tree.h"

#include <algorithm>
#include <set>
#include <vector>

#include "vector.h"

int main() {
  for (int t = 0; t < 300; ++t) {
    BST<int> bst;
    std::vector<int> v = random_int_vector(100);
    if (v.empty()) continue;
    for (int val : v) {
      if (!bst.contains(val)) bst.insert(val);
    }
    std::set<int> s(v.begin(), v.end());
    auto traversal_inorder = bst.traversal_inorder();
    std::vector<int> gt_inorder(s.begin(), s.end());
    assert_vector_eq(traversal_inorder, gt_inorder);
    int v_min = *std::min_element(v.begin(), v.end());
    int v_max = *std::max_element(v.begin(), v.end());
    for (int i = v_min - 1; i <= v_max + 1; ++i) {
      MY_ASSERT(bst.contains(i) == (s.find(i) != s.end()));
    }
    for (auto it = v.rbegin(); it != v.rend(); ++it) {
      bst.erase(*it);
      MY_ASSERT(!bst.contains(*it));
    }
  }
}
