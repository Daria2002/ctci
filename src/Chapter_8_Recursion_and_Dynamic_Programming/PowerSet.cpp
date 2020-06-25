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

std::vector<std::vector<char>> power_set_combinatorics(std::vector<char> set) {
    std::vector<std::vector<char>> subsets;
    // todo
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
    std::vector<char> set = {'a', 'b'};
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
