#include <iostream>
#include <unordered_set>

std::unordered_set<std::string> parens_optimized(int n) {
    // TODO
}

std::unordered_set<std::string> parens(int n) {
    std::unordered_set<std::string> set;
    if(n == 0) {
        set.insert("");
    } else {    
        std::unordered_set<std::string> previous_set = parens(n - 1);
        for(std::string str : previous_set) {
            for(int i = 0; i < str.size(); i++) {
                // insert pair of parentheses inside of the every already existing pair of parentheses
                if(str[i] == '(') {
                    set.insert(str.substr(0, i + 1) + "()" + str.substr(i + 1));
                }
            }
            set.insert("()" + str); // insert at the beginning of string
        }
    }
    return set;
}

void print_set(std::unordered_set<std::string> set) {
    for(std::string str : set) {
        std::cout << str << '\n';
    }
}

/**
 * Implement an algorithm to print all valid (e.g. properly opened and closed) combinations
 * of n pairs of parentheses.
 * EXAMPLE:
 * Input: 3
 * Output: ((())), (()()), (())(), ()(()), ()()()
 */
int main() {
    std::cout << "Enter number of pairs of parentheses.\n";
    int n, method;
    std::cin >> n;
    std::cout << "Enter 1 to solve using optimized algorithm or any other number to not solve using optimized algorithm\n";
    std::cin >> method;
    std::unordered_set<std::string> set;
    switch (method)
    {
    case 1:
        set = parens_optimized(n);
        break;
    default:
        set = parens(n);
        break;
    }
    print_set(set);
}