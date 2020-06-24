#include <iostream>
#include <unordered_map>

int count_ways_brute_force(int n) {
    if(n < 0) return 0;
    if(n == 0) return 1;
    return count_ways_brute_force(n-1) + count_ways_brute_force(n-2) + count_ways_brute_force(n-3);
}

// The number of ways will quickly overflow the bounds of an integer and using long will delay
// but not completely solve the issue. BigInteger uses std::string to store big int and it's 
// better approach to introduce big int instead of int for number of ways
int count_ways_memoization(int n, std::unordered_map<int, int>& memo) {
    if(n < 0) return 0;
    if(n == 0) return 1;
    if(memo[n] > -1) {
        return memo[n];
    }
    memo[n] = count_ways_memoization(n - 1, memo) + count_ways_memoization(n - 2, memo) + count_ways_memoization(n - 3, memo);
    return memo[n];
}

int count_ways_memoization(int n) {
    std::unordered_map<int, int> memo;
    for(int i = 1; i <= n; i++) {
        memo[i] = -1;
    }
    return count_ways_memoization(n, memo);
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
    std::cout << "Number of possible ways = " << (method == 1 ? count_ways_brute_force(n) : count_ways_memoization(n)) << '\n';
}
