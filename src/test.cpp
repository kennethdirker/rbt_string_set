
#include <vector>
#include <iostream>
#include "AVL.h"

using namespace avl;

class Checker {
    public:
    static inline int num = 1;

    void check(bool stat)
    {
        std::cout << "test(" << num++ << ") = " << (stat) << std::endl;
    }
};

bool equals(std::vector<std::string> &lhs, std::vector<std::string> &rhs) {
    if (lhs.size() != rhs.size())
        return false;
    for (uint i = 0; i < lhs.size(); i++)
        if (lhs[i] != rhs[i])
            return false;
    return true;
}

void print(std::vector<std::string> v) {
    for (std::string s: v)
        std::cout << s;
    std::cout << std::endl;
}

void print(std::vector<Node*> v) {
    for (Node* n: v) {
        std::string p = n->parent != nullptr ? n->parent->get() : "."; 
        std::string l = n->left != nullptr ? n->left->get() : "."; 
        std::string r = n->right != nullptr ? n->right->get() : "."; 
        std::cout << n->get() << "=" << p << "(" << l << n->height << r << ")" << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    Checker c;
    std::vector<std::string> v, test;

    // AVL tree = AVL();
    // tree.insert("h");
    // tree.insert("e");
    // tree.insert("l");
    // tree.insert("l");
    // tree.insert("o");
    // tree.insert("w");
    // tree.insert("o");
    // tree.insert("r");
    // tree.insert("l");
    // tree.insert("d");
    // print(tree.postorder_nodes());
    // tree.remove("h");
    // print(tree.postorder_nodes());
    // tree.remove("o");
    // tree.remove("d");
    // print(tree.postorder_nodes());


    v.push_back("a");
    v.push_back("b");
    v.push_back("c");
    v.push_back("d");
    v.push_back("e");
    v.push_back("f");
    v.push_back("g");
    v.push_back("h");
    v.push_back("k");
    AVL tree = AVL();
    c.check(tree.is_empty() == true);     //1
    c.check(tree.contains("k") == false); //2 
    c.check(tree.insert("k") == true);    //3
    c.check(tree.insert("k") == false);   //4
    c.check(tree.contains("k") == true);  //5
    c.check(tree.is_empty() == false);    //6
    c.check((tree.size() == 1) == true); // 7
    c.check(tree.insert("a") == true); // 8
    c.check(tree.insert("b") == true); // 9
    c.check(tree.insert("c") == true);    // 10
    c.check(tree.insert("d") == true);    // 11
    c.check(tree.insert("e") == true); // 12
    c.check(tree.insert("f") == true);    // 13
    c.check(tree.insert("g") == true);    // 14
    c.check(tree.insert("h") == true);      // 15
    c.check((tree.size() == 9) == true); // 16
    test = tree.inorder();
    c.check(equals(test, v) == true);   // 17
    c.check(tree.contains("p") == false); // 18
    c.check(tree.find("p") == nullptr); // 19
    c.check(tree.remove("p") == false); // 20
    test = tree.inorder();
    c.check(equals(test, v) == true);     // 21
    c.check(tree.contains("f") == true);  // 22
    c.check(tree.remove("f") == true);    // 23
    c.check(tree.contains("f") == false); //24
    test = tree.inorder(); 
    v.erase(v.begin() + 5); 
    c.check(equals(test, v) == true);     //25
    c.check(tree.remove("a") == true);  // 26
    c.check(tree.remove("b") == true);  // 27
    v.erase(v.begin());
    v.erase(v.begin());
    c.check(equals(test, v) == true);     // 28
    print(v);
    test = tree.inorder(); 
    print(test);
    c.check(tree.is_empty() == false); //39
    std::cout << tree.size() << std::endl;
    tree.clear();
    c.check(tree.is_empty() == true); //30
    std::cout << tree.size() << std::endl;
    print(tree.inorder());

    return 0;
}