#include <iostream>
#include <vector>
#include <unordered_map>

bool are_permutations(std::string&, std::string&);
bool are_permutations_hash_table(std::string&, std::string&);

/**
 * Given two strings, write a method to decide if one is a permutation of the other.
 */
int main() {

    std::string first, second;

    std::cout << "Enter first string:" << std::endl;
    std::cin >> first;

    std::cout << "Enter second string:" << std::endl;
    std::cin >> second;

    std::cout << first << " and " << second << " are " << 
    (are_permutations(first, second) ? "" : "not ") << 
    "permutation of each other. Checked using merge sort." << std::endl;

    std::cout << first << " and " << second << " are " << 
    (are_permutations_hash_table(first, second) ? "" : "not ") << 
    "permutation of each other. Checked using hash table." << std::endl;

    return 0;
}

void merge(std::string& str, int left_index, int middle_index, int right_index) {
    const int size_left = middle_index - left_index + 1; // left part contains middle element
    const int size_right = right_index - middle_index;

    std::string left_part = str.substr(left_index, size_left);
    std::string right_part = str.substr(middle_index + 1, size_right);

    int iter_left(0), iter_right(0), iter_orig(left_index);
    while (iter_left < size_left && iter_right < size_right)
    {
        if(left_part.at(iter_left) < right_part.at(iter_right)) {
            str[iter_orig] = left_part.at(iter_left);
            iter_left++;
        } else {
            str[iter_orig] = right_part.at(iter_right);
            iter_right++;
        }
        iter_orig++;
    }
    
    while(iter_left < size_left) {
        str[iter_orig] = left_part.at(iter_left);
        iter_left++;
        iter_orig++;
    }

    while(iter_right < size_right) {
        str[iter_orig] = right_part.at(iter_right);
        iter_right++;
        iter_orig++;
    }
}

void merge_sort(std::string& str, int left, int right) {
    if(left < right) {
        const int middle = left + (right - left) / 2;
        merge_sort(str, left, middle);
        merge_sort(str, middle + 1, right);
        merge(str, left, middle, right);
    }
}

// merge sort
void sort_string(std::string& str) {
    merge_sort(str, 0, str.size() - 1);
}

bool are_permutations(std::string& first, std::string& second) {
    if(first.size() != second.size()) return false;

    sort_string(first); // O(nlogn)
    sort_string(second);

    // O(n)
    for(int i = 0; i < first.size(); i++) {
        if(first[i] != second[i]) 
            return false;
    }
    return true;
}

// hash table: key = letter, value = number of occurences
void insert_in_hash_table(const std::string& str, std::unordered_map<char, int>& ht) {
    for(int i = 0; i < str.size(); i++) {
        ht[str[i]]++;
    }
} 

bool are_permutations_hash_table(std::string& first, std::string& second) {
    if(first.size() != second.size()) {
        return false;
    }

    std::unordered_map<char, int> ht1, ht2;
    insert_in_hash_table(first, ht1);
    insert_in_hash_table(second, ht2);

    for(const auto &[key, value] : ht1) {
        if(ht2[key] != value) {
            return false;
        }
    }
    
    return true;
}