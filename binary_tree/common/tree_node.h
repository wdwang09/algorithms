#pragma once

#include <memory>
#include <queue>
#include <vector>

template <typename T>
struct TreeNode : std::enable_shared_from_this<TreeNode<T>> {
  T val_;
  std::shared_ptr<TreeNode<T>> left_;
  std::shared_ptr<TreeNode<T>> right_;

  explicit TreeNode(const T& v) : val_(v) {}
};

// ===

// https://support.leetcode.com/hc/en-us/articles/360011883654-What-does-1-null-2-3-mean-in-binary-tree-representation-
template <typename T>
std::shared_ptr<TreeNode<T>> generate_tree_from_leetcode_style(
    const std::vector<T>& leetcode_tree, T symbol_null) {
  if (leetcode_tree.empty() || leetcode_tree.at(0) == symbol_null) {
    return nullptr;
  }

  using NodePtr = std::shared_ptr<TreeNode<T>>;

  NodePtr root = std::make_shared<TreeNode<T>>(leetcode_tree.at(0));
  std::queue<NodePtr> q;
  q.push(root);

  std::size_t idx = 0;
  while (!q.empty()) {
    NodePtr current_node = q.front();
    q.pop();
    ++idx;
    if (idx >= leetcode_tree.size()) break;
    if (leetcode_tree[idx] != symbol_null) {
      current_node->left_ = std::make_shared<TreeNode<T>>(leetcode_tree[idx]);
      q.push(current_node->left_);
    }
    ++idx;
    if (idx >= leetcode_tree.size()) break;
    if (leetcode_tree[idx] != symbol_null) {
      current_node->right_ = std::make_shared<TreeNode<T>>(leetcode_tree[idx]);
      q.push(current_node->right_);
    }
  }
  return root;
}

template <typename T>
std::vector<T> tree_to_leetcode_style(std::shared_ptr<TreeNode<T>> tree,
                                      T symbol_null) {
  std::vector<T> res;
  if (!tree) return res;
  std::queue<std::shared_ptr<TreeNode<T>>> q;
  q.push(tree);
  while (!q.empty()) {
    auto current_node = q.front();
    q.pop();
    if (!current_node) {
      res.push_back(symbol_null);
      continue;
    }
    res.push_back(current_node->val_);
    q.push(current_node->left_);
    q.push(current_node->right_);
  }
  while (res.back() == symbol_null) {
    res.pop_back();
  }
  return res;
}
