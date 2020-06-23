#include <iostream>
#include <memory>
#include <array>

template<typename K, typename V>
class HashTable {
    public:
        class LinkedListNode {
            public:
                LinkedListNode(K k, V v) : key(k), val(v) {}
                K key;
                V val;
                std::weak_ptr<std::shared_ptr<LinkedListNode>> prev;
                std::weak_ptr<std::shared_ptr<LinkedListNode>> next;
        };
        static constexpr int size = 5;
        std::array<std::shared_ptr<LinkedListNode>, size> arr;
        // insert key and val and return old val
        V put(K key, V val) {
            std::shared_ptr<LinkedListNode> node = get_node_for_key(key);
            if(node != nullptr) { // node with given key already exist in hash table
                V old_val = node -> val;
                node -> val = val;
                return old_val;
            }
            node = std::make_shared<LinkedListNode>(key, val);
            int index = get_index_for_key(key); 
            if(arr[index] != nullptr) { // linked list for given index in hash table is not empty
                node -> next = arr[index];
                node -> next -> prev = node;
            }
            arr[index] = node;
            return nullptr;
        }
        // remove node for key and return value
        V remove(K key) {
            std::shared_ptr<LinkedListNode> node = get_node_for_key(key);
            if(node == nullptr) {
                return nullptr;
            }
            if(node -> prev != nullptr) {
                node -> prev -> next = node -> next;
            } else {
                int hash_key = get_index_for_key(key);
                arr[hash_key] = node->next;
            }
            if(node -> next == nullptr) {
                node -> next -> prev = node -> prev;
            }
        }
        std::shared_ptr<LinkedListNode> get_node_for_key(K key) {

        }
};

/**
 * Design and implement a hash table which uses chaining (linked lists)
 * to handle collisions.
 */
int main() {
    

}