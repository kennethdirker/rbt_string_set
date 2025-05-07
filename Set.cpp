#include "Set.h"

using namespace set;

/**
 *  Set constructor.
 */
Set::Set() {
    tree = rbt::RedBlackTree();
    set_size = 0;
}

/**
 *  Adds a string to the set if the set doesn't already contain an identical
 *  string.
 * 
 *  Returns:
 *      True if the string was inserted, false otherwise. 
 */
bool Set::add(const std::string &data) {
    bool ret = tree.insert(data);
    if (ret)
        set_size++;
    return ret;
}

/**
 *  Checks if a string is already present in the set.
 *  Returns:
 *      True if the set contains the string, false otherwise.
 */
bool Set::contains(const std::string &data) const {
    return tree.find(data) != nullptr;
}

/**
 *  Remove a string from the set if the set contains it. 
 *
 *  Returns:
 *      True if the string was removed, false otherwise.
 */
bool Set::remove(const std::string &data) {
    bool ret = tree.remove(data);
    if (ret)
        set_size--;
    return ret;
}

/**
 * Remove all elements from the set.
 */
void Set::clear() {
    for (auto elem: dump())
        remove(elem);
}

/**
 * Returns a vector containing the strings in alphabetical order.
 */
std::vector<std::string> Set::dump() const {
    std::vector<std::string> strings;
    std::vector<rbt::Node*> nodes = tree.inorder();
    for (rbt::Node* node: nodes)
        strings.push_back(node->data);
    return strings;
}

/**
 *  Check if two sets contain the same strings.
 * 
 *  Returns: 
 *      True if the sets are equivalent, false otherwise.
 */
bool Set::operator==(const Set &set) {
    if (size() != set.size())
        return false;

    // Dump produces ordered vector
    auto elements1 = dump();
    auto elements2 = set.dump();
    for (uint i = 0; i < set_size; i++)
        if (elements1[i].compare(elements2[i]) != 0)
            return false;
    return true;
}

/**
 * Returns the amount of elements in the set.
 */
uint Set::size() const {
    return set_size;
}

/**
 * Returns whether the set is empty or not.
 */
bool Set::is_empty() const {
    return set_size == 0;
}

/**
 * Return a vector of in-order tree nodes.
 */
std::vector<rbt::Node*> Set::inorder() const {
    return tree.inorder();
}

/**
 * Set iterator implementation.
 */
Set::RBTIterator Set::iterator() const { return iterator(0); }
Set::RBTIterator Set::iterator(uint pos) const { return RBTIterator(*this, pos); }

Set::RBTIterator Set::begin() const { return iterator(0); }
Set::RBTIterator Set::end() const { return iterator(size()); }

Set::RBTIterator::RBTIterator(const Set &set, uint pos) : 
                            set(set), nodes(set.inorder()), pos(pos) {}
void Set::RBTIterator::next() { ++pos; }
bool Set::RBTIterator::operator==(const RBTIterator &rhs) const {
    return &set == &(rhs.set) && pos == rhs.pos;
}
bool Set::RBTIterator::operator!=(const RBTIterator &rhs) const {
    return !(&set == &rhs.set && pos == rhs.pos);
}