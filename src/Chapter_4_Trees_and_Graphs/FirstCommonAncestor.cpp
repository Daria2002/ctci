#include <iostream>
#include <memory>

class Node {
    public:
        Node() {}
        Node(int _value) : value(_value) {}
        std::shared_ptr<Node> right;
        std::shared_ptr<Node> left;
        std::weak_ptr<Node> parent;
        int value;
};

using NodePtr = std::shared_ptr<Node>;

// TODO: understand why you need to send by ref to change root and root->left
// it's a pointer and why sending it by value doesn't change root and root->left?
void create_tree(NodePtr& root) {
    root = std::make_shared<Node>(20);
    root -> left = std::make_shared<Node>(25);
}

std::shared_ptr<Node> fca_links_to_parents(NodePtr& root, NodePtr& successor1, NodePtr& successor2) {

}

void get_node(const int value, NodePtr& root, NodePtr& node) {

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
    if(argc < 2) {
        std::cout << "Please provide one argument that represents path to input file\n";
        return 0;
    }
    std::cout << "Enter method number for finding first common ancestor:\n";
    std::cout << "1 - With links to Parents\n";
    std::cout << "2 - With links to Parents - approved\n";
    std::cout << "3 - Without links to Parents\n";
    std::cout << "4 - Optimized\n";
    NodePtr root;
    NodePtr successor_node1;
    NodePtr successor_node2;
    NodePtr fca;
    int method, successor_name1, successor_name2;
    create_tree(root);
    std::cin >> method;
    std::cout << "Enter first successor value\n";
    std::cin >> successor_name1;
    std::cout << "Enter second successor value\n";
    std::cin >> successor_name2;
    get_node(successor_name1, root, successor_node1);
    get_node(successor_name2, root, successor_node2);
    switch (method) {
    case 1:
        fca = fca_links_to_parents(root, successor_node1, successor_node2);
        break;
    case 2:
        // fca = fca_links_to_parents_approved();
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
}