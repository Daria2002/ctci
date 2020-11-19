#include<iostream>
#include<unordered_set>

void diving_board_recursive(int k, int total, const int shorter, const int longer, std::unordered_set<int>& lengths) {
    if(k == 0) {
        lengths.emplace(total);
        return;
    }
    diving_board_recursive(k - 1, total + shorter, shorter, longer, lengths);
    diving_board_recursive(k - 1, total + longer, shorter, longer, lengths);
}

std::unordered_set<int> diving_board_recursive(int k, const int shorter, const int longer) {
    std::unordered_set<int> lengths;
    diving_board_recursive(k, 0, shorter, longer, lengths);
    return lengths;
}

void diving_board_memoization(int k, int total, const int shorter, const int longer, 
std::unordered_set<int>& lengths, std::unordered_set<std::string>& visited) {
    if(k == 0) {
        lengths.emplace(total);
        return;
    }
    // we need to check total sum and num of planks because 1 + 1 != 2 (diff num of planks is remained)
    std::string key = total + " " + k; 
    if(visited.count(key)) {
        return;
    }
    diving_board_memoization(k - 1, total + shorter, shorter, longer, lengths, visited);
    diving_board_memoization(k - 1, total + longer, shorter, longer, lengths, visited);
    visited.emplace(key);
}

std::unordered_set<int> diving_board_memoization(int k, const int shorter, const int longer) {
    std::unordered_set<int> lengths;
    std::unordered_set<std::string> visited;
    diving_board_memoization(k, 0, shorter, longer, lengths, visited);
    return lengths;
}

std::unordered_set<int> diving_board_optimal(int k, const int shorter, const int longer) {

}

void print_lengths(const std::unordered_set<int>& lengths, const int k) {
    std::cout << "All possible lengths for the diving board made of " << k << " planks:\n";
    for(int length : lengths) std::cout << length << '\n';
}

/**
 * Diving Board: You are building a diving board by placing a bunch of planks of wood end-to-end.
 * There are two types of planks, one of length shorter and one of length longer. You must use exactly
 * K planks of wood. Write a method to generate all possible lengths for the diving board.
 */
int main() {
    constexpr int shorter = 4;
    constexpr int longer = 7;
    int method;
    std::cout << "Enter 1 to solve using recursive solution, 2 to solve using momoization solution or\n"
    "any other number to solve optimal solution.\n";
    std::cin >> method;
    std::cout << "Enter the number of planks that should be used?\n";
    int k;
    std::cin >> k;
    std::unordered_set<int> lengths;
    switch (method)
    {
    case 1:
        lengths = diving_board_recursive(k, shorter, longer);
        break;
    case 2:
        lengths = diving_board_memoization(k, shorter, longer);
        break;
    default:
        lengths = diving_board_optimal(k, shorter, longer);
        break;
    }
    print_lengths(lengths, k);
}