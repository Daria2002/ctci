#include <iostream>

/**
 * Return which power of 5 is n
 */
int factorsOf5(int i) {
    int count = 0; 
    while (i % 5 == 0)
    {
        count++;
        i /= 5;
    }
    return count;
}

/**
 * Iterate through all the numbers from 2 through n, counting the number of times that 5
 * goes into each number.
 */
int countFactZeros1(int n) {
    int count = 0; 
    for(int i = 2; i <= n; i++) {
        count += factorsOf5(i);
    }
    return count;
}

/**
 * Count the factors of 5. Count how many multiples of m are in n, dividing n by m.
 */
int countFactZeros2(int n) {
    int count = 0; 
    if(n < 0) return -1;
    for(int i = 5; n/i > 0; i *= 5) count += (n / i);
    return count;
}

/**
 * Factorial Zeros: Write an algorithm which computes the number of trailing zeros in n factorial.
 */
int main() {
    int n;
    std::cout << "Enter n\n";
    std::cin >> n;
    int method;
    std::cout << "Enter 1 to count trailing zeros in n factorial counting number of times that 5\n"
    "goes into each number or any other number to directly count the factors of 5.\n";
    std::cin >> method;
    int factZeros;
    if(method == 1) {
        factZeros = countFactZeros1(n);
    } else {
        factZeros = countFactZeros2(n);
    }
    std::cout << "Number of trailing zeros in " << n << "! is " << factZeros << ".\n";
}