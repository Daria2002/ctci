#include <iostream>

int brute_force_solution(int n) {

}

int memoization(int n) {

}

/**
 * A child is running up a staircase with n steps and can hop either 1 step,
 * 2 steps, or 3 steps at a time. Implement a method to count how many possible
 * ways the child can run up the stairs.
 */
int main() {
    int method;
    std::cout << "Enter 1 to solve Triple Step using Brute Force Solution or 2 to"
    "solve it using Memoization\n";
    std::cin >> method;
    if(method != 1 && method != 2) {
        std::cout << "None of the proposed methods have not been choosen";
        return 0;
    }
    int n;
    std::cout << "Enter n-number of stairs?\n";
    std::cin >> n;
    std::cout << "Number of possible ways = " << (method == 1 ? brute_force_solution(n) : memoization(n)) << '\n';
}
