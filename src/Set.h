#ifndef SET_H
#define SET_H

#include <iostream>
#include <vector>
#include <stack>
// #include "RedBlackTree.h"
#include "AVL.h"

namespace set {
   class Set {
   private:
      avl::AVL tree; 
      // rbt::RedBlackTree tree; 
      uint set_size;

   public:
      class RBTIterator {
         private:
            const set::Set &set;
            const std::vector<avl::Node*> nodes;
            uint pos;
         public:
            RBTIterator(const set::Set &set, uint pos);
            void next();
            bool operator==(const RBTIterator &rhs) const;
            bool operator!=(const RBTIterator &rhs) const;
            std::string operator* () const { return nodes[pos]->get(); }
      };

      Set();
      bool add(const std::string &data);
      bool contains(const std::string &data) const;
      bool remove(const std::string &data);
      void clear();
      std::vector<std::string> dump() const;
      bool operator==(const Set &set);
      uint size() const;
      bool is_empty() const;
      std::vector<std::string> inorder() const;
      std::vector<avl::Node*> inorder_nodes() const;

      RBTIterator iterator() const;
      RBTIterator iterator(uint pos) const;
      RBTIterator begin() const;
      RBTIterator end() const;
   };
}

#endif