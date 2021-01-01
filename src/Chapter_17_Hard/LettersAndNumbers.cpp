#include <iostream>
#include <unordered_map>
#include <vector>

bool has_equal_letters_num(std::string str)
{
    int counter = 0;
    for(int i = 0; i < str.size(); i++)
    {
        counter += (isdigit(str[i]) ? -1 : 1);
    }
    return (counter == 0);
}

std::string longest_substr_bf(std::string str)
{
    for(int len = str.size(); len > 1; len--) // start with the longest size
    {
        for(int start = 0; start <= str.size() - len; start++)
        {
            if(has_equal_letters_num(str.substr(start, len)))
            {
                return str.substr(start, len);
            }
        }
    }
    return "";
}

std::vector<int> compute_delta(std::string str)
{
    int delta = 0;
    std::vector<int> deltas;
    for(int i = 0; i < str.size(); i++)
    {
        delta += (isdigit(str[i]) ? -1 : 1);
        deltas.push_back(delta);
    }
    return deltas;
}

std::pair<int, int> longest_match(std::vector<int> deltas)
{
    std::pair<int, int> max(0, 0);
    std::unordered_map<int, int> map;
    map[0] = -1;
    for(int i = 0; i < deltas.size(); i++)
    {
        if(map.find(deltas[i]) == map.end())
        {
            map[deltas[i]] = i;
        }
        else 
        {
            int first = map[deltas[i]];
            int span = i - first;
            int longest = max.second - max.first;
            if(span > longest)
            {
                max = std::make_pair(first, i);
            }
        }
    }
    return max; 
}

std::string longest_substr_optimal(std::string str)
{
    // compute deltas between count of number and count of letters
    std::vector<int> deltas = compute_delta(str);
    // find pair in deltas with matching values and largest span
    std::pair<int, int> span = longest_match(deltas);
    return str.substr(span.first + 1, span.second - span.first);
}

/**
 * Letters and Numbers: Given an array filled with letters and numbers, find the longest
 * subarray with an equal numbers of letters and numbers
 */
int main()
{
    std::cout << "Enter 1 to solve using brute force or any other number for optimal approach:\n";
    int method;
    std::cin >> method;
    std::string str = "ab34ab555";
    std::string substr = (method == 1 ? longest_substr_bf(str) : longest_substr_optimal(str));
    std::cout << "Longest substring of " << str << " with equal number of letters and numbers is " << substr << '\n';
}