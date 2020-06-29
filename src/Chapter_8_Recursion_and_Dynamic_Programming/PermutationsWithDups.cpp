#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <unordered_map>

void permutations(std::unordered_map<char, int> map, std::string prefix, 
    int remaining, std::vector<std::string>& result) {
    if(remaining == 0) {
        result.push_back(prefix);
        return;
    }
    for(const auto &[key, val] : map) {
        int count = map[key];
        if(count > 0) {
            map[key] = count - 1;
            permutations(map, prefix + key, remaining - 1, result);
            map[key] = count;
        }
    }
}

std::unordered_map<char, int> build_freq_map(std::string str) {
    std::unordered_map<char, int> hash_table;
    for(int i = 0; i < str.size(); i++) {
        char el = str.at(i);
        hash_table[el] = (hash_table.find(el) == hash_table.end()) ? 1 : hash_table[el] + 1;
    }
    return hash_table;
}

std::vector<std::string> permutations(std::string str) {
    std::vector<std::string> result;
    std::unordered_map<char, int> map = build_freq_map(str);
    permutations(map, "", str.size(), result);
    return result;
}

void print_permutations(std::vector<std::string> permutations) {
    for(std::string permutation : permutations) {
        std::cout << permutation << '\n';
    }
}

/**
 * Write a method to compute all permutations of a string whose characters are 
 * not necessarily unique. The list of permutations should not have duplicates.
 */
int main() {
    std::string str;
    std::cout << "Enter a string of unique characters.\n";
    std::cin >> str;
    std::vector<std::string> result = permutations(str);
    print_permutations(result);
}
