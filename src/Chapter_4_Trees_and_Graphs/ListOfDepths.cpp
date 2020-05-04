#include <iostream>
#include <vector>
#include <memory>
#include "linked_list/MyLinkedList.hpp"

typedef MyLinkedListManager::Node Node;
typedef MyLinkedListManager::LinkedList Linked_list;

std::vector<int> get_values() {
    std::vector<int> v;
    std::string value;
    std::cout << "Enter values (enter non-number value to stop):\n";
    try {
        while(true) {
            std::cin >> value;
            v.push_back(std::stoi(value));
        }
    } catch(std::exception e) {
        std::cout << "Values are saved.\n";
    }

    return v;
}

class TreeNode {
    public:
        int _value;
        std::shared_ptr<TreeNode> left;
        std::shared_ptr<TreeNode> right;
        TreeNode() {}
        TreeNode(int value) : _value(value) {}
};


std::shared_ptr<TreeNode> create_binary_tree(const std::vector<int>& values, const int start, const int end) {
    if(start > end) {
        return nullptr;
    }
    int middle_index = start + (end - start) / 2;
    std::shared_ptr<TreeNode> root = std::make_shared<TreeNode>(values[middle_index]);
    root -> left = create_binary_tree(values, start, middle_index - 1);
    root -> right = create_binary_tree(values, middle_index + 1, end);
    return root;
}

void get_linked_lists(std::shared_ptr<TreeNode>& root, std::vector<Linked_list>& linked_lists, int index) {
    if(root == nullptr) {
        return;
    }
    linked_lists[index].append_node(root -> _value);
    index++;
    get_linked_lists(root -> right, linked_lists, index);
    get_linked_lists(root -> left, linked_lists, index);

    return;
}

std::shared_ptr<TreeNode> create_binary_tree(const std::vector<int>& values) {
    std::shared_ptr<TreeNode> root(create_binary_tree(values, 0, values.size() - 1));
    return root;
}

int get_depth(std::shared_ptr<TreeNode> root, int& depth) {
    if(root == nullptr) {
        return 0;
    }
    int tmp1 = get_depth(root -> left, depth);
    int tmp2 = get_depth(root -> right, depth);
    depth = ((tmp1 > tmp2) ? tmp1 : tmp2);
    depth++;
    return depth;
}

int get_depth(std::shared_ptr<TreeNode> root) {
    int depth = 0;
    get_depth(root, depth);
    return depth;
}

std::vector<Linked_list> initialize_linked_list(int size) {
    std::vector<Linked_list> linked_lists;
    for(int i = 0; i < size; i++) {
        Linked_list ll;
        linked_lists.push_back(ll);
    }
    return linked_lists;
}

std::vector<Linked_list> get_linked_lists(const std::vector<int>& values) {
    std::shared_ptr<TreeNode> root(create_binary_tree(values));
    int start = 0;
    int depth = get_depth(root);
    std::vector<Linked_list> linked_lists = initialize_linked_list(depth);
    get_linked_lists(root, linked_lists, start);
    return linked_lists;
}

void print_result(const std::vector<Linked_list>& lists) {
    for(int i = 0; i < lists.size(); i++) {
        std::cout << "list number " << i << ":\n";
        Node* tmp = lists[i].head;
        while (tmp != nullptr) {
            std::cout << tmp -> value << '\n';
            tmp = tmp -> next;
        }
        
    }
}

/**
 * Given a binary tree, design an algorithm which creates a linked list of all the nodes 
 * at each depth (e.g., if you have a tree with depth D, you'll have D linked lists).
 */
int main() {
    std::cout << "===============================================================\n"
                 "Program for creating linked list for every level of binary tree\n"
                 "===============================================================\n";
    std::vector<int> values = get_values();
    std::vector<Linked_list> lists = get_linked_lists(values);
    print_result(lists);
    return 0;
}