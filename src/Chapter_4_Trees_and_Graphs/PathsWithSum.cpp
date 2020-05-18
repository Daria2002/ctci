#include <iostream>
#include <memory>

class Node {
    public:
        Node() {}
        Node(int val) : value(val) {}
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        int value;
        void insert(int val) {
            if(val <= value) {
                if(left == nullptr) {
                    left = std::make_shared<Node>(val);
                } else {
                    left -> insert(val);
                }
            } else {
                if(right == nullptr) {
                    right = std::make_shared<Node>(val);
                } else {
                    right -> insert(val);
                }
            }
        }
};

using NodePtr = std::shared_ptr<Node>;

class Tree {
    public:
        Tree() = default;
        Tree(NodePtr r) : root(r) {}
        NodePtr root;
};

Tree create_tree() {
    NodePtr node = std::make_shared<Node>(150);
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
    return Tree(node);
}

int count_paths_with_sum_from_node(NodePtr node, int sum, int current_sum) {
    if(node == nullptr) return 0;
    current_sum += node -> value;
    int total_paths = 0;
    if(current_sum == sum) {
        total_paths++;
    }
    total_paths += count_paths_with_sum_from_node(node -> left, sum, current_sum);
    total_paths += count_paths_with_sum_from_node(node -> right, sum, current_sum);
    return total_paths;
}

int count_paths_with_sum(NodePtr node, int sum) {
    if(node == nullptr) {
        return 0;
    }
    int paths_from_root = count_paths_with_sum_from_node(node, sum, 0);
    int paths_on_left = count_paths_with_sum(node -> left, sum);
    int paths_on_right = count_paths_with_sum(node -> right, sum);
    return paths_from_root + paths_on_left + paths_on_right;
}

/**
 * You are given a binary tree in which each node contains an integer value (which
 * might be positive or negative). Design an algorithm to count the number of paths
 * that sum to a given value. The path does not need to start or end at the root or
 * a leaf, but it must go downwards (traveling only from parent nodes to child nodes).
 */
int main() {
    Tree tree = create_tree();
    std::cout << "===================================\n";
    std::cout << "Program for counting paths with sum\n";
    std::cout << "===================================\n";
    std::cout << "Enter sum:\n";
    int sum;
    std::cin >> sum;
    std::cout << "Number of paths = " << count_paths_with_sum(tree.root, sum) << '\n';
}
