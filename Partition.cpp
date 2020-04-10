#include <iostream>
#include "MyLinkedList.hpp"

typedef MyLinkedListManager::LinkedList linked_list;
typedef MyLinkedListManager::Node node;

node partition(const linked_list&, const int&);

/**
 * Write code to partition a linked list around a value x, such that all nodes 
 * less than x come before all nodes greater than or equal to z. (IMPORTANT: The
 * partition element x can appear anywhere in the "right partition"; it does not
 * need to appear between the left and the right partitions. The additional
 * spacing the example below indicates the partition.) 
 * EXAMPLE: 
 * Input: 3 -> 5 -> 8 -> 5 -> 10 -> 2 -> 1 [partition = 5]
 * Output: 3 -> 1 -> 2    ->     10 -> 5 -> 5 -> 8
 */
int main() {
    linked_list ll = MyLinkedListManager::get_linked_list();
    std::cout << "Enter a partition value:" << std::endl;
    int partition_value;
    std::cin >> partition_value;
    node new_linked_list = partition(ll, partition_value);
}

node partition(const linked_list& ll, const int& partition_value) {

}