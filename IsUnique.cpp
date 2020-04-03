#include <stdio.h>
#include <iostream>

class QuickSort {
    public:
        QuickSort() {}
        void sort_string(std::string&);
    private:
        void quick_sort(std::string&, const int&, const int&);
        int partition(std::string&, const int&, const int&);
        inline void swap_letters(std::string&, const int&, const int&);
};

class StringChecker {
    public:
        StringChecker() {}

        bool IsUnique(const std::string& str) const {
            int checker = 0;
            for(int i = 0; i < str.size(); i++) {
                int val = str.at(i) - 'a';
                if((checker & (1 << val)) > 0) {
                    return false;
                }
                checker |= (1 << val);
            }
            return true;
        }

        bool IsLowerCaseLetter(const std::string& str) const {
            for(const auto letter:str) {
                if(letter - 'a' < 0 || 'z' - letter < 0) {
                    return false;
                }
            }
            return true;
        }
    private:
};

bool check_uniqueness(const std::string&);
std::string get_lower_case_letter(const StringChecker&);

/**
 * Implement an algorithm to determine if a string has all unique 
 * characters. What if you cannot use additional data structures?
 */
int main() {
    // 1st approach: sort string and check neighbouring characters (no additional data structures)
    std::cout << "Enter string:" << std::endl;
    std::string string_to_check;
    std::cin >> string_to_check;
    QuickSort quickSort;
    quickSort.sort_string(string_to_check);
    std::cout << "Characters are " << (check_uniqueness(string_to_check) ? "" : "not ") << "unique." << std::endl;

    // 2nd approach: check using bit vector and assuming that the string only uses lower case letters a-z
    StringChecker checker;
    string_to_check = get_lower_case_letter(checker);
    std::cout << "Characters are " << (checker.IsUnique(string_to_check) ? "" : "not ") << "unique." << std::endl;
}

std::string get_lower_case_letter(const StringChecker& checker) {
    std::string str;
    while(true) {
        std::cout << "Enter string with lower case letters a-z:" << std::endl;
        std::cin >> str;
        if(!checker.IsLowerCaseLetter(str)) {
            std::cout << "String " << str << " constains characters that are not a-z." << std::endl;
        } else {
            return str;
        }
    }
}

bool check_uniqueness(const std::string& string_to_check) {
    for(int i = 0; i < string_to_check.size() - 1; i++) {
        if(string_to_check[i] == string_to_check[i+1]) {
            return false;
        }
    }
    return true;
}

inline void QuickSort::swap_letters(std::string& str, const int& first, const int& second) {
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
int QuickSort::partition(std::string& str, const int& low, const int& high) {
    const int pivot = str.at(high);
    int i = low - 1;
    char tmp;
    for(int j = low; j <= high - 1; j++) {
        if(str.at(j) < pivot) {
            i++;
            swap_letters(str, i, j);
        }
    }
    swap_letters(str, i + 1, high);
    return (i + 1);
}

void QuickSort::quick_sort(std::string& string_to_sort, const int& low, const int& high) {
    if(low < high) {
        int border = partition(string_to_sort, low, high);
        quick_sort(string_to_sort, low, border - 1);
        quick_sort(string_to_sort, border + 1, high);
    }
}

// use quick sort
void QuickSort::sort_string(std::string& string_to_sort) {
    quick_sort(string_to_sort, 0, string_to_sort.size() - 1);
}