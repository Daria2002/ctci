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
    int c0 = 0, c1 = 0, tmp = number;
    while(tmp & 1 == 1) {
        c1++;
        tmp >>= 1;
    }

    // there is no smaller number because all 1s are on the right just next to each other
    if(tmp == 0) {
        return -1;
    }

    while(((tmp & 1) == 0) && (tmp != 0)) {
        c0++;
        tmp >>= 1;
    }
    int p = c0 + c1;
    // clear all bits till (including) rightmost non-trailing 1
    int mask_clear = ((~0) << (p + 1));
    number &= mask_clear;
    int mask_set_ones = (1 << (c1 + 1)) - 1; // rightmost non-trailing 1 is flipped to 0, so there is one extra 1 to set
    number |= mask_set_ones << (c0 - 1); // rightmost non-trailing 1 is flipped to 0, so there is one 0 less to be set
    return number;
}

int get_next_arithmetic(int n) {
    // set trailing 0s to 1s
    int c0 = 0, c1 = 0, tmp = n;
    while((tmp & 1 == 0) && tmp != 0) {
        tmp >>= 1;
        c0++;
    }
    while((tmp & 1) == 1) {
        tmp >>= 1;
        c1++;
    }
    // there is no larger number with the same number of 1s because
    // number looks like: 1111...111000...0000
    if(c0 + c1 == 31 || c0 + c1 == 0) {
        return -1;
    }
    // set trailing 0s to 1
    n = n + (1 << c0) - 1;
    // set rightmost non-trailing 0 to 1
    n = n + 1;
    // set c1 - 1 leftmost 0s to 1s
    n = n + (1 << (c1-1)) - 1; // be careful: 2 ^ x = 2 xor x, but: 1 << x = pow(2, x)
    return n;
}

int get_prev_arithmetic(int n) {
    int c0 = 0, c1 = 0, tmp = n;
    while(tmp & 1 == 1) {
        c1++;
        tmp >>= 1;
    }

    // there is no smaller number because all 1s are on the right just next to each other
    if(tmp == 0) {
        return -1;  
    }

    while(((tmp & 1) == 0) && (tmp != 0)) {
        c0++;
        tmp >>= 1;
    }
    // set to 0 everything that is on the right of the rightmost non-trailing 1
    n = n - ((1 << c1) - 1);
    // set the rightmost non-trailing 1 to 0 and everything on the right to it flip from 0 to 1
    n = n - 1;
    // set last (c0 - 1) numbers (with indexes in range [0, c0 - 2]) to 0
    n = n - ((1 << (c0 - 1)) - 1);
    return n;
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
