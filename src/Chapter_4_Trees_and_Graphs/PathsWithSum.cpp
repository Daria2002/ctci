#include <iostream>
#include <memory>
#include <unordered_map>

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
    node -> insert(4);
    node -> insert(-3);
    node -> insert(6);
    node -> insert(1);
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

void update_hash_table(std::unordered_map<int, int>& hash_table, int key, int delta) {
    if(hash_table.find(key) != hash_table.end()) {
        int old_val = hash_table[key];
        hash_table.insert({key, old_val + delta});
        return;
    }
    hash_table.insert({key, delta});
}

int get_value_or_default(std::unordered_map<int, int> path_count, int sum_to_search) {
    if(path_count.find(sum_to_search) == path_count.end()) {
        return 0;
    }
    return path_count[sum_to_search];
}

int count_paths_with_sum_optimized(NodePtr node, const int target_sum, int current_sum, std::unordered_map<int, int> path_count) {
    if(node == nullptr) {
        return 0;
    }
    current_sum += node -> value;
    int sum_to_search = current_sum - target_sum;
    int num_of_paths = get_value_or_default(path_count, sum_to_search);
    if(current_sum == target_sum) {
        num_of_paths++;
    }
    update_hash_table(path_count, current_sum, 1);
    num_of_paths += count_paths_with_sum_optimized(node -> left, target_sum, current_sum, path_count);
    num_of_paths += count_paths_with_sum_optimized(node -> right, target_sum, current_sum, path_count);
    // update_hash_table(path_count, current_sum, -1);
    return num_of_paths;
}

int count_paths_with_sum_optimized(NodePtr node, const int target_sum) {
    return count_paths_with_sum_optimized(node, target_sum, 0, std::unordered_map<int, int>());
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
    int sum, num_of_paths, method;
    std::cin >> sum;
    std::cout << "Enter 1 to calculate number of paths using brute force algorithm or "
                 "2 to calculate number of paths using optimized algorithm.\n";
    std::cin >> method;
    switch (method) {
    case 1:
        num_of_paths = count_paths_with_sum(tree.root, sum);
        break;
    case 2:
        num_of_paths = count_paths_with_sum_optimized(tree.root, sum);
        break;
    default:
        std::cout << "Non of the proposed methods have not been choosen.\n";
        return 0;
    }
    std::cout << "Number of paths = " << num_of_paths << '\n';
}
