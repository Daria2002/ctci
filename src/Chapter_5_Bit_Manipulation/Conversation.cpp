#include <iostream>

int bits_to_flip_shift_count(int base, int target) {
    int xor_result = base ^ target;
    int counter = 0;
    while(xor_result != 0) {
        // if(xor_result & 1 == 1) {
        //     counter++;
        // }
        // better way of writting code in comment:
        counter += (xor_result & 1);
        xor_result >>= 1;
    }
    return counter;
}

int bits_to_flip_smart_count(int base, int target) {
    int xor_result = base ^ target;
    int counter = 0;
    while(xor_result != 0) {
        xor_result = xor_result & (xor_result - 1);
        counter++;
    }
    return counter;
}

/**
 * Write a function to determine the number of bits you would need to flip 
 * to convert integer A to integer B.
 * EXAMPLE:
 * Input : 29 (or: 11101), 15 (or: 01111)
 * Output: 2
 */
int main() {
    std::cout << "=====================================================================================================\n"
                 "Program for counting number of bits to be flipped in order to convert base integer to target integer.\n"
                 "=====================================================================================================\n";
    int a, b;
    std::cout << "Enter base integer:\n";
    std::cin >> a;
    std::cout << "Enter target integer:\n";
    std::cin >> b;
    int to_be_flipped, method;
    std::cout << "Choose 1 to use XOR and shift count method or 2 to use XOR and smart counter:\n";
    std::cin >> method;
    switch (method) {
    case 1:
        to_be_flipped = bits_to_flip_shift_count(a, b);
        break;
    case 2:
        to_be_flipped = bits_to_flip_smart_count(a, b);
        break;
    default:
        std::cout << "None of the provided methods have not been choosen\n";
        return 0;
    }
    std::cout << "Number of bits that should be flipped to convert " << a << " to " << b << " = " << to_be_flipped << ".\n";
}
