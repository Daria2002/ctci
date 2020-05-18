#include <iostream>
#include <memory>
#include <stdlib.h>
#include <time.h>

class TreeNode : public std::enable_shared_from_this<TreeNode> { // public inheritance!!
    public:     
        TreeNode() {};
        TreeNode(int val) : value(val) {}
        int value;
        int size;
        std::shared_ptr<TreeNode> left;
        std::shared_ptr<TreeNode> right;
        // ask where to put duplicates (on left or right)
        void insert(int val) {
            if(val <= value) {
                if(left == nullptr) {
                    left = std::make_shared<TreeNode>(val);
                } else {
                    left -> insert(val);
                }
            } else {
                if(right == nullptr) {
                    right = std::make_shared<TreeNode>(val);
                } else {
                    right -> insert(val);
                }
            }
            size++;
        }
        std::shared_ptr<TreeNode> find(int val) {
            if(val == value) {
                return shared_from_this();
            }
            if(val < value) {
                return left == nullptr ? nullptr : left -> find(val);
            } else {
                return right == nullptr ? nullptr : right -> find(val);
            }
        }
        void delete_node(int val) {
            if(left != nullptr && left -> value == val) {
                left = nullptr;
            } else if(right != nullptr && right -> value == val) {
                right = nullptr;
            }
            if(left != nullptr && left -> value < val) {
                left -> delete_node(val);
            } else if(right != nullptr) {
                right -> delete_node(val);
            }
            size--;
        }
        std::shared_ptr<TreeNode> get_random_node() {
            int left_size = left == nullptr ? 0 : left -> size;
            // initialize random seed
            srand(time(NULL));
            // generate random number in range [0, size]
            int random_number = rand() % size;
            if(random_number < left_size) {
                return left -> get_random_node();
            } else if(random_number == left_size) {
                return shared_from_this();
            }
            // return right node
            return right -> get_random_node();
        }
        std::shared_ptr<TreeNode> ith_node(int index) {
            int left_size = left == nullptr ? 0 : left -> size;
            if(index < left_size) {
                return left -> ith_node(index);
            } else if(index == left_size) {
                return shared_from_this();
            }
            return right -> ith_node(index - (left_size + 1));
        }
};

using NodePtr = std::shared_ptr<TreeNode>;

class Tree {
    public:
        NodePtr root = nullptr;
        int size() {
            return root == nullptr ? 0 : root -> size;
        }
        void insert(int val) {
            if(root == nullptr) {
                root = std::make_shared<TreeNode>(val);
            } else {
                root -> insert(val);
            }
        }
        NodePtr find(int val) {
            if(root == nullptr) {
                return nullptr;
            }
            return root -> find(val);
        }
        void delete_node(int val) {
            if(root == nullptr) {
                return;
            }
            return root -> delete_node(val);
        }
        std::shared_ptr<TreeNode> get_random_node() {
            if(root == nullptr) {
                return nullptr;
            }
            srand(time(NULL));
            int random_number = rand() % size();
            return root -> ith_node(random_number);
        }
};

void create_tree(NodePtr& node) {
    node = std::make_shared<TreeNode>(150);
    node -> insert(2);
    node -> insert(20);
    node -> insert(15);
    node -> insert(45);
    node -> insert(210);
    node -> insert(310);
    node -> insert(49);
    node -> insert(200);
    node -> insert(300);
    node -> insert(46);
    node -> insert(5000);
    node -> insert(100);
    node -> insert(1000);
    node -> insert(3);
    NodePtr found_node = node -> find(2);
    std::cout << "found node = " << found_node -> value << '\n';
    node -> delete_node(3); // used for testing delete_node_functionality
}

/**
 * You are implementing a binary search tree class from scratch, which, in addition to 
 * insert, find, and delete, has a method getRandomNode() which returns a random node from
 * the tree. All nodes should be equally likely to be chosen. Design and implement an algorithm for
 * getRandomNode, and explain how you would implement the rest of the methods.
 */
int main() {
    NodePtr node;
    create_tree(node);
    NodePtr random_node = node -> get_random_node();
    std::cout << "Method 1: random node value = " << random_node -> value << '\n';
    Tree tree;
    tree.root = node;
    random_node = tree.get_random_node();
    std::cout << "Method 2: random node value = " << random_node -> value << '\n';
}
