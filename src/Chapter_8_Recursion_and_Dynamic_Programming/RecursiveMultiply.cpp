#include <iostream>
#include <vector>

int product_recursion1(int smaller, int bigger) {
    if(smaller == 0) return 0;
    if(smaller == 1) return bigger;
    int half = smaller >> 1; // divide by 2
    int first_half = product_recursion1(half, bigger);
    int second_half = smaller % 2 ? product_recursion1(smaller - half, bigger) : first_half;
    return first_half + second_half;
}

int product1(int first, int second) {
    return product_recursion1(first < second ? first : second, first > second ? first : second);
}

int product_recursion2(int smaller, int bigger, std::vector<int>& memo) {
    if(smaller == 0) return 0;
    if(smaller == 1) return bigger;
    if(memo[smaller] != -1) return memo[smaller];
    int half = smaller >> 1; // divide by 2
    int first_half = product_recursion2(half, bigger, memo);
    int second_half = smaller % 2 ? product_recursion2(smaller - half, bigger, memo) : first_half;
    memo[smaller] = first_half + second_half;
    return memo[smaller];
}

int product2(int first, int second) {
    std::vector<int> memo;
    for(int i = 0; i <= first; i++) {
        memo.push_back(-1);
    }
    return product_recursion2(first < second ? first : second, first > second ? first : second, memo);
}

int product_recursion3(int smaller, int bigger) {
    if(smaller == 0) return 0;
    if(smaller == 1) return bigger;
    int half = smaller >> 1;
    int first_half = product_recursion3(half, bigger);
    if(smaller % 2) {
        return first_half + first_half + bigger;
    } 
    return first_half + first_half;
}

int product3(int first, int second) {
    return product_recursion3(first < second ? first : second, first > second ? first : second);
}


/**
 * Write a recursive function to multiply two positive integers without using the *
 * operator (or / operator). You can use addition, subtraction, and bit shifting, but
 * you should minimize the number of those operations.
 */
int main() {
    std::cout << "==================\nRecursive Multiply\n==================\n";
    std::cout << "Enter 1 to use first algorithm, 2 to use second algorithm and any other number to use third algorithm\n";
    int method, result, first, second;
    std::cin >> method;
    std::cout << "Enter first number.\n";
    std::cin >> first; 
    std::cout << "Enter second number.\n";
    std::cin >> second; 
    switch (method)
    {
    case 1:
        result = product1(first, second);
        break;
    case 2:
        result = product2(first, second);
        break;
    default:
        result = product3(first, second);
        break;
    }
    std::cout << "Result = " << result << '\n';
}
