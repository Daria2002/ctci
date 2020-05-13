#include <iostream>
#include <memory>
#include <vector>
#include <iterator>
#include <algorithm>
#include <list>

class Node {
    public:
        Node(int val) : value(val) {}
        Node(int val, int l, int r) : value(val), left(std::make_shared<Node>(l)), right(std::make_shared<Node>(r)) {}
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        // parent is weak ptr because there is a cycle if we use std::shared<ptr>
        // std::weak_ptr<Node> parent;
        int value;
};

using NodePtr = std::shared_ptr<Node>;

void create_tree(NodePtr& root) {
    root = std::make_shared<Node>(20, 25, 14);
    NodePtr tmp = root -> left;
    tmp -> left = std::make_shared<Node>(17);
    tmp -> left -> left = std::make_shared<Node>(16);
    tmp -> left -> left -> right = std::make_shared<Node>(15);
    tmp -> right = std::make_shared<Node>(5, 18, 3);
    tmp -> right -> left -> right = std::make_shared<Node>(1);
    tmp -> right -> right -> right = std::make_shared<Node>(21);
    tmp = tmp -> right -> right -> right;
    tmp -> left = std::make_shared<Node>(4, 19, 12);
    tmp = root -> right;
    tmp -> left = std::make_shared<Node>(13);
    tmp -> right = std::make_shared<Node>(27);
    tmp -> left -> right = std::make_shared<Node>(7);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::list<T>& v) {
    os << "[ ";
    std::copy(std::begin(v), std::end(v), std::ostream_iterator<T>(os, " "));
    os << "]";
    return os;
}

std::vector<std::list<int>> get_combinations(NodePtr root) {
    std::vector<std::list<int>> results;
    return results;
}

void print_combinations(std::vector<std::list<int>> v) {
    std::for_each(v.begin(), v.end(), [](std::list<int> el) { std::cout << el << '\n';});
}

/**
 * A binary search tree was created by traversing through an array from left to right
 * and inserting each element. Given a binary search tree with distinct elements, print
 * all possible arrays that could have led to this tree.
 * EXAMPLE:
 * Input: 
 *         2
 *       /  \
 *      1    3
 * Output: {2, 1, 3}, {2, 3, 1}
 */
int main() {
    NodePtr root;
    create_tree(root);
    std::vector<std::list<int>> results = get_combinations(root);
    print_combinations(results);
}
