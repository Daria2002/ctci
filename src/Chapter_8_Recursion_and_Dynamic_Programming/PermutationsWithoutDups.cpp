#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <vector>

void permutations2(std::string str, std::string prefix, const int size) {
    if(prefix.size() == size) {
        std::cout << prefix << '\n';
        return;
    }
    for(int i = 0; i < str.size(); i++) {
        prefix.push_back(str[i]);
        permutations2(str.substr(0, i) + str.substr(i + 1), prefix, size);
        prefix.pop_back();
    }
}

void permutations2(std::string str) {
    permutations2(str, "", str.size());
}

std::vector<std::string> permutations1(std::string str) {
    std::vector<std::string> permutations;
    if(str.empty()) {
        permutations.push_back("");
        return permutations;
    }
    char first = str[0];
    std::vector<std::string> words = permutations1(str.substr(1));
    for(std::string word : words) {
        for(int i = 0; i <= word.size(); i++) {
            permutations.push_back(word.substr(0, i) + first + word.substr(i));
        }
    }
    return permutations;
}

bool has_unique_characters(std::string str) {
    std::unordered_set<char> hash_table;
    for(int i = 0; i < str.size(); i++) {
        if(std::find(hash_table.begin(), hash_table.end(), str[i]) != hash_table.end()) {
            return false;
        }
        hash_table.insert(str[i]);
    }
    return true;
}

void print_permutations(std::vector<std::string> permutations) {
    for(std::string permutation : permutations) {
        std::cout << permutation << '\n';
    }
}

/**
 * Write a method to compute all permutations of a string of unique characters.
 */
int main() {
    std::string str;
    std::cout << "Enter a string of unique characters.\n";
    std::cin >> str;
    if(has_unique_characters(str)) {
        std::cout << "Enter 1 to generate permutations using approach 1: Building from permutations of first n-1 characters or\n"
        "any other number to use approach 2: Building from permutations of all n-1 character substrings.\n";
        int method;
        std::cin >> method;
        switch (method)
        {
        case 1:
            print_permutations(permutations1(str));
            break;
        default:
            permutations2(str);
            break;
        }
    } else {
        std::cout << str << " is not a string of unique characters.\n";
    }
}
