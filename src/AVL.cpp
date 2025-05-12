// #include <cmath>
#include <algorithm>
#include <stdexcept>
#include "AVL.h"

using namespace avl;

/*********************************
 *              Node
 *********************************/

bool Node::operator==(const Node &rhs) const { return this->s.compare(rhs.s) == 0; }
bool Node::operator!=(const Node &rhs) const { return this->s.compare(rhs.s) != 0; }
bool Node::operator<(const Node &rhs) const { return this->s.compare(rhs.s) < 0; }
bool Node::operator>(const Node &rhs) const { return this->s.compare(rhs.s) > 0; }
bool Node::operator==(const std::string &rhs) const { return this->s.compare(s) == 0; }
bool Node::operator!=(const std::string &rhs) const { return this->s.compare(s) != 0; }
bool Node::operator<(const std::string &rhs) const { return this->s.compare(s) < 0; }
bool Node::operator>(const std::string &rhs) const { return this->s.compare(s) > 0; }
std::string Node::get() const { return s; }

/*********************************
 *              AVL
 *********************************/
void AVL::inorder_helper(Node *node, std::vector<std::string> &v) const {
    if (node == nullptr)
        return;

    inorder_helper(node->left, v);
    v.push_back(node->get());
    inorder_helper(node->right, v);
}

void AVL::inorder_helper(Node *node, std::vector<Node*> &v) const {
    if (node == nullptr)
        return;

    inorder_helper(node->left, v);
    v.push_back(node);
    inorder_helper(node->right, v);
}

void AVL::preorder_helper(Node *node, std::vector<Node *> &v) const
{
    if (node == nullptr)
        return;

    preorder_helper(node->left, v);
    preorder_helper(node->right, v);
    v.push_back(node);
}

void AVL::preorder_helper(Node *node, std::vector<std::string> &v) const
{
    if (node == nullptr)
        return;

    preorder_helper(node->left, v);
    preorder_helper(node->right, v);
    v.push_back(node->get());
}

Node* AVL::insert_node(Node* parent, const std::string &s) {
    Node *new_node = new Node(s);
    new_node->parent = parent;
    update_parent(new_node, new_node);
    tree_size++;

    return new_node;
}

uint AVL::get_height(Node* node) const { return node == nullptr ? 0 : node->height; }

Node* AVL::pivot_left(Node* old_pivot) {
    // Rotate
    Node* x = 
    // Node* new_pivot = old_pivot->right;
    // update_parent(old_pivot, new_pivot);
    // new_pivot->parent = old_pivot->parent;

    // old_pivot->parent = new_pivot;
    // Node* temp = new_pivot->left;
    // new_pivot->left = old_pivot;

    // old_pivot->right = temp;
    // old_pivot->right->parent = old_pivot;


    // Adjust balance
    new_pivot->height = 1 + std::max(get_height(new_pivot->left),
                                 get_height(new_pivot->right));
    old_pivot->height = 1 + std::max(get_height(old_pivot->left),
                                 get_height(old_pivot->right));

    return new_pivot;
}

Node* AVL::pivot_right(Node* old_pivot)
{
    // Rotate
    Node *new_pivot = old_pivot->left;
    update_parent(old_pivot, new_pivot);
    new_pivot->parent = old_pivot->parent;

    old_pivot->parent = new_pivot;
    Node *temp = new_pivot->right;
    new_pivot->right = old_pivot;

    old_pivot->left = temp;
    old_pivot->left->parent = old_pivot;

    // Adjust height
    new_pivot->height = 1 + std::max(get_height(new_pivot->left), 
                                 get_height(new_pivot->right));
    old_pivot->height = 1 + std::max(get_height(old_pivot->left),
                                 get_height(old_pivot->right));

    return new_pivot;
}

int AVL::get_balance(Node* node) const {
    if (node == nullptr)
        return 0;
    return get_height(node->left) - get_height(node->right);
}

void AVL::balance_after_insert(Node *new_node)
{
    Node *node = new_node;
    while (node != nullptr)
    {   // Search from leaf to root for unbalanced node
        int balance = get_balance(node);
        if (std::abs(balance) > 1)
        {   // Tree is imbalanced
            if (balance > 1 && *new_node < *(node->left))
            {   // Left left
                node = pivot_right(node);
            }   
            else if (balance > 1 && *new_node > *(node->left))
            {   // Left right
                node->left = pivot_left(node->left);
                node = pivot_right(node);
            }   
            else if (balance < -1 && *new_node < *(node->right))
            {   // Right left
                node->right = pivot_right(node->right);
                node = pivot_left(node);
            } 
            else if (balance < -1 && *new_node > *(node->right))
            {   // Right right
                node = pivot_left(node);
            }

            return;
        }

        node = node->parent;
    }
}

