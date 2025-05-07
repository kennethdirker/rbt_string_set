/*
 *  RedBlackTree.h
 *  Red-Black Tree implementation.
 * 
 *  Adjusted by Kenneth Dirker
 *  Originally written by Yassaman Ommi on 2018-11-27.
 */

#include "RedBlackTree.h"

using namespace rbt;

void RedBlackTree::leftRotate(Node* x) {
    if (x == nullptr || x->right == nullptr)
        return;

    Node* y = x->right;
    x->right = y->left;
    if (y->left != nullptr)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

//  right rotation
void RedBlackTree::rightRotate(Node* y) {
    if (y == nullptr || y->left == nullptr)
        return;

    Node* x = y->left;
    y->left = x->right;
    if (x->right != nullptr)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == nullptr)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

// fix violations after inserting a node
void RedBlackTree::fixInsert(Node* z) {
    while (z != root && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y != nullptr && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left;
            if (y != nullptr && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

// Transplant function used in deletion
void RedBlackTree::transplant(Node* u, Node* v) {
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != nullptr)
        v->parent = u->parent;
}

//    delete a node
void RedBlackTree::deleteNode(Node* z) {
    if (z == nullptr)
        return;

    Node* y = z;
    Node* x = nullptr;
    Color y_original_color = y->color;

    if (z->left == nullptr) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == nullptr) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = minimum(z->right);
        y_original_color = y->color;
        x = y->right;

        if (y->parent == z) {
            if (x != nullptr)
                x->parent = y; // Check if x is not nullptr before assigning parent
        } else {
            if (x != nullptr)
                x->parent = y->parent; // Check if x and y->parent are not nullptr before assigning parent
            transplant(y, y->right);
            if (y->right != nullptr)
                y->right->parent = y; // Check if y->right is not nullptr before assigning parent
            y->right = z->right;
            if (y->right != nullptr)
                y->right->parent = y; // Check if y->right is not nullptr before assigning parent
        }
        transplant(z, y);
        y->left = z->left;
        if (y->left != nullptr)
            y->left->parent = y; // Check if y->left is not nullptr before assigning parent
        y->color = z->color;
    }

    if (y_original_color == BLACK && x != nullptr) // Check if x is not nullptr
        fixDelete(x);

    delete z; // Free memory allocated for the deleted node
}

// Function to fix violations after deleting a node
void RedBlackTree::fixDelete(Node* x) {
    while (x != root && x != nullptr && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if ((w->left == nullptr || w->left->color == BLACK) &&
                (w->right == nullptr || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right == nullptr || w->right->color == BLACK) {
                    if (w->left != nullptr)
                        w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->right != nullptr)
                    w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if ((w->right == nullptr || w->right->color == BLACK) &&
                (w->left == nullptr || w->left->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left == nullptr || w->left->color == BLACK) {
                    if (w->right != nullptr)
                        w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->left != nullptr)
                    w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    if (x != nullptr)
        x->color = BLACK;
}

// find the minimum node in a subtree
Node* RedBlackTree::minimum(Node* node) {
    while (node->left != nullptr)
        node = node->left;
    return node;
}

// print the tree structure (in-order traversal)
void RedBlackTree::printHelper(Node* root, int space) {
    constexpr int COUNT = 5;
    if (root == nullptr)
        return;
    space += COUNT;
    printHelper(root->right, space);
    std::cout << std::endl;
    for (int i = COUNT; i < space; i++)
        std::cout << " ";
    std::cout << root->data << "(" << ((root->color == RED) ? "RED" : "BLACK") << ")" << std::endl;
    printHelper(root->left, space);
}

RedBlackTree::RedBlackTree() {
    root = nullptr;
}

// insert a node
bool RedBlackTree::insert(const std::string &value) {
    Node* new_node_ptr = new Node(value);
    Node* parent_ptr = nullptr;
    Node* node_ptr = root;

    // Traverse tree to leave
    while (node_ptr != nullptr) {
        parent_ptr = node_ptr;      // Remember parent node
        if (new_node_ptr->data.compare(node_ptr->data) < 0)
            node_ptr = node_ptr->left;
        else if (new_node_ptr->data.compare(node_ptr->data) > 0)
            node_ptr = node_ptr->right;
        else
            return false;
    }

    // Insert new node
    new_node_ptr->parent = parent_ptr;
    if (parent_ptr == nullptr)
        root = new_node_ptr;
    else if (new_node_ptr->data.compare(parent_ptr->data) < 0)
        parent_ptr->left = new_node_ptr;
    else
        parent_ptr->right = new_node_ptr;
    fixInsert(new_node_ptr);

    return true;
}

/**
 * Try and find a node containing a certain string. If such a node exists,
 * return a pointer to it. Returns a nullptr otherwise.
 */
Node* RedBlackTree::find(const std::string &value) const {
    Node* node_ptr = root;
    
    while (node_ptr != nullptr) {
        if (value.compare(node_ptr->data) == 0)
            return node_ptr;
        
        if (node_ptr->data.compare(value) > 0) 
            node_ptr = node_ptr->left;
        
        else
            node_ptr = node_ptr->right;
    }
    return nullptr;
}

/**
 * Delete the node containing the string value if it exists in the tree.
 * 
 * Returns:
 *      True if a node was deleted, false otherwise.
 */
bool RedBlackTree::remove(const std::string &value) {
    Node* node_ptr = find(value);
    if (node_ptr == nullptr)
        return false;
    
    deleteNode(node_ptr);
    return true;
}

// print the tree structure
void RedBlackTree::printTree() {
    printHelper(root, 0);
}

/**
 * Recursive helper function to traverse the tree and save its elements
 * in-order.
 * 
 * Arguments: 
 *      node: Root of the traversal.
 *      v: Reference to string vector in which node values are saved.  
 */
void RedBlackTree::inorder_helper(Node* node, std::vector<rbt::Node*> &v) const {
    if (node != nullptr) {
        inorder_helper(node->left, v);
        v.push_back(node);
        // v.push_back(node->data);
        inorder_helper(node->right, v);
    }
}

/**
 * Traverse the tree in-order and return a vector containing the strings
 * contained in the tree in alphabetical order.
 */
std::vector<rbt::Node*> RedBlackTree::inorder() const {
    std::vector<rbt::Node*> v;
    inorder_helper(root, v);
    return v;
}
