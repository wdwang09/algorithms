// https://en.wikipedia.org/wiki/Tree_traversal

#pragma once

#include <stack>
#include <vector>

#include "common/tree_node.h"

namespace recursion {

template <typename T>
void _preorder(std::shared_ptr<TreeNode<T>> node, std::vector<T> &v) {
  if (!node) return;
  v.push_back(node->val_);
  _preorder(node->left_, v);
  _preorder(node->right_, v);
}

template <typename T>
std::vector<T> preorder(std::shared_ptr<TreeNode<T>> node) {
  std::vector<T> v;
  _preorder(node, v);
  return v;
}

template <typename T>
void _inorder(std::shared_ptr<TreeNode<T>> node, std::vector<T> &v) {
  if (!node) return;
  _inorder(node->left_, v);
  v.push_back(node->val_);
  _inorder(node->right_, v);
}

template <typename T>
std::vector<T> inorder(std::shared_ptr<TreeNode<T>> node) {
  std::vector<T> v;
  _inorder(node, v);
  return v;
}

template <typename T>
void _postorder(std::shared_ptr<TreeNode<T>> node, std::vector<T> &v) {
  if (!node) return;
  _postorder(node->left_, v);
  _postorder(node->right_, v);
  v.push_back(node->val_);
}

template <typename T>
std::vector<T> postorder(std::shared_ptr<TreeNode<T>> node) {
  std::vector<T> v;
  _postorder(node, v);
  return v;
}

}  // namespace recursion

namespace iteration {

template <typename T>
std::vector<T> preorder(std::shared_ptr<TreeNode<T>> node) {
  std::vector<T> res;
  if (!node) return res;
  std::stack<std::shared_ptr<TreeNode<T>>> s;
  s.push(node);
  while (!s.empty()) {
    auto current_node = s.top();
    s.pop();
    res.push_back(current_node->val_);
    if (current_node->right_) {
      s.push(current_node->right_);
    }
    if (current_node->left_) {
      s.push(current_node->left_);
    }
  }
  return res;
}

template <typename T>
std::vector<T> inorder(std::shared_ptr<TreeNode<T>> node) {
  std::vector<T> res;
  if (!node) return res;
  std::stack<std::shared_ptr<TreeNode<T>>> s;
  auto current_node = node;
  while (!s.empty() || current_node) {
    if (current_node) {
      s.push(current_node);
      current_node = current_node->left_;
    } else {
      current_node = s.top();
      s.pop();
      res.push_back(current_node->val_);
      current_node = current_node->right_;
    }
  }
  return res;
}

template <typename T>
std::vector<T> postorder(std::shared_ptr<TreeNode<T>> node) {
  std::vector<T> res;
  if (!node) return res;
  std::stack<std::shared_ptr<TreeNode<T>>> s;
  auto current_node = node;
  decltype(current_node) last_node_visited = nullptr;
  while (!s.empty() || current_node) {
    if (current_node) {
      s.push(current_node);
      current_node = current_node->left_;
    } else {
      if (s.top()->right_ && s.top()->right_ != last_node_visited) {
        current_node = s.top()->right_;
      } else {
        // When visiting a node, its children were already visited.
        res.push_back(s.top()->val_);
        last_node_visited = s.top();
        s.pop();
      }
    }
  }
  return res;
}

}  // namespace iteration
