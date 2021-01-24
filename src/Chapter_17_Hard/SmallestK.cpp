#include <iostream>
#include <vector>
#include <algorithm>
#include "heap/MaxHeap.hpp"

// O(nlogn)
std::vector<int> smallest_sort(std::vector<int> elements, const int k)
{
    std::sort(elements.begin(), elements.end());
    return std::vector<int>(elements.begin(), elements.begin() + k);
}

std::vector<int> smallest_max_heap(std::vector<int> elements, const int k)
{
    // todo
    return elements;
}

std::vector<int> smallest_selection_rank1(std::vector<int> elements, const int k)
{
    // todo
    return elements;
}

std::vector<int> smallest_selection_rank2(std::vector<int> elements, const int k)
{
    // todo
    return elements;
}

/**
 * Smallest K : Design an algorithm to find the smallest K numbers in an array.
 */
int main()
{
    std::cout << "Enter 1 for approach using sorting, 2 for approach using max heap, 3 for selection rank algorithm\n"
    "(if elements are unique) or any other number for selection rank algorithm (if elements are not unique)\n";
    int method;
    std::cin >> method;
    std::cout << "Enter k:\n";
    int k;
    std::cin >> k;
    std::vector<int> elements = {8, 6, 17, 5, 1, 6, 12, 2};
    std::vector<int> smallest;
    if(method == 1)
    {
        smallest = smallest_sort(elements, k);
    }
    else if(method == 2)
    {
        smallest = smallest_max_heap(elements, k);
    }
    else if(method == 3)
    {
        smallest = smallest_selection_rank1(elements, k);
    }
    else
    {
        smallest = smallest_selection_rank2(elements, k);
    }
    std::cout << "Smallest k elements: ";
    for(int el : smallest) std::cout << el << ", ";
    std::cout << '\n';
}