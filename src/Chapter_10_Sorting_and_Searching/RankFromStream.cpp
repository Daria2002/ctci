#include <iostream>
#include <memory>

class RankNode {
    public:
        int left_size = 0;
        std::shared_ptr<RankNode> left, right;
        int data = 0;
        RankNode(int d) : data(d) {}
        // O(log N) on balanced tree, O(N) on unbalanced tree
        void insert(int d) {
            if(d <= data) {
                if(left != nullptr) left -> insert(d);
                else left = std::make_shared<RankNode>(d);
                left_size++;
            } else {
                if(right != nullptr) right -> insert(d);
                else right = std::make_shared<RankNode>(d);
            }
        }
        // O(log N) on balanced tree, O(N) on unbalanced tree
        int get_rank(int d) {
            if(d == data) return left_size;
            if(d < data) {
                if(left == nullptr) return -1;
                else return left -> get_rank(d);
            } else {
                int right_rank = (right == nullptr ? -1 : right -> get_rank(d));
                if(right_rank == -1) return -1;
                else return left_size + 1 + right -> get_rank(d);
            }
        }
};

/**
 * Imagine you are reading in a stream of integers. Periodically, you wish to be able
 * to look up the rank of a number x (the number of values less than or equal to x). Implement the data
 * structures and algorithms to support these operations. That is, implement the method track (int x), 
 * which is called when each number is generated, and the method getRankOfNumber(int x), which returns 
 * the number of values less than or equal to X (not including x itself).
 * EXAMPLE:
 * Stream(in order of appearance):5, 1, 4, 4, 5, 9, 7, 13, 3
 * getRankOfNumber(l) = 0
 * getRankOfNumber(3) = 1
 * getRankOfNumber(4) = 3 
 */
int main() {
    std::cout << "It's easy to implement this using array, but it's inefficient for inserting elements.\n"
                 "The second approach is to insert elements in a binary search tree instead of inserting\n"
                 "into an array. The method insert will run in O(log N), where N is the size of the tree.\n"
                 "To find the rank we can use in-order traversal, keeping a counter as we traverse. The goal\n"
                 "is that by the time we find x, counter will equal to the number of elements less than x.\n";
    RankNode rank_node(5);
    rank_node.insert(1);
    rank_node.insert(4);
    rank_node.insert(4);
    rank_node.insert(5);
    rank_node.insert(9);
    rank_node.insert(7);
    rank_node.insert(13);
    rank_node.insert(3);
    std::cout << "Rank of 1 = " << rank_node.get_rank(1) << '\n';
    std::cout << "Rank of 3 = " << rank_node.get_rank(3) << '\n';
    std::cout << "Rank of 4 = " << rank_node.get_rank(4) << '\n';
}
