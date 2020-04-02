#include <stdio.h>
#include <iostream>

bool check_uniqueness(const std::string&);
void sort_string(std::string&);
void quick_sort(std::string&, const int&, const int&);
int partition(std::string&, const int&, const int&);
inline void swap_letters(std::string&, const int&, const int&);

/**
 * Implement an algorithm to determine if a string has all unique 
 * characters. What if you cannot use additional data structures?
 */
int main() {

    std::cout << "Enter string:" << std::endl;
    std::string string_to_check;
    std::cin >> string_to_check;

    // sort letters in string
    sort_string(string_to_check);
    std::cout << string_to_check << std::endl;
    // print if string has all unique characters
    std::cout << "Characters are " << (check_uniqueness(string_to_check) ? "" : "not ") << "unique." << std::endl;
}

bool check_uniqueness(const std::string& string_to_check) {
    for(int i = 0; i < string_to_check.size() - 1; i++) {
        if(string_to_check[i] == string_to_check[i+1]) {
            return false;
        }
    }
    return true;
}

inline void swap_letters(std::string& str, const int& first, const int& second) {
    char tmp;
    tmp = str.at(first);
    str[first] = str.at(second);
    str[second] = tmp;
}

/**
 * This function uses last element as pivot and put
 * smaller elements to the left of pivot and greater 
 * elements to the right of pivot.
 */
int partition(std::string& str, const int& low, const int& high) {
    const int pivot = str.at(high);
    int i = low - 1;
    char tmp;
    for(int j = low; j <= high - 1; j++) {
        if(str.at(j) < pivot) {
            i++;
            swap_letters(str, i, j);
        }
    }
    swap_letters(str, i, high);
    return (i + 1);
}

void quick_sort(std::string& string_to_sort, const int& low, const int& high) {
    if(low < high) {
        int border = partition(string_to_sort, low, high);
        quick_sort(string_to_sort, low, border - 1);
        quick_sort(string_to_sort, border + 1, high);
    }
}

// use quick sort
void sort_string(std::string& string_to_sort) {
    quick_sort(string_to_sort, 0, string_to_sort.size() - 1);
}