#include <iostream>
#include <memory>

class TreeNode {
    public:     
        TreeNode() {};
        TreeNode(int val) : value(val) {}
        int value;
        std::shared_ptr<TreeNode> left;
        std::shared_ptr<TreeNode> right;
};

using NodePtr = std::shared_ptr<TreeNode>;

class BinarySearchTree {
    public:
        BinarySearchTree(NodePtr& r) : root(r) {}
        NodePtr root;
        void insert(int value) {

        }
        NodePtr find(int value) {

        }
        void delete_node(int value) {

        }
        NodePtr get_random_node() {

        }
};

/**
 * You are implementing a binary search tree class from scratch, which, in addition to 
 * insert, find, and delete, has a method getRandomNode() which returns a random node from
 * the tree. All nodes should be equally likely to be chosen. Design and implement an algorithm for
 * getRandomNode, and explain how you would implement the rest of the methods.
 */
int main() {

}
