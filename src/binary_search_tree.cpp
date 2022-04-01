#include "assignment/binary_search_tree.hpp"

namespace assignment {

  BinarySearchTree::~BinarySearchTree() {
    BinarySearchTree::Clear();
  }

  void BinarySearchTree::Insert(int key, int value) {
    insert(key, value, root_);
  }

  bool BinarySearchTree::Remove(int key) {
    if (!Contains(key)) {
      return false;
    }
    return remove(key, root_);
  }

  void BinarySearchTree::Clear() {
    clear(root_);
    root_ = nullptr;
  }

  std::optional<int> BinarySearchTree::Find(int key) const {
    Node* node = find(key, root_);
    if (node != nullptr) {
      return node->value;
    }
    return std::nullopt;
  }

  bool BinarySearchTree::Contains(int key) const {
    return Find(key) != std::nullopt;
  }

  bool BinarySearchTree::IsEmpty() const {
    return root_ == nullptr;
  }

  std::optional<int> BinarySearchTree::FindMin() const {
    Node* node = find_min(root_);
    if (node != nullptr) {
      return node->key;
    }
    return std::nullopt;
  }

  std::optional<int> BinarySearchTree::FindMax() const {
    Node* node = find_max(root_);
    if (node != nullptr) {
      return node->key;
    }
    return std::nullopt;
  }

  Node* BinarySearchTree::root() const {
    return root_;
  }

  // вспомогательные методы

  void BinarySearchTree::insert(int key, int value, Node*& node) {
    if (node == nullptr) {
      node = new Node(key, value);
    } else {
      if (node->key == key) {
        node->value = value;
      } else if (node->key < key) {
        insert(key, value, node->right);
      } else {
        insert(key, value, node->left);
      }
    }
  }

  bool BinarySearchTree::remove(int key, Node*& node) {
    if (node->key < key) {
      return remove(key, node->right);
    } else if (node->key > key) {
      return remove(key, node->left);
    } else {
      if (node->left == nullptr & node->right == nullptr) {
        delete node;
        node = nullptr;
      } else if (node->left != nullptr & node->right == nullptr) {
        Node* deletedNode = node;
        node = node->left;
        delete deletedNode;
      } else if (node->left == nullptr & node->right != nullptr) {
        Node* deletedNode = node;
        node = node->right;
        delete deletedNode;
      } else if (node->left != nullptr & node->right != nullptr) {
        Node* insteadNode = find_min(node->right);
        node->key = insteadNode->key;
        node->value = insteadNode->value;
        return remove(node->key, node->right);
      }
      return true;
    }
  }

  void BinarySearchTree::clear(Node* node) {
    if (node != nullptr) {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

  Node* BinarySearchTree::find(int key, Node* node) const {
    if (node == nullptr) {
      return nullptr;
    } else if (node->key == key) {
      return node;
    } else if (node->key < key) {
      return find(key, node->right);
    } else {
      return find(key, node->left);
    }
  }

  Node* BinarySearchTree::find_min(Node* node) const {
    if (node == nullptr) {
      return nullptr;
    } else if (node->left == nullptr) {
      return node;
    } else {
      return find_min(node->left);
    }
  }

  Node* BinarySearchTree::find_max(Node* node) const {
    if (node == nullptr) {
      return nullptr;
    } else if (node->right == nullptr) {
      return node;
    } else {
      return find_max(node->right);
    }
  }

}  // namespace assignment