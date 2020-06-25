#include <iostream>
#include <vector>

std::vector<std::vector<char>> power_set_recursion(std::vector<char> set, int iteration_index) {
    std::vector<std::vector<char>> subsets;
    if(iteration_index == set.size()) {
        std::vector<char> v; // empty subset
        subsets.push_back(v);
        return subsets;
    }
    subsets = power_set_recursion(set, iteration_index + 1);
    std::vector<std::vector<char>> new_subsets;
    for(std::vector<char> subset : subsets) {
        new_subsets.push_back(subset);
        subset.push_back(set[iteration_index]);
        new_subsets.push_back(subset);
    }
    return new_subsets;
}

std::vector<std::vector<char>> power_set_recursion(std::vector<char> set) {
    return power_set_recursion(set, 0);
}

std::vector<char> convert_int_to_char_vector(int num, std::vector<char> set) {
    std::vector<char> v;
    int index = 0;
    // condition i > 0 is ok because this loop changes v only for 
    // values that has bit set to 1
    for(int i = num; i > 0; i >>= 1) {
        if(i & 1 == 1) {
            v.push_back(set[index]);
        }
        index++;
    }
    return v;
}

// binary representation: every num is in the set(1) or it is not(0).
// n numbers -> 2^n combinations (2 states for every num)
// generate 2^n binary numbers and translate the binary num into a set 
std::vector<std::vector<char>> power_set_combinatorics(std::vector<char> set) {
    std::vector<std::vector<char>> subsets;
    for(int i = 0; i < (1 << set.size()); i++) {
        subsets.push_back(convert_int_to_char_vector(i, set));
    }
    return subsets;
}

std::ostream& operator<<(std::ostream& os, std::vector<std::vector<char>> subsets) {
    for(std::vector<char> subset : subsets) {
        if(subset.empty()) {
            os << "{}";
        }
        for(char c : subset) {
            os << "{" << c << "}";
        }
        os << '\n';
    }
    return os;
}

/**
 * Write a method to return all subsets of a set.
 */
int main() {
    std::cout << "=========\nPower Set\n=========\n";
    std::cout << "Enter 1 to solve problem using recursion or any other number to solve using combinatorics.\n";
    std::vector<char> set = {'a', 'b', 'c', 'd'};
    int method;
    std::cin >> method;
    std::vector<std::vector<char>> subsets;
    switch (method)
    {
    case 1:
        subsets = power_set_recursion(set);
        break;
    default:
        subsets = power_set_combinatorics(set);
        break;
    }
    std::cout << subsets << '\n';
}
