#include <iostream>

int swap_odd_and_even_bits(int n) {
    // mask_odd gives odd numbers
    int mask_odd = 0xaaaaaaaa; // a = 1010, mask = 1010...1010
    int mask_even =  0x55555555; // 5 = 0101, mask = 0101...0101
    int odd_nums = n & mask_odd;
    int even_nums = n & mask_even;
    int result = ((odd_nums >> 1) | (even_nums << 1));
    return result;
}

/**
 * Write a program, to swap odd and even bits in an integer with as few instructions as
 * possible (e.g., bit 0 and bit 1 are swapped, bit 2 and bit 3 are swapped, and so on).
 */
int main() {
    std::cout << "====================================================\n"
                 "Program for swapping odd and even bits in an integer\n"
                 "====================================================\n";
    int n;
    std::cout << "Enter a number to swap:\n";
    std::cin >> n;
    std::cout << "Swapped number = " << swap_odd_and_even_bits(n) << '\n';
}
