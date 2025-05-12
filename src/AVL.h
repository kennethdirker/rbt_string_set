#include <iostream>
#include <vector>

#ifndef AVL_H
#define AVL_H

namespace avl {

    class Node {
    private:
        const std::string s;

    public:
        Node *parent;
        Node *left;
        Node *right;
        short height;

        Node(std::string s) : s(s), parent(nullptr), left(nullptr), right(nullptr), height(0) {};
        bool operator==(const Node &rhs) const;
        bool operator!=(const Node &rhs) const;
        bool operator<(const Node &rhs) const;
        bool operator>(const Node &rhs) const;
        bool operator==(const std::string &rhs) const;
        bool operator!=(const std::string &rhs) const;
        bool operator<(const std::string &rhs) const;
        bool operator>(const std::string &rhs) const;
        std::string get() const;
    };

    class AVL {
        private:
            Node* root;
            uint tree_size = 0;

            void inorder_helper(Node* node, std::vector<std::string> &nodes) const;
            void inorder_helper(Node *node, std::vector<Node *> &nodes) const;
            void preorder_helper(Node *node, std::vector<std::string> &nodes) const;
            void preorder_helper(Node *node, std::vector<Node *> &nodes) const;
            void update_parent(Node* node, Node* ptr);
            void update_heights(Node* node);
            Node* insert_node(Node* parent, const std::string &s);
            Node* get_next(Node* node);
            Node* remove_node(Node* node);
            Node* pivot_left(Node* pivot);
            Node* pivot_right(Node* pivot);
            void balance_after_insert(Node *node);
            void balance_after_remove(Node *node);
            uint get_height(Node *node) const;
            int get_balance(Node *node) const;

        public:
            AVL() : root(nullptr), tree_size(0) {}
            ~AVL() { clear(); }
            bool insert(const std::string &s);
            Node* find(const std::string &s) const;
            bool contains(const std::string &s) const;
            bool remove(const std::string &s);
            std::vector<std::string> inorder() const;
            std::vector<std::string> preorder() const;
            uint size() const;
            bool is_empty() const;
            void clear();
    };




}

#endif




