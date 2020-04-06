#include <iostream>
#include <unordered_map>

bool perm_of_palin_using_hash_table(const std::string&);

/**
 * Given a string, write a function to check if it is a permutation of a palindrome.
 * A palindrome is a word or phrase that is the same forwards and backwards. A permutation
 * is a rearrangement of letters. The palindrome does not need to be limited to just 
 * dictionary words. You can ignore casing and non-letter characters.
 */
int main() {
    std::string str;
    std::cout << "Enter the string to check if it is a permutation of a palindrome: " << std::endl;
    std::getline(std::cin, str);

    std::cout << "Check using hash table: String " << str << " is " << 
        (perm_of_palin_using_hash_table(str) ? "" : "not ") <<
         "a permutation of a polindrome." << std::endl;
}

int get_value(const char& character) {
    if(character - 'a' >= 0 && character - 'z' <= 0) {
        return character - 'a';
    }
    return -1;
}

void fill_hash_table(std::unordered_map<int, int>& hash_table, const std::string& str) {
    for(const auto character : str) {
        int val = get_value(character);
        if(val == -1) continue;
        hash_table[val]++;
    }
}

int number_of_letters_that_occurred_odd_times(const std::unordered_map<int, int>& hash_table) {
    int counter = 0;
    for(const auto&[key, value] : hash_table) {
        if(value % 2 != 0) {
            counter++;
        }
    }
    return counter;
}

bool perm_of_palin_using_hash_table(const std::string& str) {
    std::unordered_map<int, int> hash_table;
    fill_hash_table(hash_table, str);
    return number_of_letters_that_occurred_odd_times(hash_table) <= 1;
}