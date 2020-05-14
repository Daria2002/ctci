#include <iostream>
#include <memory>

class Node {
    public:
        Node() {}
        Node(int val) : value(val) {}
        Node(int val, std::shared_ptr<Node> l, std::shared_ptr<Node> r) : value(val), left(l), right(r) {}
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        int value;
};

using NodePtr = std::shared_ptr<Node>;

void create_bigger_tree(NodePtr& root) {

}

void create_smaller_nonsubtree(NodePtr& root) {
    
}

void create_smaller_subtree(NodePtr& root) {
    
}

bool is_subtree(NodePtr root1, NodePtr root2) {
    if(root1 == nullptr || root2 == nullptr) {
        return false;
    }
    if(root1 != root2) {
        return is_subtree(root1 -> left, root2) || is_subtree(root1 -> right, root2);
    }
    return is_subtree(root1 -> left, root2 -> left) && is_subtree(root1 -> right, root2 -> right);
}

/**
 * T1 and T2 are two very large binary trees, with T1 much bigger than T2. Create an
 * algorithm to determine if T2 is a subtree of T1. A tree T2 is a subtree if T1 if
 * there exists a node n in T1 such that the subtree of n is identical to T2. That is,
 * if you cut off the tree at node n, the two trees would be identical.
 */
int main() {
    NodePtr t1;
    NodePtr t2;
    create_bigger_tree(t1);
    create_smaller_nonsubtree(t2);
    // create_smaller_subtree(t2);
    std::cout << "T2 is " << (is_subtree(t1, t2) ? "" : "not ") << "a subtree of T1.\n";
}
