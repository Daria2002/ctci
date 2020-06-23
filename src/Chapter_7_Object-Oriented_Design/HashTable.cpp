#include <iostream>
#include <memory>
#include <array>
#include <functional>
#include <cmath>

template<typename K, typename V>
class LinkedListNode : public std::enable_shared_from_this<LinkedListNode<K, V>> {
    public:
        LinkedListNode(K k, V v) : key(k), val(v) {}
        K key;
        V val;
        std::shared_ptr<LinkedListNode<K, V>> prev;
        std::shared_ptr<LinkedListNode<K, V>> next;
};

template<typename K, typename V>
class HashTable {
    public:
        static constexpr int size = 5;
        std::array<std::shared_ptr<LinkedListNode<K, V>>, size> arr;
        // return true if there was already some value, otherwise false
        bool put(K key, V val) {
            std::shared_ptr<LinkedListNode<K, V>> node = get_node_for_key(key);
            if(node != nullptr) { // node with given key already exist in hash table
                V old_val = node -> val;
                node -> val = val;
                return true;
            }
            node = std::make_shared<LinkedListNode<K, V>>(key, val);
            int index = hash_index(key); 
            if(arr[index] != nullptr) { // linked list for given index in hash table is not empty
                node -> next = arr[index];
                (node -> next) -> prev = node;
            }
            arr[index] = node;
            return false;
        }
        // remove node for key and return value
        bool remove(K key) {
            std::shared_ptr<LinkedListNode<K, V>> node = get_node_for_key(key);
            if(node == nullptr) {
                return false;
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
            return node -> val;
            return true;
        }
        std::shared_ptr<LinkedListNode<K, V>> get_node_for_key(K key) {
            std::shared_ptr<LinkedListNode<K, V>> node = arr[hash_index(key)];
            while (node != nullptr)
            {
                if(node -> key == key) {
                    return node;
                }
                node = (node -> next);
            }
            return node;
        }
        int hash_index(K key) {
            return std::hash<K>{}(key) % size;
        }
};

template<typename K, typename V>
std::ostream& operator<<(std::ostream& os, const HashTable<K, V>& ht) {
    for(int i = 0; i < ht.size; i++) {
        std::shared_ptr<LinkedListNode<K, V>> head = ht.arr[i];
        os << "Hash index = " << i << '\n';
        while(head != nullptr) {
            os << "key = " << head -> key << ", val = " << head -> val << '\n';
            head = (head -> next);
        }
    }
    return os;
}

/**
 * Design and implement a hash table which uses chaining (linked lists)
 * to handle collisions.
 */
int main() {
    HashTable<std::string, int> ht;
    ht.put("car", 3);
    ht.put("tree", 4);
    ht.put("board", 5);
    ht.put("sun", 3);
    ht.put("screen", 6);
    ht.put("afternoon", 9);
    ht.put("homework", 8);
    std::cout << ht << '\n';
}
