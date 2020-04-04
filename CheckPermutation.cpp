#include <iostream>
#include <vector>

bool are_permutations(const std::string&, const std::string&);

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
    "permutation of each other" << std::endl;

    return 0;
}

void merge(std::string str, int left, int middle, int right) {

}

void merge_sort(std::string& str, const int& left, const int& right) {
    if(left < right) {
        const int middle = (left + right) / 2;
        merge_sort(str, left, middle);
        merge_sort(str, middle + 1, right);
        merge(str, left, middle, right);
    }
}

// merge sort
void sort_string(std::string& str) {
    merge_sort(str, 0, str.size());
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