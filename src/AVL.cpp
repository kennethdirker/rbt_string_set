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
bool Node::operator==(const std::string &rhs) const { return this->s.compare(rhs) == 0; }
bool Node::operator!=(const std::string &rhs) const { return this->s.compare(rhs) != 0; }
bool Node::operator<(const std::string &rhs) const { return this->s.compare(rhs) < 0; }
bool Node::operator>(const std::string &rhs) const { return this->s.compare(rhs) > 0; }
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

void AVL::preorder_helper(Node *node, std::vector<std::string> &v) const
{
    if (node == nullptr)
        return;

    v.push_back(node->get());
    preorder_helper(node->left, v);
    preorder_helper(node->right, v);
}

void AVL::preorder_helper(Node *node, std::vector<Node *> &v) const
{
    if (node == nullptr)
        return;

    v.push_back(node);
    preorder_helper(node->left, v);
    preorder_helper(node->right, v);
}

void AVL::postorder_helper(Node *node, std::vector<std::string> &v) const
{
    if (node == nullptr)
        return;

    preorder_helper(node->left, v);
    preorder_helper(node->right, v);
    v.push_back(node->get());
}

void AVL::postorder_helper(Node* node, std::vector<Node*> &v) const {
    if (node == nullptr)
        return;

    postorder_helper(node->left, v);
    postorder_helper(node->right, v);
    v.push_back(node);
}

uint AVL::get_height(Node* node) const { return node == nullptr ? 0 : node->height; }

// Update the height of the node and its grandparents.
void AVL::update_heights(Node* node) {
    while (node != nullptr) {
        node->height = 1 + std::max(get_height(node->left),
                                    get_height(node->right));
        node = node->parent;
    }
}

// Change the pointer of the parent of node that points to node into 
// some other pointer.
void AVL::update_parent_child_ptr(Node* node, Node* ptr) {
    Node* parent = node->parent;
    if (parent == nullptr)
        root = ptr;
    else if (*node < *parent)
        parent->left = ptr;
    else
        parent->right = ptr;
}

// Allocate a node containing string s and add it to the tree under parent.
Node* AVL::insert_node(Node* parent, const std::string &s) {
    Node *new_node = new Node(s);
    new_node->parent = parent;
    update_parent_child_ptr(new_node, new_node);
    update_heights(new_node);
    tree_size++;

    return new_node;
}

// Returns the balance of a node, which is a height comparison of its children.
int AVL::get_balance(Node* node) const {
    if (node == nullptr)
        return 0;
    return get_height(node->left) - get_height(node->right);
}

// Perform a left rotation and return a pointer to the new root of the sub-tree.
Node* AVL::pivot_left(Node* old_pivot) {
    // Rotate
    Node* new_pivot = old_pivot->right;
    new_pivot->parent = old_pivot->parent;
    update_parent_child_ptr(old_pivot, new_pivot);

    old_pivot->right = new_pivot->left;
    if (old_pivot->right != nullptr)
        old_pivot->right->parent = old_pivot;
    old_pivot->parent = new_pivot;
    new_pivot->left = old_pivot;

    // Adjust height
    old_pivot->height = 1 + std::max(get_height(old_pivot->left),
                                     get_height(old_pivot->right));
    new_pivot->height = 1 + std::max(get_height(new_pivot->left),
                                     get_height(new_pivot->right));

    return new_pivot;
}

// Perform a right rotation and return a pointer to the new root of the sub-tree.
Node* AVL::pivot_right(Node* old_pivot)
{
    // Rotate
    Node* new_pivot = old_pivot->left;
    new_pivot->parent = old_pivot->parent;
    update_parent_child_ptr(old_pivot, new_pivot);

    old_pivot->left = new_pivot->right;
    if (old_pivot->left != nullptr)
        old_pivot->left->parent = old_pivot;
    old_pivot->parent = new_pivot;
    new_pivot->right = old_pivot;

    // Adjust height
    old_pivot->height = 1 + std::max(get_height(old_pivot->left),
                                     get_height(old_pivot->right));
    new_pivot->height = 1 + std::max(get_height(new_pivot->left), 
                                     get_height(new_pivot->right));

    return new_pivot;
}


// Restores the AVL properties of the tree by checking the balance of 
// the replacement and all nodes in the path to the root node.
void AVL::balance_after_insert(Node *new_node)
{
    Node *node = new_node->parent;
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
                pivot_left(node->left);
                node = pivot_right(node);
            }   
            else if (balance < -1 && *new_node < *(node->right))
            {   // Right left
                pivot_right(node->right);
                node = pivot_left(node);
            } 
            else if (balance < -1 && *new_node > *(node->right))
            {   // Right right
                node = pivot_left(node);
            }

            break;
        }

        node = node->parent;
    }

    update_heights(new_node);
}

// Add a node containing string s to the tree. Returns true if the node is
// added. If the string is already in the tree, returns false instead.
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

    Node* new_node = insert_node(parent, s);

    if (parent != nullptr)
        balance_after_insert(new_node);

    return true;
}

