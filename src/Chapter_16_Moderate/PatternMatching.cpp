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
    for(int mainSize = 0; mainSize < size; mainSize++) 
    {
        // build string that is represented with letter a in pattern
        std::string mainStr = value.substr(0, mainSize + 1);
        // build string that is represented with letter b in pattern 
        for(int altStart = mainSize; altStart <= size; altStart++) 
        {
            for(int altEnd = altStart; altEnd <= size; altEnd++) 
            {
                std::string altStr = value.substr(altStart, altEnd - altStart + 1);
                if(value == build_with_pattern(pattern, mainStr, altStr)) {
                    return true;
                }
            }
        }
    }
    return false;
}

int count_letter(std::string pattern, char c) 
{
    int count = 0;
    for(int i = 0; i < pattern.size(); i++) 
    {
        if(pattern[i] == c) count++;
    }
    return count;
}

bool is_match_optimal(std::string pattern, std::string value)
{
    if(pattern.size() == 0) return value.size() == 0;
    char main_char = pattern[0];
    char alt_char = main_char == 'a' ? 'b' : 'b';
    int size = value.size();
    int count_of_main = count_letter(pattern, main_char);
    int count_of_alt = count_letter(pattern, alt_char);
    int first_alt_index = pattern.find(alt_char);
    for(int main_size = 0; main_size <= size; main_size++)
    {
        int remaining_len = size - count_of_main * main_size;
        std::string main_str = value.substr(0, main_size);
        if(count_of_alt == 0 || remaining_len % count_of_alt == 0) 
        {
            int start_alt = first_alt_index * main_size;
            std::string alt_str = count_of_alt == 0 ? "" : value.substr(start_alt, remaining_len / count_of_alt);
            std::string cand = build_with_pattern(pattern, main_str, alt_str);
            if(cand == value) return true;
        }
    }
    return false;
}

bool is_equal(std::string s1, int offset1, int offset2, int size)
{
    for(int i = 0; i < size; i++)
    {
        if(s1[offset1 + i] != s1[offset2 + i])
        {
            return false;
        }
    }
    return true;
}

bool matches(std::string pattern, std::string value, int main_size, int alt_size, int alt_start_index)
{
    int offset2 = main_size;
    for(int i = 1; i < pattern.size(); i++) 
    {
        int size = pattern[i] == pattern[0] ? main_size : alt_size;
        int offset1 = pattern[i] == pattern[0] ? 0 : alt_start_index;
        if(!is_equal(value, offset1, offset2, size))
        {
            return false;
        }
        offset2 += size;
    }
    return true;
}

bool is_match_optimal_alternate(std::string pattern, std::string value)
{
    if(pattern.size() == 0) return value.size() == 0;
    char main_char = pattern[0];
    char alt_char = main_char == 'a' ? 'b' : 'a';
    int size = value.size();
    int count_main = count_letter(pattern, main_char);
    int count_alt = count_letter(pattern, alt_char);
    int first_alt_pattern = pattern.find(alt_char);
    int max_main_size = size / count_main;
    for(int main_size = 0; main_size <= max_main_size; main_size++)
    {
        int rem_len = size - main_size * count_main;
        if(count_alt == 0 || rem_len % count_alt == 0)
        {
            int alt_start_index = main_size * first_alt_pattern;
            int alt_size = count_alt == 0 ? 0 : rem_len / count_alt;
            if(matches(pattern, value, main_size, alt_size, alt_start_index)) return true;
        }
    }
    return false;
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