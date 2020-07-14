#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

void sort(std::vector<std::string>& anagrams) {
    // kex - sorted word, value - all anagrams of key that occurred in anagrams vector
    std::unordered_map<std::string, std::vector<std::string>> map;
    for(std::string word : anagrams) {
        std::string unsorted_word = word;
        std::sort(word.begin(), word.end());
        std::vector<std::string> values;
        // word in already in a map
        if(map.find(word) != map.end()) {
            values = map[word];
        }
        values.push_back(unsorted_word);
        map[word] = values;
    }
    anagrams.clear();
    for(auto const& [key, val] : map) {
        anagrams.insert(anagrams.end(), val.begin(), val.end());
    }
}

/**
 * Write a method to sort an array of strings so that all the anagrams are next to each other.
 */
int main() {
    std::vector<std::string> anagrams = {"rat", "state", "save", "cider", "vase", "angel", "glean", "tar", "cried", "taste"};
    sort(anagrams);
    for(int i = 0; i < anagrams.size(); i++) {
        std::cout << anagrams[i] << '\n';
    }
}
