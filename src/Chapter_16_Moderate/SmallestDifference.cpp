#include <iostream>
#include <array>

int smallestDifferenceBruteForce(std::array<int, 5> a, std::array<int, 5> b) {
    // TODO
    return 0;
}

int smallestDifferenceOptimal(std::array<int, 5> a, std::array<int, 5> b) {
    // TODO
    return 0;
}

int smallestDifferenceOptimalSize(std::array<int, 5> a, std::array<int, 5> b) {
    // TODO
    return 0;
}

/**
 * Smallest Difference: Given two arrays of integers, compute the pair of values (one value in
 * each array) with the smallest (non-negative) difference. Return the difference.
 * EXAMPLE:
 * Input: {1, 3, 15, 11, 2}, {23, 127, 235, 19, 8}
 * Output: 3. That is, the pair (11, 8)
 */
int main() {
    std::array<int, 5> a = {1, 3, 15, 11, 2};
    std::array<int, 5> b = {1, 3, 15, 11, 2};
    std::cout << "Enter 1 to solve using brute force, 2 to solve using optimal approach or any other\n"
    "number to solve using optimal approach if the arrays are significantly different in size.\n";
    int method;
    std::cin >> method;
    int smallestDifference;
    if(method == 1) {
        smallestDifference = smallestDifferenceBruteForce(a, b);
    } else if(method == 2) {
        smallestDifference = smallestDifferenceOptimal(a, b);
    } else {
        smallestDifference = smallestDifferenceOptimalSize(a, b);
    }
    std::cout << "Smallest difference between arrays = " << smallestDifference << '\n';
}