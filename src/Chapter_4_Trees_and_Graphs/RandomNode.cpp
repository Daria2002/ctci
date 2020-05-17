#include <iostream>
#include <memory>

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
            // TODO
            return shared_from_this();
        }
};

using NodePtr = std::shared_ptr<TreeNode>;

/**
 * You are implementing a binary search tree class from scratch, which, in addition to 
 * insert, find, and delete, has a method getRandomNode() which returns a random node from
 * the tree. All nodes should be equally likely to be chosen. Design and implement an algorithm for
 * getRandomNode, and explain how you would implement the rest of the methods.
 */
int main() {
    NodePtr node = std::make_shared<TreeNode>(1);
    node -> insert(2);
    node -> insert(3);
    NodePtr node2 = node -> find(2);
    node -> delete_node(3);
}
