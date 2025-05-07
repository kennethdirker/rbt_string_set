/*
 *  RedBlackTree.h
 *  Red-Black Tree header.
 * 
 *  Adjusted by Kenneth Dirker
 *  Originally written by Yassaman Ommi on 2018-11-27.
 */

#ifndef RedBlackTree_h
#define RedBlackTree_h

#include <iterator>
#include <cstddef>
#include <iostream>
#include <vector>
namespace rbt {
    enum Color { RED, BLACK };

    struct Node {
        const std::string data;
        Color color;
        Node* left;
        Node* right;
        Node* parent;

        explicit Node(const std::string &val) :
                    data(val), color(RED), left(nullptr),
                    right(nullptr), parent(nullptr) {}
    };

    /**
     * Red-Black tree: Self-balancing binary search tree
     */
    class RedBlackTree {
    private:
        Node* root;

        //  Left rotation
        void leftRotate(Node* x);

        //  Right rotation
        void rightRotate(Node* y);

        // Fix violations after inserting a node
        void fixInsert(Node* z);

        // Transplant function used in deletion
        void transplant(Node* u, Node* v);

        // Delete a node
        void deleteNode(Node* z);

        // Function to fix violations after deleting a node
        void fixDelete(Node* x);

        // Find the minimum node in a subtree
        Node* minimum(Node* node);

        // Recursive helper function to traverse the tree in-order
        void inorder_helper(Node* node, std::vector<rbt::Node*> &v) const;
        // void inorder_helper(Node* node, std::vector<std::string> &v) const;

        // Print the tree structure (in-order traversal)
        void printHelper(Node* root, int space);


    public:
        // Constructor
        RedBlackTree();

        // Insert a node
        bool insert(const std::string &value);

        // Search the tree for a string value and return the node containing it
        Node* find(const std::string &value) const;

        // Delete a node by value
        bool remove(const std::string &value);

        // Return a alphabetically ordered vector of the tree's strings.
        std::vector<rbt::Node*> inorder() const;

        // Print the tree structure
        void printTree();

    };
}
#endif