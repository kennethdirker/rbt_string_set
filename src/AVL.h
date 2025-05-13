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

        Node(std::string s) : s(s), parent(nullptr), left(nullptr), right(nullptr), height(1) {};
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

            void inorder_helper(Node* node, std::vector<std::string> &vec) const;
            void inorder_helper(Node *node, std::vector<Node *> &vec) const;
            void preorder_helper(Node *node, std::vector<std::string> &vec) const;
            void preorder_helper(Node *node, std::vector<Node *> &vec) const;
            void postorder_helper(Node *node, std::vector<std::string> &vec) const;
            void postorder_helper(Node *node, std::vector<Node *> &vec) const;
            uint get_height(Node *node) const;
            void update_heights(Node* node);
            void update_parent_child_ptr(Node* node, Node* ptr);
            Node* insert_node(Node* parent, const std::string &s);
            int get_balance(Node *node) const;
            Node* pivot_left(Node* pivot);
            Node* pivot_right(Node* pivot);
            void balance_after_insert(Node *node);
            Node* get_next(Node* node);
            Node* remove_node(Node* node);
            void balance_after_remove(Node *node);

        public:
            AVL() : root(nullptr), tree_size(0) {}
            ~AVL() { clear(); }
            std::vector<std::string> inorder() const;
            std::vector<Node*> inorder_nodes() const;
            std::vector<std::string> preorder() const;
            std::vector<Node*> preorder_nodes() const;
            std::vector<std::string> postorder() const;
            std::vector<Node*> postorder_nodes() const;
            bool insert(const std::string &s);
            Node* find(const std::string &s) const;
            bool contains(const std::string &s) const;
            bool remove(const std::string &s);
            uint size() const;
            bool is_empty() const;
            void clear();
            void print(std::vector<Node*> v) const;
    };




}

#endif




