#include <iostream>

bool is_power_of_2(int n) {
    // n & (n - 1) == 0 only if there is one 1 in n
    // if there is one 1 in n, than n is a power of 2
    return (n & (n - 1)) == 0;
}

/**
 * Explain what the following code does: ((n & (n - 1)) == 0).
 */
int main() {
    std::cout << "=======================================================\n"
                 "Program for checking if provided number is a power of 2\n"
                 "=======================================================\n";
    int n;
    std::cout << "Enter a number:\n";
    std::cin >> n;
    std::cout << n << " is " << (is_power_of_2(n) ? "" : "not ") << "a power of 2.\n";
    return 0;
}
