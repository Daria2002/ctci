#include <iostream>

struct NextNumbers {
    int largest;
    int smallest;
};

std::ostream& operator<<(std::ostream& os, NextNumbers nn) {
    return os << "Largest = " << nn.largest << ", smallest = " << nn.smallest << '\n';
}

int get_next_bm(int number) {
    int c0 = 0, c1 = 0, tmp = number;
    while(((tmp & 1) == 0) && tmp != 0) {
        c0++;
        tmp >>= 1;
    }
    while((tmp & 1) == 1) {
        c1++;
        tmp >>= 1;
    }
    // number 11...1100...00 doesn't have next largest number with same number of 1s
    // checking if c0 + c1 == 31 because integer range is [-2^31, 2^31 - 1]
    // unsigned integer has range [0, 2^32 - 1]
    if(c0 + c1 == 31 || c0 + c1 == 0) {
        return -1;
    }
    int p = c0 + c1;
    // set rightmost non-trailing 0 to 1
    // i.e. 1400 has 2 trailing zeros
    number |= (1 << p);
    // mask for clearing everything before rightmost non-trailing zero
    int mask = ~((1 << p) - 1); // 1111...1110000
    number &= mask;
    // insert ones on right
    number |= ((1 << (c1 - 1)) - 1); // insert c1 - 1 number of 1s because the rightmost non-trailing 0 is flipped to 1
    return number;
}

int get_prev_bm(int number) {

}

int get_next_arithmetic(int number) {

}

int get_prev_arithmetic(int number) {

}

typedef int (* function_call)(int number);

NextNumbers get_next_numbers(int number, function_call func_largest, function_call func_smallest) {
    NextNumbers r;
    r.largest = func_largest(number);
    r.smallest = func_smallest(number);
    return r;
}

NextNumbers next_numbers_bm(int number) {
    return get_next_numbers(number, get_next_bm, get_prev_bm);
}

NextNumbers next_numbers_arithmetic(int number) {
    return get_next_numbers(number, get_next_arithmetic, get_prev_arithmetic);
}

/**
 * Given a positive integer, print the next smallest and the next 
 * largest number that have the same number of 1 bits in their
 * binary representation.
 */
int main() {
    std::cout << "=====================================================================================\n"
                 "Program for searching the next largest and smallest number with same number of 1 bits\n"
                 "=====================================================================================\n";
    std::cout << "Enter 1 to solve this problem using bit manipulation approach or 2 for solving it using arithmetic approach:\n";
    int method, number;
    std::cin >> method;
    std::cout << "Enter an input number:\n";
    std::cin >> number;
    NextNumbers result;
    switch (method) {
    case 1:
        result = next_numbers_bm(number);
        break;
    case 2:
        result = next_numbers_arithmetic(number);
        break;
    default:
        std::cout << "None of the proposed methods have not been choosen.\n";
        return 0;
    }
    std::cout << result;
}
