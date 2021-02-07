#include <iostream>
#include <vector>
#include <algorithm>

int missing_number(const std::vector<int>& elements)
{
    long long actual_sum = 0; // sum is long long because it might be very large number
    std::for_each(elements.begin(), elements.end(), [&](auto el) { actual_sum += el; });
    int n = elements[elements.size() - 1];
    long long full_sum = n * (n + 1) / 2;
    return full_sum - actual_sum;
}

std::pair<int, int> missing_numbers(const std::vector<int>& elements)
{
    std::pair<int, int> missing = std::make_pair(-1, -1);
    // todo
    return missing;
}

/**
 * Missing Two: You are given an array with all the numbers from 1 to N appearing exactly once, except for one number
 * that is missing. How can you find the missing number in O(N) time and O(1) space? What if there were two numbers missing?
 */
int main()
{
    std::cout << "Enter 1 to find 1 missing num or any other number to find 2 missing numbers:\n";
    int method;
    std::cin >> method;
    if(method == 1)
    {
        std::vector<int> elements = {1, 2, 3, 5, 6, 7, 8, 9, 10};
        std::cout << "Missing number is " << missing_number(elements) << ".\n";
    }
    else 
    {
        std::vector<int> elements = {1, 2, 3, 5, 6, 7, 8, 10};
        std::pair<int, int> missing = missing_numbers(elements);
        std::cout << "Missing numbers are " << missing.first << ", " << missing.second << '\n';
    }
}