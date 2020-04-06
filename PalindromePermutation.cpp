#include <iostream>
#include <unordered_map>

bool perm_of_palin_using_hash_table(const std::string&);
bool alternate_perm_of_palin_using_hash_table(const std::string&);
bool is_perm_palindrome_using_bit_vector(const std::string&);

/**
 * Given a string, write a function to check if it is a permutation of a palindrome.
 * A palindrome is a word or phrase that is the same forwards and backwards. A permutation
 * is a rearrangement of letters. The palindrome does not need to be limited to just 
 * dictionary words. You can ignore casing and non-letter characters.
 */
int main() {
    std::string str;
    std::cout << "Enter the string to check if it's permutation is a palindrome: " << std::endl;
    std::getline(std::cin, str);

    std::cout << "Check if permutation is a palindrome using hash table: String " << str << " have " << 
        (perm_of_palin_using_hash_table(str) ? "" : "not ") <<
         "got a permutation that is a polindrome." << std::endl;

    std::cout << "Check if permutation is a palindrome using alternate hash table: String " << str << " have " << 
        (alternate_perm_of_palin_using_hash_table(str) ? "" : "not ") <<
         "got a permutation that is a polindrome." << std::endl;

    std::cout << "Check if permutation is a palindrome using bit vector: String " << str << " have " << 
        (is_perm_palindrome_using_bit_vector(str) ? "" : "not ") <<
         "got a permutation that is a polindrome." << std::endl;
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

int count_odd_occurrences(const std::string& str) {
    std::unordered_map<int, int> hash_table;
    int count_odd = 0;
    for(const auto character : str) {
        int val = get_value(character);
        if(val == -1) continue;
        hash_table[val]++;
        if(hash_table[val] % 2 == 0) {
            count_odd--;
        } else {
            count_odd++;
        }
    }
    return count_odd;
}

bool more_than_one_set_bit(const int& bit_vector) {
    return (bit_vector & (bit_vector - 1)) > 0;
}

bool is_perm_palindrome_using_bit_vector(const std::string& str) {
    int checker = 0;

    for(const auto& character : str) {
        int val = get_value(character);
        if(val == -1) continue;
        checker ^= (1 << val); // set/unset bit
    }

    return (!more_than_one_set_bit(checker));
}

/**
 * This approach is similar to already introduced hash table, but here 
 * instead of calling number_of_letters_that_occurred_odd_times, counter is 
 * used in function where hash table is filled with characters 
 */
bool alternate_perm_of_palin_using_hash_table(const std::string& str) {
    return count_odd_occurrences(str) <= 1;
}