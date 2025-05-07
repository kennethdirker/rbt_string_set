#include <iostream>
#include "Set.h"

/**
* The main function
*/
int main() {
    // create your set
    set::Set set1 = set::Set();

    // add some data
    set1.add(std::string("Some data"));


    // check some data
    std::cout << (set1.contains(std::string("Some data")) ? "yes" : "no") << std::endl;
    std::cout << (set1.contains(std::string("some data")) ? "yes" : "no") << std::endl;


    // remove some data
    std::cout << (set1.remove(std::string("Some data")) ? "contained" : "did not contain") << std::endl;
    std::cout << (set1.remove(std::string("some data")) ? "contained" : "did not contain") << std::endl;
    

    // Check equality
    set::Set set2 = set::Set();
    std::cout << "sets are " << (set1 == set2 ? "equal" : "unequal") << std::endl;
   
    set1.add(std::string("More data"));
    std::cout << "sets are " << (set1 == set2 ? "equal" : "unequal") << std::endl;
  
    set2.add(std::string("More data"));
    std::cout << "sets are " << (set1 == set2 ? "equal" : "unequal") << std::endl;
     
    // Out of order addition
    set1.add(std::string("Even more data"));
    std::cout << "sets are " << (set1 == set2 ? "equal" : "unequal") << std::endl;
  
    set2.add(std::string("Much more data"));
    std::cout << "sets are " << (set1 == set2 ? "equal" : "unequal") << std::endl;
     
    set1.add(std::string("Much more data"));
    std::cout << "sets are " << (set1 == set2 ? "equal" : "unequal") << std::endl;
  
    set2.add(std::string("Even more data"));
    std::cout << "sets are " << (set1 == set2 ? "equal" : "unequal") << std::endl;
  

    // set order
    std::cout << "set1 dump: ";
    for (auto s: set1.dump())
        std::cout << s << ", ";
    std::cout << std::endl;

    std::cout << "set2 dump: ";
    for (auto s: set2.dump())
        std::cout << s << ", ";
    std::cout << std::endl;


    // Iterator
    std::cout << "set1 it dump: ";
    for (auto it = set1.iterator(); it != set1.end(); it.next())
        std::cout << *it << ", ";
    std::cout << std::endl;
    
    std::cout << "set1 it dump: ";
    for (auto it = set1.iterator(1); it != set1.end(); it.next())
        std::cout << *it << ", ";
    std::cout << std::endl;


    // Clear set and check if it's empty
    std::cout << (set1.is_empty() ? "empty" : "not empty") << std::endl;
    set1.clear();
    std::cout << (set1.is_empty() ? "empty" : "not empty") << std::endl;


    
    // done
    return 0;
}
