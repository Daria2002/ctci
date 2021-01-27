#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

struct CompareString
{
    inline bool operator()(const std::string& first, const std::string& second) const
    {
        return first.size() > second.size();
    }
};


std::string longest_word(std::vector<std::string> words)
{
    std::unordered_map<std::string, bool> map; // easy lookup, O(1)
    for(std::string word : words) map[word] = true;
    std::sort(words.begin(), words.end(), CompareString());
    for(std::string word : words)
    {
        for(int i = 0; i < word.size(); i++)
        {
            std::string left = word.substr(0, i + 1);
            std::string right = word.substr(i + 1);
            if(map[left] && map[right]) return word;
        }
    }
    return "";
}

bool can_build_word(std::string word, bool is_original, std::unordered_map<std::string, bool> map) 
{
    if(map.count(word) && !is_original) return map[word];
    for(int i = 0; i < word.size(); i++)
    {
        std::string left = word.substr(0, i + 1);
        std::string right = word.substr(i + 1);
        if(map[left] && can_build_word(right, false, map)) return true;
    }
    map[word] = false;
    return false;
}

std::string longest_word_optimal(std::vector<std::string> words)
{
    std::unordered_map<std::string, bool> map;
    for(std::string word : words) map[word] = true;
    std::sort(words.begin(), words.end(), CompareString());
    for(std::string word : words)
    {
        if(can_build_word(word, true, map)) return word;
    }
    return "";
}

/**
 * Longest Word: Given a list of words, write a program to find the longest word made of other words
 * in the list.
 * EXAMPLE:
 * Input: cat, banana, dog, nana, walk, walker, dogwalker
 * Output: dogwalker
 */
int main()
{
    int method;
    std::cout << "Enter 1 to solve for approach where the longest word contains only of two other words from the list\n"
    "or any other number to solve using approach where the longest word contains any number of other words from the list:\n";
    std::cin >> method;
    std::vector<std::string> elements = {"cat", "banana", "dog", "nana", "walk", "walker", "dogwalker", "hitchhiking"};
    std::cout << "Longest word = " << (method == 1 ? longest_word(elements) : longest_word_optimal(elements)) << '\n';
}