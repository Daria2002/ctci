#include <iostream>
// #include <cctype>
// #include <cstdlib>
// #include <cstdio>

bool has_equal_letters_num(std::string str)
{
    int counter = 0;
    for(int i = 0; i < str.size(); i++)
    {
        counter += (isdigit(str[i]) ? 1 : -1);
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

std::string longest_substr_optimal(std::string str)
{
    // todo
    return "";
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