
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

int main() {
    Checker c;
    std::vector<std::string> v, test;
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
    print(tree.inorder());
    c.check(tree.insert("a") == true); // 8
    print(tree.inorder());
    c.check(tree.insert("b") == true); // 9
    print(tree.inorder());
    c.check(tree.insert("c") == true);    // 10
    print(tree.inorder());
    c.check(tree.insert("d") == true);    // 11
    print(tree.inorder());
    c.check(tree.insert("e") == true); // 12
    print(tree.inorder());
    c.check(tree.insert("f") == true);    // 13
    print(tree.inorder());
    c.check(tree.insert("g") == true);    // 14
    print(tree.inorder());
    c.check(tree.insert("h") == true);      // 15
    print(tree.inorder());
    c.check((tree.size() == 9) == true); // 16
    print(tree.inorder());
    test = tree.inorder();
    c.check(equals(test, v) == true);   // 17
    c.check(tree.remove("p") == false); // 18
    test = tree.inorder();
    c.check(equals(test, v) == true);     // 19
    c.check(tree.contains("f") == true);  // 20
    c.check(tree.remove("f") == true);    // 21
    c.check(tree.contains("f") == false); //22
    test = tree.inorder(); 
    v.erase(v.begin() + 5); 
    c.check(equals(test, v) == true);     //23
    

    return 0;
}