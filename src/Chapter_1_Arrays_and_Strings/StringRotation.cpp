#include <iostream>

/**
 * Assume you have a method isSubstring which checks if one word is a substring
 * of another. Given two strings, s1 and s2, write a code to check if s2 is a 
 * rotation of s1 using only one call to isSubstring (e.g., "waterbottle" is a 
 * rotation of "erbottlewat").
 */
int main() {
    std::string s1, s2;
    std::cout << "Enter first string:" << std::endl;
    std::cin >> s1;
    std::cout << "Enter second string:" << std::endl;
    std::cin >> s2;

    if(s1.size() != s2.size()) {
        std::cout << "s1 is not rotation of s2 because they are not the same size." << std::endl;
        return 0;
    }

    std::string s1s1 = s1 + s1;
    // npos is a static member constant value with the greatest possible
    // value for an element of type size_t
    bool isSubstring = s1s1.find(s2) != std::string::npos;
    std::cout << "s1 = " << s1 << " is " << (isSubstring ? "" : "not ")
    << "rotation of s2 = " << s2 << std::endl; 
}