#include <iostream>
#include <vector>
#include <numeric>

int sum(const std::vector<int>& v)
{
    return std::accumulate(v.begin(), v.end(), 0);
}

struct Target
{
    bool possible_to_swap;
    int value;
    int sum_diff;
};


Target target_value(const std::vector<int>& v1, const std::vector<int>& v2)
{
    int sum1 = sum(v1);
    int sum2 = sum(v2);
    Target target;
    target.sum_diff = sum2 - sum1;
    target.possible_to_swap = ((sum2 - sum1) % 2 == 0);
    target.value = (sum2 - sum1) / 2;
    return target;
}

std::vector<int> sum_swap_brute_force(const std::vector<int>& v1, const std::vector<int>& v2)
{
    Target target = target_value(v1, v2);
    if(!target.possible_to_swap) return {};
    int target_val = target.value;
    int sum_diff = target.sum_diff;
    std::cout << "target value = " << target_val << '\n';
    for(const int val1 : v1)
    {
        for(const int val2 : v2)
        {
            if(val1 + val2 == sum_diff && val2 - val1 == target_val) return {val1, val2};
        }
    }
    return {};
}

std::vector<int> sum_swap_optimal(std::vector<int> v1, std::vector<int> v2)
{
    std::vector<int> swap_values;
    // todo
    return swap_values;
}

std::vector<int> sum_swap_alternate(std::vector<int> v1, std::vector<int> v2)
{
    std::vector<int> swap_values;
    // todo
    return swap_values;
}

/**
 * Sum Swap: Given two arrays of integers, find a pair of values (one value from
 * each array) that you can swap to give the two arrays the same sum.
 * EXAMPLE:
 * Input: {4, 1, 2, 1, 1, 2} and {3, 6, 3, 3}
 * Output: {1, 3}
 */
int main()
{
    int method;
    std::cout << "Enter 1 to solve using brute force approach, 2 to solve using\n"
    "optimal approach and any other number to solve using alternate approach:\n";
    std::cin >> method;
    std::vector<int> v1 = {4, 1, 2, 1, 1, 2};
    std::vector<int> v2 = {3, 6, 3, 3};
    std::vector<int> swap_values;
    switch (method)
    {
    case 1:
        swap_values = sum_swap_brute_force(v1, v2);
        break;
    case 2:
        swap_values = sum_swap_optimal(v1, v2);
        break;
    default:
        swap_values = sum_swap_alternate(v1, v2);
        break;
    }
    if(swap_values.size() > 0)
        std::cout << "Swap values = " << swap_values[0] << ", " << swap_values[1] << '\n';
    else
        std::cout << "There is no pair to swap.\n";
}