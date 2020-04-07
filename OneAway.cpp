#include <iostream>

bool checkOneReplacementAway(const std::string&, const std::string&);
bool checkOneInsertAway(const std::string&, const std::string&);
bool checkOneEditAway(const std::string&, const std::string&);

/**
 * There are three types of edits that can be performed on strings: insert a character, 
 * remove a character, or replace a character. Given two strings, write a function to 
 * check if they are one edit (or zero edits) away.
 */
int main() {

    std::cout << "Enter first string: " << std::endl;
    std::string first, second;
    std::getline(std::cin, first);
    std::cout << "Enter second string: " << std::endl;
    std::getline(std::cin, second);
    std::cout << "Strings are "  << (checkOneEditAway(first, second) ? "" : "not ") <<
    "one edit away." << std::endl;
}

bool checkOneReplacementAway(const std::string& first, const std::string& second) {
    bool different = false;
    int second_index = 0, first_index = 0;
    while(first_index < first.size() && second_index < second.size()) {
        if(first[first_index] != second[second_index]) {
            if(different) {
                return false;
            }
            different = true;
        }
        second_index++;
        first_index++;
    }
    return true;
}

// first argument is longer
bool checkOneInsertAway(const std::string& first, const std::string& second) {
    bool different = false;
    int first_index = 0, second_index = 0;
    while(first_index < first.size() && second_index < second.size()) {
        if(first[first_index] != second[second_index]) {
            if(different) {
                return false;
            }
            different = true;
        } else {
            second_index++;
        }
        first_index++;
    }
    return true;
}

bool checkOneEditAway(const std::string& first, const std::string& second) {
    if(first.size() == second.size()) {
        return checkOneReplacementAway(first, second);
    } else if(first.size() - 1 == second.size()) {
        return checkOneInsertAway(first, second);
    } else if(first.size() + 1 == second.size()) {
        return checkOneInsertAway(second, first);
    }
    return false;
}
