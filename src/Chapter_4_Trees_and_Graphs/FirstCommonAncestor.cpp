#include <iostream>
#include <memory>

class Node {
    public:
        Node() {}
        Node(int _value) : value(_value) {}
        Node(int _value, std::weak_ptr<Node> _parent) : value(_value), parent(_parent) {}
        std::shared_ptr<Node> right;
        std::shared_ptr<Node> left;
        std::weak_ptr<Node> parent;
        int value;
};

using NodePtr = std::shared_ptr<Node>;

void create_tree(NodePtr& root) {
    root = std::make_shared<Node>(20);
    root -> left = std::make_shared<Node>(25, root);
    root -> right = std::make_shared<Node>(14, root);
    NodePtr tmp;
    tmp = root -> left;
    tmp -> left = std::make_shared<Node>(17, tmp);
    tmp -> left -> left = std::make_shared<Node>(16, tmp -> left);
    tmp -> left -> left -> right = std::make_shared<Node>(15, tmp -> left -> left);
    tmp -> right = std::make_shared<Node>(5, tmp);
    tmp -> right -> left = std::make_shared<Node>(18, tmp -> right);
    tmp -> right -> left -> right = std::make_shared<Node>(1, tmp -> right -> left);
    tmp -> right -> right = std::make_shared<Node>(3, tmp -> right);
    tmp -> right -> right -> right = std::make_shared<Node>(21, tmp -> right -> right);
    tmp = tmp -> right -> right -> right;
    tmp -> left = std::make_shared<Node>(4, tmp);
    tmp -> left -> left = std::make_shared<Node>(19, tmp -> left);
    tmp -> left -> right = std::make_shared<Node>(12, tmp -> left);
    tmp = root -> right;
    tmp -> left = std::make_shared<Node>(13, tmp);
    tmp -> left -> right = std::make_shared<Node>(7, tmp -> left);
    tmp -> right = std::make_shared<Node>(27, tmp);
}

int depth(NodePtr node) {
    int depth = 0;
    while(node != nullptr) {
        node = (node -> parent).lock();
        depth++;
    }
    return depth;
}

void go_up_by_delta(NodePtr& node, int delta) {
    int old_val = node -> value;
    while (delta > 0 && node != nullptr) {
        node = (node -> parent).lock();
        delta--;
    }  
}

NodePtr fca_links_to_parents(NodePtr& successor1, NodePtr& successor2) {
    int depth_delta = depth(successor1) - depth(successor2);
    // first is deeper node, second is shellower node
    NodePtr first = (depth_delta > 0) ? successor1 : successor2;
    NodePtr second = (depth_delta > 0) ? successor2 : successor1;
    go_up_by_delta(first, std::abs(depth_delta));
    while(first != nullptr && second != nullptr && first != second) {
        first = (first -> parent).lock();
        second = (second -> parent).lock();
    }
    return ((first == nullptr || second == nullptr) ? nullptr : first);
}

bool get_node(const int value, NodePtr& root, NodePtr& node) {
    if(root == nullptr) {
        return false;
    }
    if(root -> value == value) {
        node = root;
        return true;
    }
    if(get_node(value, root -> left, node))
        return true;
    if(get_node(value, root -> right, node)) 
        return true;
    return false;
}

bool covers(NodePtr& root, NodePtr& node) {
    if(root == nullptr) return false;
    if(node == root) return true;
    return covers(root -> right, node) || covers(root -> left, node);
}

NodePtr get_sibiling(NodePtr& node) {
    if(node == nullptr || (node -> parent).lock() == nullptr) return nullptr;
    NodePtr parent = (node -> parent).lock();
    return (parent -> left == node ? parent -> right : parent -> left);
}

NodePtr fca_links_to_parents(NodePtr& root, NodePtr& successor1, NodePtr& successor2) {
    if(!covers(root, successor1) || !covers(root, successor2)) {
        return nullptr;
    } else if(covers(successor1, successor2)) {
        return successor1;
    } else if(covers(successor1, successor2)) {
        return successor2;
    }
    NodePtr parent = (successor1 -> parent).lock();
    NodePtr sibiling = get_sibiling(successor1);
    while (!covers(sibiling, successor2)) {
        sibiling = get_sibiling(parent);
        parent = (parent -> parent).lock();
    }
    return parent;
}

/**
 * Design an algorithm and write code to find the first common ancestor 
 * of two nodes in a binary tree. Avoid storing additional nodes in a data
 * structure.
 * NOTE: This is not necessarily a binary search tree.
 * ABBREVIATIONS:
 * fca - first common ancestor
 */
int main(int argc, char** argv) {
    std::cout << "=====================================\n"
                 "Program to find first common ancestor\n"
                 "=====================================\n";
    std::cout << "Enter method number for finding first common ancestor:\n";
    std::cout << "1 - With links to Parents\n";
    std::cout << "2 - With links to Parents - reaching all nodes in the first common ancestor subtree\n";
    std::cout << "3 - Without links to Parents\n";
    std::cout << "4 - Optimized\n";
    NodePtr root, fca;
    int method;
    create_tree(root);
    NodePtr first_successor, second_successor;
    get_node(4, root, first_successor);
    get_node(15, root, second_successor);
    std::cin >> method;
    switch (method) {
    case 1:
        fca = fca_links_to_parents(first_successor, second_successor);
        break;
    case 2:
        fca = fca_links_to_parents(root, first_successor, second_successor);
        break;
    case 3:
        // fca = fca_without_links_to_parents();
        break;
    case 4:
        // fca = fca_optimized();
        break;
    default:
        std::cout << "None of the provided methods have not been selected\n";
        break;
    }
    std::cout << "First common ancestor has value " << (fca -> value) << ".\n";
}
