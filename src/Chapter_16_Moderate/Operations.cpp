#include <iostream>

// time complexity: O(n)
int negate(int n) {
    int neg = 0;
    int newSign = n < 0 ? 1 : -1;
    while(n != 0) {
        n += newSign;
        neg += newSign;
    }
    return neg;
}

int negate_optimal(int n) {
    int neg = 0; 
    int newSign = n < 0 ? 1 : -1;
    int delta = newSign;
    while(n != 0) {
        bool diffSign = ((n + delta > 0) != (n > 0));
        if(n + delta != 0 && diffSign) {
            delta = newSign;
        }
        n += delta;
        neg += delta;
        delta += delta;
    }
    return neg;
}

// subtraction in terms of addition -> a-b = a+(-1)*b
// multiplication is not allowed -> implement negate function
int subtract(int first, int second) {
    return first + negate_optimal(second);
}

int abs_f(int num) {
    return (num < 0 ? negate(num) : num);
}

// sum first num, second number of times
int multiply(int first, int second) {
    if(first < second) return multiply(second, first);
    int sum = 0;
    for(int i = abs_f(second); i > 0; i = subtract(i, 1)) {
        sum += first;
    }
    // if first num is negative, negative values are summed in for loop
    if(second < 0) {
        // negate sum if second is negative
        sum = negate(sum);
    }
    return sum;
}

// x = a/b or find x that a = bx = xb
// compute x by adding b to itself repeatedly until we reach a
// the number of times we need to do that will equal x
int divide(int first, int second) {
    if(second == 0) throw "Error: division with 0 is not possible.\n";
    int abs_first = abs_f(first); 
    int abs_second = abs_f(second); 
    int product = 0;
    int x = 0;
    while (product + abs_second <= abs_first)
    {
        product += abs_second;
        x++;
    }
    return (((first > 0) == (second > 0)) ? x : negate(x));
}

/**
 * Write methods to implement the multiply, subtract and divide operations for integers.
 * The results of all of these are integers. You can use the add operator, but not minus, times or divide.
 */
int main() {
    std::cout << "Enter 1 to use multiply, 2 to use subtract or any other number to use divide operation:\n";
    int operation;
    std::cin >> operation;
    int first, second;
    std::cout << "Enter 1st number:\n";
    std::cin >> first;
    std::cout << "Enter 2nd number:\n";
    std::cin >> second;
    if(operation == 1) {
        std::cout << first << " * " << second << " = " << multiply(first, second) << '\n';
    } else if(operation == 2) {
        std::cout << first << " - " << second << " = " << subtract(first, second) << '\n';
    } else {
        std::cout << first << " : " << second << " = " << divide(first, second) << '\n';
    }
}