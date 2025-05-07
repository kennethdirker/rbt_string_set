#ifndef SET_H
#define SET_H

#include <iostream>
#include <vector>
#include <stack>
#include "RedBlackTree.h"

namespace set {
   class Set {
   private:
      rbt::RedBlackTree tree; 
      uint set_size;

   public:
      class RBTIterator {
         private:
            const set::Set &set;
            const std::vector<rbt::Node*> nodes;
            uint pos;
         public:
            RBTIterator(const set::Set &set, uint pos);
            void next();
            bool operator==(const RBTIterator &rhs) const;
            bool operator!=(const RBTIterator &rhs) const;
            std::string operator* () const { return nodes[pos]->data; }
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
      std::vector<rbt::Node*> inorder() const;

      RBTIterator iterator() const;
      RBTIterator iterator(uint pos) const;
      RBTIterator begin() const;
      RBTIterator end() const;
   };
}

#endif