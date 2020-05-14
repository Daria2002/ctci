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
    root -> left -> left = std::make_shared<Node>(17);
    root -> left -> right = std::make_shared<Node>(12);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::list<T>& v) {
    os << "[ ";
    std::copy(std::begin(v), std::end(v), std::ostream_iterator<T>(os, " "));
    os << "]";
    return os;
}

void weave(std::list<int>& first, std::list<int>& second, std::vector<std::list<int>>& results, std::list<int> prefix) {
    if(first.empty() || second.empty()) {
        prefix.insert(prefix.end(), first.begin(), first.end());
        prefix.insert(prefix.end(), second.begin(), second.end());
        results.push_back(prefix);
        return;
    }
    int head = first.front();
    first.pop_front();
    prefix.push_back(head);
    weave(first, second, results, prefix);
    prefix.pop_back();
    first.push_front(head);
    head = second.front();
    second.pop_front();
    prefix.push_back(head);
    weave(first, second, results, prefix);
    prefix.pop_back();
    second.push_front(head);
}

void print_combinations(const std::vector<std::list<int>>& v) {
    std::for_each(v.begin(), v.end(), [](const std::list<int>& el) { std::cout << el << '\n';});
}

std::vector<std::list<int>> get_combinations(const NodePtr& root) {
    std::vector<std::list<int>> combinations;
    std::list<int> prefix;
    if(root == nullptr) {
        combinations.push_back(prefix);
        return combinations;
    }
    prefix.push_back(root -> value);
    std::vector<std::list<int>> left_combinations = get_combinations(root -> left);
    std::vector<std::list<int>> right_combinations = get_combinations(root -> right);
    std::vector<std::list<int>> weaved_combinations;
    for(std::list<int>& left_combination : left_combinations) {
        for(std::list<int>& right_combination : right_combinations) {
            weave(left_combination, right_combination, weaved_combinations, prefix);
            combinations.insert(combinations.end(), weaved_combinations.begin(), weaved_combinations.end());
            weaved_combinations.clear();
        }
    }
    return combinations;
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
