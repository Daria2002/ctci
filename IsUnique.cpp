#include <stdio.h>
#include <iostream>

bool check_uniqueness(const std::string&);
void sort_string(std::string&);

/*
 * Implement an algorithm to determine if a string has all unique 
 * characters. What if you cannot use additional data structures?
 */
int main() {

    std::cout << "Enter string:" << std::endl;
    std::string string_to_check;
    std::cin >> string_to_check;

    // sort letters in string
    sort_string(string_to_check);
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

// use quick sort
void sort_string(std::string& string_to_sort) {
    
}