void AVL::balance_after_remove(Node *new_node)
{
    Node *node = new_node;
    while (node != nullptr)
    {
        int balance = get_balance(node);

        if (std::abs(balance) > 1)
        {   // Tree is imbalanced
            if (balance > 1) 
            {   // Left
                balance = get_balance(node->left);
                if (balance >= 0)
                { // Left left
                    node = pivot_right(node);
                }
                else
                {   // Left right
                    node->left = pivot_left(node->left);
                    node = pivot_right(node);
                }
            }
            else 
            {   // Right
                balance = get_balance(node->right);
                if (balance > 0) 
                {   // Right left
                    node->right = pivot_right(node->right);
                    node = pivot_left(node);
                }
                else
                {   // Right right
                    node = pivot_left(node);
                }
            }
        }

        node = node->parent;
    }
}

bool AVL::insert(const std::string &s) {
    Node* node = root;
    Node* parent = nullptr;
    Node temp_node(s);

    // Traverse tree to leaf
    while (node != nullptr) {
        // Value is already in the tree
        if (temp_node == *node)
            return false;
        
        // Descent 1 layer
        parent = node;
        if (temp_node < *node)
            node = node->left;
        else
            node = node->right;
    }

    // Node* new_node = insert_node(parent, left, s);
    Node* new_node = insert_node(parent, s);
    update_heights(new_node);

    if (parent != nullptr)
        balance_after_insert(new_node);

    return true;
}

Node *AVL::find(const std::string &s) const {
    Node* node = root;
    while (node != nullptr){
        // Value is already in the tree
        if (*node == s)
            return node;
        
        // Descent 1 layer
        if (*node > s)
            node = node->left;
        else
            node = node->right;
    }
    return nullptr;
}

bool AVL::contains(const std::string &s) const {
    return find(s) != nullptr;
}

void AVL::update_parent(Node* node, Node* ptr) {
    Node* parent = node->parent;
    if (parent == nullptr)
        root = ptr;
    else if (*node < *parent)
        parent->left = ptr;
    else
        parent->right = ptr;
}

Node* AVL::get_next(Node* node) {
    node = node->right;
    while (node->left != nullptr)
        node = node->left;
    
    return node;
}

void AVL::update_heights(Node* node) {
    while (node != nullptr) {
        node->height = 1 + std::max(get_height(node->left),
                                    get_height(node->right));
        node = node->parent;
    }
}

Node* AVL::remove_node(Node *node)
{
    Node* node_ptr = node;
    // Node* parent = node->parent;
    // Node* parent;

    // Delete leaf
    if (node->left == nullptr && node->right == nullptr) {
        update_parent(node, nullptr);
        node = node->parent;
    } // Delete node with both children
    else if (node->left != nullptr && node->right != nullptr) {
        Node* next = get_next(node);
        update_parent(next, nullptr);
        next->parent = node->parent;
        next->left = node->left;
        next->right = node->right;
        next->height = node->height;
        update_parent(next, next);
        // update_heights(next->parent, next);
    } // Delete node with left child
    else if (node->left != nullptr) {
        node->left->parent = node->parent;
        update_parent(node, node->left);
    } // Delete node with right child
    else {
        node->right->parent = node->parent;
        update_parent(node, node->right);
    }
    update_heights(node);
    delete node_ptr;
    tree_size--;
    
    return node;
}

bool AVL::remove(const std::string &s) {
    // Retrieve the node to be deleted
    Node* node = find(s);
    if (node == nullptr)
        return false;
        
    // Remove node and rebalance the tree if needed
    Node* parent = remove_node(node);
    if (parent != nullptr)
        balance_after_remove(parent);

    return true;
}

std::vector<std::string> AVL::inorder() const {
    std::vector<std::string> v;
    inorder_helper(root, v);
    return v;
}

std::vector<std::string> AVL::preorder() const {
    // std::vector<Node*> v;
    std::vector<std::string> v;
    preorder_helper(root, v);
    // preorder_helper(root, v);
    // for (Node* n: v) {
    //     std::cout << n->height << n->get() << std::endl;
    //     s.push_back(n->get());
    // }
    // return s;
    return v;
}

uint AVL::size() const {
    return tree_size;
}

bool AVL::is_empty() const {
    return tree_size == 0;
}



void AVL::clear() {
    std::vector<Node*> v;
    inorder_helper(root, v);
    for (Node* n: v)
        remove_node(n);
}