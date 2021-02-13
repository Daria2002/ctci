#include <iostream>
#include <unordered_set>
#include <vector>
    
std::unordered_set<std::string> set_up_dict(std::vector<std::string> words)
{
    std::unordered_set<std::string> dict;
    for(std::string word : words) dict.emplace(word);
    return dict;
}

std::vector<std::string> words_one_away(std::string word)
{
    std::vector<std::string> words;
    for(int i = 0; i < word.size(); i++)
    {
        for(char c = 'A'; c <= 'Z'; c++)
        {
            std::string w = word.substr(0, i) + c + word.substr(i + 1);
            words.push_back(w);
        }
    }
    return words;
}

std::vector<std::string> transform(std::unordered_set<std::string> visited, std::string start, 
std::string end, std::unordered_set<std::string> dict)
{
    std::vector<std::string> path;
    if(start == end)
    {
        path.push_back(start);
        return path;
    }
    else if(visited.find(start) != visited.end() || dict.find(start) == dict.end())
    {
        return path; // empty
    }
    visited.emplace(start);
    std::vector<std::string> words = words_one_away(start);
    for(std::string word : words)
    {
        std::vector<std::string> path = transform(visited, word, end, dict);
        if(!path.empty())
        {
            path.push_back(start);
            return path;
        }
    }
    return path;
}

std::vector<std::string> transform_bf(std::string start, std::string end, std::vector<std::string> words)
{
    std::unordered_set<std::string> dict = set_up_dict(words);
    std::unordered_set<std::string> visited;
    return transform(visited, start, end, dict);
}

std::vector<std::string> transform_optimized(std::string start, std::string end, std::vector<std::string> dict)
{
    std::vector<std::string> w;
    // todo
    return w;
}

std::vector<std::string> transform_optimal(std::string start, std::string end, std::vector<std::string> dict)
{
    std::vector<std::string> w;
    // todo
    return w;
}

/**
 * Given two words of equal length that are in a dictionary, write a method to tranfsorm one word into another word
 * by changing only one letter at a time. The new word you get in each step must be in the dictionary.
 * EXAMPLE
 * Input: DAMP, LIKE
 * Output: DAMP -> LAMP -> LIMP -> LIME -> LIKE
 */
int main()
{
    std::cout << "Enter 1 to solve using bf approach, 2 to solve using optimized approach or any other number\n"
    "to solve using optimized approach:\n";
    int method;
    std::cin >> method;
    const std::string start = "DAMP";
    const std::string end = "LIKE";
    std::vector<std::string> dict = {"DAMP", "LIKE", "LAMP", "LIMP", "LIME", "LIKE", "DOOR", "LOOK", "LEFT", "LIPS", "TAKE"};
    std::vector<std::string> result;
    if(method == 1)
    {
        result = transform_bf(start, end, dict);
    }
    else if(method == 2)
    {
        result = transform_optimized(start, end, dict);
    }
    else 
    {
        result = transform_optimal(start, end, dict);
    }
    for(int i = result.size() - 1; i >= 0; i--) std::cout << result[i] << (i == 0 ? "" : " -> ");
    std::cout << '\n';
}