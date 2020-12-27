#include <iostream>
#include <cstdlib> // rand, srand
#include <ctime> // time
#include <unordered_map>

class LinkedListNode
{
    public:
        int key;
        std::string value;
        LinkedListNode(int k, std::string val) : key(k), value(val) {}
        LinkedListNode* next = nullptr;
        LinkedListNode* prev = nullptr;
};

class LRUCache
{
    public:
        int max_size;
        int linked_list_size = 0;
        LinkedListNode* head = nullptr;
        LinkedListNode* tail = nullptr;
        std::unordered_map<int, LinkedListNode*> map;

        LRUCache(int max) : max_size(max) {} 

        std::string getValue(int key)
        {
            if(map.find(key) != map.end())
            {
                return map[key]->value;
            }
            return "";
        }

        void removeFromLinkedList(LinkedListNode*& node)
        {
            // std::cout << "remove from ll\n";
            if(node == nullptr) 
            {
                // std::cout << "node == nullptr\n";
                return;
            }
            linked_list_size--;
            if(node->prev != nullptr) 
            {
                // std::cout << "node->prev != nullptr\n";
                node->prev->next = node->next;
            }
            if(node->next != nullptr) 
            {
                // std::cout << "node->next != nullptr\n";
                node->next->prev = node->prev;
            }
            if(tail != nullptr && node->key == tail->key)
            {
                // std::cout << "node == tail\n";
                tail = node->prev;
            }
            if(head != nullptr && node->key == head->key) 
            {
                // std::cout << "node == head\n";
                head = node->next;
            }
        }

        void insertAtFrontOfLinkedList(LinkedListNode* node)
        {
            if(tail != nullptr && (linked_list_size >= max_size))
            {
                removeKey(tail->key);
            }
            if(head == nullptr)
            {
                head = node;
                tail = node;
            }
            else 
            {
                head->prev = node;
                node->next = head;
                head = node;
                head->prev = nullptr;
            }
            linked_list_size++;
        }

        // remove from linked list and hash table
        void removeKey(int key)
        {
            if(auto node_iter = map.find(key); node_iter != map.end())
            { 
                LinkedListNode* node = map[key];
                removeFromLinkedList(node);
                map.erase(node_iter);
            }
        }

        void setKeyValue(int key, std::string value)
        {
            removeKey(key);
            LinkedListNode* node = new LinkedListNode(key, value);
            insertAtFrontOfLinkedList(node);
            map[key] = node;
        }
};

/**
 * LRU Cache: Design and build a "least recently used" cache, which evicts the least recently used item.
 * The cache should map from keys to values (allowing you to insert and retrieve a value associated with
 * a particular key) and be initialized with a max size. When it is full, it should evict the least
 * recently used item. You can assume the keys are integers and the values are strings.
 */
int main()
{
    srand(time(NULL));
    constexpr int max_size = 5;
    LRUCache cache(5);
    for(int i = 0; i < 10; i++)
    {
        int key = rand() % 5;
        std::cout << "\nll size = " << cache.linked_list_size << '\n';
        std::cout << "Key = " << key << '\n';
        if(std::string value = cache.getValue(key); value != "")
        {
            LinkedListNode* node = new LinkedListNode(key, value);
            cache.insertAtFrontOfLinkedList(node);
        }
        else
        {
            value += key + 'a';
            value += key + 'b';
            cache.setKeyValue(key, value);
        }  
    
        if(cache.head != nullptr && cache.tail != nullptr)
            std::cout << "head key = " << cache.head->key << ", tail key = " << cache.tail->key << '\n';
        else 
            std::cout << "sth == nullptr\n";
            
        std::cout << "Linked list: ";
        LinkedListNode* node = cache.head;
        while (node != nullptr)
        {
            std::cout << node->key << ", ";
            node = node->next;
        }

    }
    std::cout << "\nLinked list:\n";
    LinkedListNode* node = cache.head;
    while (node != nullptr)
    {
        std::cout << "key = " << node->key << ", val = " << node->value << '\n';
        node = node->next;
    }
    std::cout << "Map:\n";
    for(auto pair : cache.map)
    {
        std::cout << "(" << pair.first << ", " << pair.second->value << ")\n";
    }
}