#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

std::vector<std::pair<int, int>> pairs_with_sum_bf(
const std::vector<int>& numbers, const int target_sum)
{
    std::vector<std::pair<int, int>> pairs;
    for(int i = 0; i < numbers.size(); i++)
    {
        for(int j = i + 1; j < numbers.size(); j++)
        {
            if(numbers[i] + numbers[j] == target_sum) 
            {
                pairs.push_back(std::make_pair(numbers[i], numbers[j]));
            }
        }
    }
    return pairs;
}

// use hash map and be careful when {6, 5, 5, -1, 10} and {6, 5, -1, 10}
std::vector<std::pair<int, int>> pairs_with_sum_optimized(
const std::vector<int>& numbers, const int target_sum)
{
    std::vector<std::pair<int, int>> pairs;
    std::unordered_map<int, int> unpaired_count;
    // initialize unpaired count
    for(int num : numbers) unpaired_count[num] = 0;
    for(int first : numbers)
    {
        int second = target_sum - first;
        if(unpaired_count[second] > 0)
        {
            pairs.push_back(std::make_pair(first, second));
            unpaired_count[second]--;
        }
        else
        {
            unpaired_count[first]++;
        }
    }
    return pairs;
}

std::vector<std::pair<int, int>> pairs_with_sum_alternate(
std::vector<int> numbers, const int target_sum)
{
    std::vector<std::pair<int, int>> pairs;
    std::sort(numbers.begin(), numbers.end());
    int first = 0;
    int last = numbers.size() - 1;
    while (first < last)
    {
        int sum = numbers[first] + numbers[last];
        if(sum == target_sum)
        {
            pairs.push_back(std::make_pair(numbers[first], numbers[last]));
            first++;
            last--;
        }
        else if(sum < target_sum)
        {
            first++;
        }
        else // sum > target sum
        {
            last--;
        }
    }
    return pairs;
}

/**
 * Pairs With Sum: Design an algorithm to find all pairs of integers within 
 * an array which sum to a specific value. 
 */
int main()
{
    std::cout << "Enter 1 to solve using brute force approach, 2 to solve using optimized approach,\n"
    "or any other number to solve using alternate approach:\n";
    int method;
    std::cin >> method;
    std::vector<std::pair<int, int>> pairs;
    std::vector<int> numbers = {2, 4, 1, 6, 5, 11, 5, -1, 10};
    constexpr int target_sum = 10;
    switch (method)
    {
    case 1:
        pairs = pairs_with_sum_bf(numbers, target_sum);
        break;
    case 2:
        pairs = pairs_with_sum_optimized(numbers, target_sum);
        break;
    default:
        pairs = pairs_with_sum_alternate(numbers, target_sum);
        break;
    }
    for(auto pair : pairs)
    {
        std::cout << "(" << pair.first << ", " << pair.second << ")\n";
    }
}