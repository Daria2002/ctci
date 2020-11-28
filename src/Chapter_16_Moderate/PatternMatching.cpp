#include <iostream>
#include <vector>
#include <string> // substr

std::string build_with_pattern(std::string pattern, std::string mainStr, std::string altStr) 
{
    std::string str = "";
    char first = pattern[0];
    for(char c : pattern) 
    {
        if(c == first) {
            str += mainStr;
        } else {
            str += altStr;
        }
    }
    return str;
}

/**
 * This brute force algorithm takes O(n^4) time
 */
bool is_match_brute_force(std::string pattern, std::string value)
{
    if(pattern.size() == 0) return value.size() == 0;
    int size = value.size();
    for(int mainSize = 0; mainSize < size; mainSize++) {
        // build string that is represented with letter a in pattern
        std::string mainStr = value.substr(0, mainSize + 1);
        // build string that is represented with letter b in pattern 
        for(int altStart = mainSize; altStart <= size; altStart++) {
            for(int altEnd = altStart; altEnd <= size; altEnd++) {
                std::string altStr = value.substr(altStart, altEnd - altStart + 1);
                if(value == build_with_pattern(pattern, mainStr, altStr)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool is_match_optimal(std::string pattern, std::string value)
{
    // todo
    return true;
}

bool is_match_optimal_alternate(std::string pattern, std::string value)
{
    // todo
    return true;
}

/**
 * Pattern Matching: You are given two strings, pattern and value. The pattern string consists of
 * just the letters a and b, describing a pattern within a string. For example, the string catcatgocatgo
 * matches the pattern aabab (where cat is a and go is b). It also matches patterns like a, ab, and b.
 * Write a method to determine if value matches pattern.
 */
int main() 
{
    std::vector<std::string> patterns = {"aabab", "a", "b", "ab", "abbab"};
    std::string value = "catcatgocatgo";
    bool match;
    std::cout << "Enter 1 to use brute force approach, 2 to use optimal approach and any other number to solve using\n"
    "alternate optimized approach:\n";
    int method;
    std::cin >> method;
    for(std::string pattern : patterns) 
    {
        if(method == 1) {
            match = is_match_brute_force(pattern, value);
        } else if(method == 2) {
            match = is_match_optimal(pattern, value);
        } else {
            match = is_match_optimal_alternate(pattern, value);
        }
        std::cout << "Pattern " << pattern << (match ? " " : " doesn't ") << "match value " << value << '\n';
    }
}