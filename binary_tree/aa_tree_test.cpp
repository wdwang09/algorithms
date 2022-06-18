#include "aa_tree.h"

#include <algorithm>
#include <set>
#include <vector>

#include "vector.h"

int main() {
  for (int t = 0; t < 300; ++t) {
    AATree<int> tree;
    std::vector<int> v = random_int_vector(100);
    if (v.empty()) continue;
    for (int val : v) {
      if (!tree.contains(val)) tree.insert(val);
    }
    std::set<int> s(v.begin(), v.end());
    auto traversal_inorder = tree.traversal_inorder();
    std::vector<int> gt_inorder(s.begin(), s.end());
    assert_vector_eq(traversal_inorder, gt_inorder);

    int v_min = *std::min_element(v.begin(), v.end());
    int v_max = *std::max_element(v.begin(), v.end());
    for (int i = v_min - 1; i <= v_max + 1; ++i) {
      MY_ASSERT(tree.contains(i) == (s.find(i) != s.end()));
    }

    MY_ASSERT(tree.is_aa_tree());

    for (auto it = v.rbegin(); it != v.rend(); ++it) {
      auto num = *it;
      if (s.find(num) != s.end()) {
        MY_ASSERT(tree.contains(num));
        s.erase(num);
        MY_ASSERT(tree.erase(num));
      }
      MY_ASSERT(!tree.contains(num));
      MY_ASSERT(tree.is_aa_tree());
    }
  }
}
