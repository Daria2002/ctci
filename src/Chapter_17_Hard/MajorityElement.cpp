#include <iostream>
#include <vector>

bool is_majority_el(const std::vector<int>& elements, const int num)
{
    int count = 0;
    for(const int el : elements) if(el == num) count++;
    return count >= (elements.size() / 2);
}

// time: O(n^2), does not fit the time requirement
int majority_el_slow(const std::vector<int>& elements) 
{
    for(const int el : elements)
    {
        if(is_majority_el(elements, el)) return el;
    }
    return -1;
}

int majority_el_optimal(const std::vector<int>& elements)
{
    // todo
    return 0;
}

/**
 * Majority Element: A majority element is an element that makes up more than half of the items in
 * an array. Given a positive integers array, find majority element. If there is no majority element, 
 * return -1. Do this in O(N) time and O(1) space.
 * Input: 1 2 5 9 5 9 5 5 5
 * Output: 5
 */ 
int main()
{
    std::cout << "Enter 1 to for slow solution or any other number to solve using optimal approach:\n";
    int method;
    std::cin >> method;
    const std::vector<int> v = {1, 2, 5, 9, 5, 9, 5, 5, 5};
    const int majority_el = (method == 1 ? majority_el_slow(v) : majority_el_optimal(v));
    std::cout << "A majority element is " << (majority_el == -1 ? "not found" : std::to_string(majority_el)) << ".\n";
}