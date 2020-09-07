#include <iostream>

void swap_in_place_diff(int& a, int& b) {
    a -= b;
    b += a;
    a = b - a;
    return;
}

// benefit of this solution is that it workd for more data type than just integers
// xor returns 1 if x != y, otherwise 0
void swap_in_place_xor(int& a, int& b) {
    a ^= b; // bit in a are set to 1 if those bits are different for a and b, otherwise 0
    b ^= a; // b is equal to old value of a
    a ^= b; // a is equal to old value of b
    return;
}

/**
 * Number Swapper: Write a function to swap two numbers in place (that is, without
 * temporary variables)
 */
int main() {
    int a(5);
    int b(2);
    std::cout << "Before swap: " << "a = " << a << ", b = " << b << '\n';
    std::cout << "Enter 1 to swap in place using diff or any other number to swap using xor.\n";
    int method;
    std::cin >> method;
    if(method == 1) {
        swap_in_place_diff(a, b);
    } else {
        swap_in_place_xor(a, b);
    }
    std::cout << "After swap: " << "a = " << a << ", b = " << b << '\n';
}