// Return a pointer to the node containing string s. If s is not in the tree,
// return a nullptr instead.
Node *AVL::find(const std::string &s) const {
    Node* node = root;
    while (node != nullptr){
        // Check if the node contains the string
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

// Return true if the tree contains a node with string s, false otherwise.
bool AVL::contains(const std::string &s) const {
    return find(s) != nullptr;
}

// Return the inorder successor node. If node is the last inorder tree node,
// return a nullptr instead.
Node* AVL::get_next(Node* node) {
    if (node->right == nullptr)
        return nullptr;

    node = node->right;
    while (node->left != nullptr)
        node = node->left;
    
    return node;
}

// Remove node from the tree. Returns a pointer to the node that takes the old
// node's place.
Node* AVL::remove_node(Node *node)
{
    Node* to_delete = node;

    // Choose deletion strategy based on children
    if (node->left == nullptr && node->right == nullptr) 
    {   // Delete leaf
        update_parent_child_ptr(node, nullptr);
        node = node->parent;
    } 
    else if (node->left != nullptr && node->right != nullptr) 
    {   // Delete node with both children
        Node* next = get_next(node);
        if (next->right == nullptr)
        {   // Next inorder node is leaf and can safely be swapped
            update_parent_child_ptr(node, next);
            update_parent_child_ptr(next, nullptr);
            next->parent = node->parent;
            next->left = node->left;
            next->right = node->right;
            if (next->left)
                next->left->parent = next;
            if (next->right)
                next->right->parent = next;
            node = next;
        }
        else
        {   // Next inorder node has child that connects to its grandparent
            update_parent_child_ptr(node, next);

            // Replace next inorder node with its right child
            update_parent_child_ptr(next, next->right);
            next->right->parent = next->parent;
            Node* to_update = next->right;

            // Replace deletion target with next inorder node
            next->parent = node->parent;
            next->left = node->left;
            next->right = node->right;
            if (next->left)
                next->left->parent = next;
            if (next->right)
                next->right->parent = next;
            update_heights(next->right);
        }
    } 
    else if (node->left != nullptr) 
    {   // Delete node with only left child
        node->left->parent = node->parent;
        update_parent_child_ptr(node, node->left);
        node = node->left;
    } 
    else if (node->right != nullptr) 
    {   // Delete node with only right child
        node->right->parent = node->parent;
        update_parent_child_ptr(node, node->right);
        node = node->left;
    }

    update_heights(node);
    
    delete to_delete;
    tree_size--;

    return node;
}

// Restores the AVL properties of the tree by checking the balance of 
// the replacement and all nodes in the path to the root node.
void AVL::balance_after_remove(Node *replacement_node)
{
    Node *node = replacement_node;
    while (node != nullptr)
    {   // Check all ancestor nodes
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
                    pivot_left(node->left);
                    node = pivot_right(node);
                }
            }
            else 
            {   // Right
                balance = get_balance(node->right);
                if (balance > 0) 
                {   // Right left
                    pivot_right(node->right);
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
    update_heights(replacement_node);
}

// Search and remove the node containing s. Returns true if the node is found
// and removed, or false otherwise.
bool AVL::remove(const std::string &s) {
    // Retrieve the node to be deleted
    Node* node = find(s);
    if (node == nullptr)
        return false;

    // Remove node and rebalance the tree if needed
    node = remove_node(node);
    if (node != nullptr)
        balance_after_remove(node);

    return true;
}

// Return a vector of all strings in the tree in-order.
std::vector<std::string> AVL::inorder() const {
    std::vector<std::string> v;
    inorder_helper(root, v);
    return v;
}

// Return a vector of pointers to all nodes in the tree in-order.
std::vector<Node*> AVL::inorder_nodes() const {
    std::vector<Node*> v;
    inorder_helper(root, v);
    return v;
}


// Return a vector of all strings in the tree pre-order.
std::vector<std::string> AVL::preorder() const {
    std::vector<std::string> v;
    preorder_helper(root, v);
    return v;
}

// Return a vector of pointers to all nodes in the tree pre-order.
std::vector<Node*> AVL::preorder_nodes() const {
    std::vector<Node*> v;
    preorder_helper(root, v);
    return v;
}

// Return a vector of all strings in the tree in post-order.
std::vector<std::string> AVL::postorder() const {
    std::vector<std::string> v;
    postorder_helper(root, v);
    return v;
}

// Return a vector of pointers to all nodes in the tree post-order.
std::vector<Node*> AVL::postorder_nodes() const {
    std::vector<Node*> v;
    postorder_helper(root, v);
    return v;
}

// Return the amount of nodes in the tree.
uint AVL::size() const {
    return tree_size;
}

bool AVL::is_empty() const {
    return tree_size == 0;
}

// Deallocate nodes and remove them from the tree.
void AVL::clear() {
    std::vector<Node*> v;
    postorder_helper(root, v);
    for (Node* n: v)
        remove_node(n);
}

// Prints the tree nodes in preorder, including parent, child and height info. 
void AVL::print(std::vector<Node*> v) const{
    for (Node* n: v) {
        std::string p = n->parent != nullptr ? n->parent->get() : "."; 
        std::string l = n->left != nullptr ? n->left->get() : "."; 
        std::string r = n->right != nullptr ? n->right->get() : "."; 
        std::cout << n->get() << "=" << p << "(" << l << n->height << r << ")" << std::endl;
    }
    std::cout << std::endl;
}