#include<iostream>
#include<limits>

int flip(int bit) {
    return 1^bit;
}

int sign(int a) {
    return flip((a >> 31) & 0x1);
}

/**
 * If sign(a) == sign(b) -> sc > 0 if a > b, otherwise sc < 0
 * If sign(a) != sign(b) -> bigger num is positive num
 */
int max_num(int a, int b) {
    int sa = sign(a);
    int sb = sign(b);
    int c = a - b;
    int sc = sign(c);
    int use_sign_of_a = sa ^ sb;
    int use_sign_of_c = flip(sa ^ sb);
    int k = use_sign_of_a * sa + use_sign_of_c * sc;
    int q = flip(k);
    return k * a + q * b; // k = 1 if a > b, otherwise 0... q is flipped k
}

/**
 * Write a method that finds the maximum of two numbers. You should not use if else or any other
 * comparison operator.
 */
int main() {
    int a;
    int b;
    std::cout << "Enter 1st num: ";
    std::cin >> a;
    std::cout << "Enter 2nd num: ";
    std::cin >> b;
    std::cout << "Max num is " << max_num(a, b) << '\n'; 
}