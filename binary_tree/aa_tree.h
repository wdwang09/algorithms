// https://en.wikipedia.org/wiki/AA_tree

#pragma once

#include <memory>
#include <vector>

template <class T, class Compare = std::less<>>
class AATree {
 private:
  struct Node {
    T val_;
    std::shared_ptr<AATree<T, Compare>::Node> left_;
    std::shared_ptr<AATree<T, Compare>::Node> right_;
    unsigned level_ = 1;

    explicit Node(const T& v) : val_(v) {}
  };

  using AANode = AATree<T, Compare>::Node;

  std::shared_ptr<AANode> root_;
  Compare cmp_;

 public:
  void insert(const T& val) { root_ = insert(val, root_); }

  bool contains(const T& val) { return find(val) != nullptr; }

  bool erase(const T& val) {
    bool is_erased = false;
    std::tie(root_, is_erased) = erase(val, root_);
    return is_erased;
  }

  std::vector<T> traversal_inorder() const {
    std::vector<T> v;
    traversal_inorder(root_, v);
    return v;
  }

  bool is_aa_tree() { return is_aa_tree(root_); }

 private:
  /*
   *    L <- T    =>    L -> T
   *   A B    R        A    B R
   */
  static std::shared_ptr<AANode> skew(std::shared_ptr<AANode> root) {
    // balanced
    if (!root) return root;
    if (!root->left_) return root;
    if (root->left_->level_ != root->level_) return root;
    // unbalanced
    auto L = root->left_;  // not nullptr
    root->left_ = L->right_;
    L->right_ = root;
    return L;
  }

  /*
   *    T -> R -> X    =>     R
   *   A    B               T   X
   *                       A B
   */
  static std::shared_ptr<AANode> split(std::shared_ptr<AANode> root) {
    // balanced
    if (!root) return root;
    if (!root->right_ || !root->right_->right_) return root;
    if (root->right_->right_->level_ != root->level_) return root;
    // unbalanced
    auto R = root->right_;
    root->right_ = R->left_;
    R->left_ = root;
    ++R->level_;
    return R;
  }

  std::shared_ptr<AANode> insert(const T& val, std::shared_ptr<AANode> root) {
    if (!root) {
      return std::make_shared<AANode>(val);
    }
    if (cmp_(val, root->val_)) {
      root->left_ = insert(val, root->left_);
    } else {
      root->right_ = insert(val, root->right_);
    }

    root = skew(root);
    root = split(root);
    return root;
  }

  std::pair<std::shared_ptr<AANode>, bool> erase(const T& val,
                                                 std::shared_ptr<AANode> root) {
    std::pair<std::shared_ptr<AANode>, bool> root_and_is_existent(nullptr,
                                                                  false);
    if (!root) return root_and_is_existent;

    // BST delete
    if (cmp_(val, root->val_)) {
      std::tie(root->left_, root_and_is_existent.second) =
          erase(val, root->left_);
    } else if (cmp_(root->val_, val)) {
      std::tie(root->right_, root_and_is_existent.second) =
          erase(val, root->right_);
    } else {
      // root is the node to be deleted
      root_and_is_existent.second = true;
      if (!root->left_ && !root->right_) {
        root_and_is_existent.first = nullptr;
        return root_and_is_existent;
      }
      if (!root->left_) {
        auto successor = root->right_;
        while (successor->left_) {
          successor = successor->left_;
        }
        root->val_ = successor->val_;
        root->right_ = erase(successor->val_, root->right_).first;
      } else {
        auto predecessor = root->left_;
        while (predecessor->right_) {
          predecessor = predecessor->right_;
        }
        root->val_ = predecessor->val_;
        root->left_ = erase(predecessor->val_, root->left_).first;
      }
    }

    // re-balance tree
    root = decrease_level(root);
    root = skew(root);
    root->right_ = skew(root->right_);
    if (root->right_) {
      root->right_->right_ = skew(root->right_->right_);
    }
    root = split(root);
    root->right_ = split(root->right_);
    root_and_is_existent.first = root;
    return root_and_is_existent;
  }

  static std::shared_ptr<AANode> decrease_level(std::shared_ptr<AANode> root) {
    if (!root) return nullptr;
    using LevelType = decltype(root->level_);
    LevelType left_level = 0, right_level = 0;
    if (root->left_) left_level = root->left_->level_;
    if (root->right_) right_level = root->right_->level_;
    LevelType should_be = std::min(left_level, right_level) + 1;
    if (should_be < root->level_) {
      root->level_ = should_be;
      if (root->right_ && should_be < root->right_->level_) {
        root->right_->level_ = should_be;
      }
    }
    return root;
  }

  std::shared_ptr<AANode> find(const T& val) {
    std::shared_ptr<AANode> current_node = root_;
    while (true) {
      if (!current_node) return nullptr;
      if (cmp_(val, current_node->val_)) {
        current_node = current_node->left_;
      } else if (cmp_(current_node->val_, val)) {
        current_node = current_node->right_;
      } else {
        return current_node;
      }
    }
  }

  static void traversal_inorder(std::shared_ptr<AANode> node,
                                std::vector<T>& v) {
    if (!node) return;
    traversal_inorder(node->left_, v);
    v.push_back(node->val_);
    traversal_inorder(node->right_, v);
  }

  /*
   * Only check level. Don't check BST.
   *
   * https://en.wikipedia.org/wiki/AA_tree#Balancing_rotations
   *
   * 1. The level of every leaf node is one.
   * 2. The level of every left child is exactly one less than that of its
   * parent.
   * 3. The level of every right child is equal to or one less than that of its
   * parent.
   * 4. The level of every right grandchild is strictly less than that of its
   * grandparent.
   * 5. Every node of level greater than one has two children.
   */
  static bool is_aa_tree(std::shared_ptr<AANode> root) {
    if (!root) return true;
    // 1
    if (!root->left_ && !root->right_ && root->level_ != 1) return false;
    // 2
    if (root->left_ && root->left_->level_ + 1 != root->level_) return false;
    // 3
    if (root->right_ && (root->right_->level_ != root->level_ &&
                         root->right_->level_ + 1 != root->level_)) {
      return false;
    }
    // 4
    if (root->right_ && root->right_->right_ &&
        root->right_->right_->level_ >= root->level_) {
      return false;
    }
    // 5
    if (root->level_ > 1 && (!root->left_ || !root->right_)) return false;
    return is_aa_tree(root->left_) && is_aa_tree(root->right_);
  }
};
