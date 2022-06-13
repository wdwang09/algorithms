#include "traversal.h"

#include <memory>
#include <vector>

#include "common/binary_tree_testcase.h"
#include "vector.h"

int main() {
  constexpr int null = INT_MAX;
  auto tree_testcase = get_leetcode_style_tree(null);
  for (const auto& v : tree_testcase) {
    std::shared_ptr<TreeNode<int>> tree =
        generate_tree_from_leetcode_style(v, null);
    assert_vector_eq(tree_to_leetcode_style(tree, null), v);
    std::vector<int> r_vec, i_vec;
    r_vec = recursion::preorder(tree);
    i_vec = iteration::preorder(tree);
    assert_vector_eq(r_vec, i_vec);
    r_vec = recursion::inorder(tree);
    i_vec = iteration::inorder(tree);
    assert_vector_eq(r_vec, i_vec);
    r_vec = recursion::postorder(tree);
    i_vec = iteration::postorder(tree);
    assert_vector_eq(r_vec, i_vec);
  }
}
