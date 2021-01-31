#include <iostream>
#include <unordered_map>
#include <vector>

inline bool is_substr_at_index(std::string big, std::string small, int index)
{
    return (big.substr(index, small.size()) == small);
}

std::vector<int> get_indices(std::string str, std::string word)
{
    std::vector<int> indices;
    for(int index = 0; index < str.size() - word.size() + 1; index++)
    {
        if(is_substr_at_index(str, word, index)) indices.push_back(index);
    }
    return indices;
}

std::unordered_map<std::string, std::vector<int>> multi_search1(std::string big_word, std::vector<std::string> small_words)
{
    std::unordered_map<std::string, std::vector<int>> map;
    for(std::string small_word : small_words) map[small_word] = get_indices(big_word, small_word);
    return map;
}

std::unordered_map<std::string, std::vector<int>> multi_search2(std::string str, std::vector<std::string> small_words)
{
    std::unordered_map<std::string, std::vector<int>> map;
    // todo
    return map;
}

std::unordered_map<std::string, std::vector<int>> multi_search3(std::string str, std::vector<std::string> small_words)
{
    std::unordered_map<std::string, std::vector<int>> map;
    // todo
    return map;
}

/**
 * Multi Search: Given a string b and an array of smaller strings T, design a method to search
 * b for each small string in T. Return a mapping of each string to a list of its locations.
 */
int main()
{
    int method;
    std::cout << "Enter 1 for solution #1, 2 for solution #2 or any other number for solution #3:\n";
    std::cin >> method;
    std::string str = "mississippi";
    std::vector<std::string> small_words = {"is", "ppi", "hi", "sis", "i", "ssippi"};
    std::unordered_map<std::string, std::vector<int>> str_location;
    if(method == 1)
    {
        str_location = multi_search1(str, small_words);
    }
    else if(method == 2)
    {
        str_location = multi_search2(str, small_words);
    }
    else
    {
        str_location = multi_search3(str, small_words);
    }
    for(auto pair : str_location) 
    {
        std::cout << pair.first << ": ";
        std::vector<int> indices = pair.second;
        for(int index : indices) std::cout << index << ", ";
    }
    std::cout << '\n';
}