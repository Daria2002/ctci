#include <iostream>
#include <vector>

int product_recursion1(int smaller, int bigger) {
    if(smaller == 0) return 0;
    if(smaller == 1) return bigger;
    // TODO
    return 0;
}

int product1(int first, int second) {
    return product_recursion1(first < second ? first : second, first > second ? first : second);
}

int product_recursion2(int smaller, int bigger) {
    // TODO
    return 0;
}

int product2(int first, int second) {
    // TODO
    return 0;
}

int product_recursion3(int smaller, int bigger) {
    // TODO
    return 0;
}

int product3(int first, int second) {
    // TODO
    return 0;
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
