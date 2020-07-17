#include <iostream>

/**
 * Compare and contrast a hash table and an STL map. How is a hash table 
 * implemented? If the number of inputs is small, which data structure 
 * options can be used instead of a hash table? 
 */
int main() {
    std::cout << "Hash table insert and look up complexity: O(1)\n"
                 "STL map and binary search tree insert and look up complexity: O(log N)\n"
                 "Hash table is implemented as an array of linkedin lists where each node\n"
                 "holds two pieces of data: key and value. Array index is equal to\n"
                 "hashFunction(key). If different keys has a same hash function there could be\n"
                 "collision. That's the reason to store key and value in linked list node.\n"
                 "If the number of inputs is small we can use binary search tree and STL map\n"
                 "because even though they have O(log N) time complexity, the number of inputs\n"
                 "may be small enough to make this time negligible";
}
