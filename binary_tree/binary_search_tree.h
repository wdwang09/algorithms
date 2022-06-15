// https://en.wikipedia.org/wiki/Binary_search_tree

#pragma once

#include <memory>
#include <stdexcept>
#include <vector>

template <class T, class Compare = std::less<>>
class BST {
 private:
  struct Node {
    T val_;
    std::shared_ptr<BST<T, Compare>::Node> left_;
    std::shared_ptr<BST<T, Compare>::Node> right_;

    explicit Node(const T& v) : val_(v) {}
  };

  using BSTNode = BST<T, Compare>::Node;

 public:
  std::vector<T> traversal_inorder() const {
    std::vector<T> v;
    traversal_inorder(root_, v);
    return v;
  }

  void insert(const T& val) {
    auto new_node = std::make_shared<BSTNode>(val);
    if (!root_) {
      root_ = new_node;
      return;
    }
    auto current_node = root_;
    while (true) {
      if (cmp_(new_node->val_, current_node->val_)) {
        if (!current_node->left_) {
          current_node->left_ = new_node;
          return;
        }
        current_node = current_node->left_;
      } else {
        if (!current_node->right_) {
          current_node->right_ = new_node;
          return;
        }
        current_node = current_node->right_;
      }
    }
  }

  bool contains(const T& val) {
    std::shared_ptr<BSTNode> p;
    return find(val, p) != nullptr;
  }

  bool erase(const T& val) {
    std::shared_ptr<BSTNode> del_node_parent;
    std::shared_ptr<BSTNode> del_node = find(val, del_node_parent);
    if (!del_node) return false;
    if (!del_node->left_) {
      transplant(del_node_parent, del_node, del_node->right_);
    } else if (!del_node->right_) {
      transplant(del_node_parent, del_node, del_node->left_);
    } else {
      std::shared_ptr<BSTNode> successor = del_node->right_;
      std::shared_ptr<BSTNode> successor_parent = del_node;
      // successor must exists
      while (successor->left_) {
        successor_parent = successor;
        successor = successor->left_;
      }
      // successor doesn't have left child
      if (successor_parent != del_node) {
        transplant(successor_parent, successor, successor->right_);
        successor->right_ = del_node->right_;
      }
      transplant(del_node_parent, del_node, successor);
      successor->left_ = del_node->left_;
    }
    return true;
  }

 private:
  std::shared_ptr<BSTNode> find(const T& val,
                                std::shared_ptr<BSTNode>& parent) {
    parent = nullptr;
    std::shared_ptr<BSTNode> current_node = root_;
    while (true) {
      if (!current_node) return nullptr;
      if (cmp_(val, current_node->val_)) {
        parent = current_node;
        current_node = current_node->left_;
      } else if (cmp_(current_node->val_, val)) {
        parent = current_node;
        current_node = current_node->right_;
      } else {
        return current_node;
      }
    }
  }

  // change child to another node
  void transplant(std::shared_ptr<BSTNode> subtree_parent,
                  std::shared_ptr<BSTNode> subtree_root_old,
                  std::shared_ptr<BSTNode> subtree_root_new) {
    if (!subtree_parent) {
      root_ = subtree_root_new;
    } else if (subtree_root_old == subtree_parent->left_) {
      subtree_parent->left_ = subtree_root_new;
    } else if (subtree_root_old == subtree_parent->right_) {
      subtree_parent->right_ = subtree_root_new;
    } else {
      throw std::runtime_error(
          "subtree_parent isn't subtree_root_old's parent.");
    }
  }

  void traversal_inorder(std::shared_ptr<BSTNode> node,
                         std::vector<T>& v) const {
    if (!node) return;
    traversal_inorder(node->left_, v);
    v.push_back(node->val_);
    traversal_inorder(node->right_, v);
  }

  std::shared_ptr<BSTNode> root_;
  Compare cmp_;
};
