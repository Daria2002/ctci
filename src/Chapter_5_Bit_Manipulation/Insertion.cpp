#include <iostream>
#include <cmath>
#define NUM_SIZE 32

void decimal_to_binary(int num, std::string& bin) {
    if(num / 2 != 0) {
        decimal_to_binary(num / 2, bin);
    }
    bin += num % 2 + '0';
}

std::string decimal_to_binary(int num) {
    std::string bin;
    decimal_to_binary(num, bin);
    return bin;
}

int insert(int N, int M, int start, int end) {
    if(start > end || start < 0 || end >= NUM_SIZE) return 0;
    int allOnes = ~1;
    int left = allOnes << (end + 1);
    int right = ((1 << start) - 1);
    int mask = left | right;
    int cleared_n = N & mask;
    int shifted_m = M << start;
    return cleared_n | shifted_m;
}

void binary_to_decimal(std::string bin, int& dec, int current_index) {
    if(current_index != bin.size() - 1) {
        binary_to_decimal(bin, dec, current_index + 1);
    }
    int multiplier = bin[bin.size() - 1 - current_index] == '0' ? 0 : 1; 
    dec += multiplier * std::pow(2, current_index);
}

void binary_to_decimal(std::string bin, int& dec) {
    dec = 0;
    binary_to_decimal(bin, dec, 0);
}

/**
 * You are given two 32-bit numbers, N and M, and two bit positions, i and j.
 * Write a method to insert M into N such that M starts at bit j and ends at
 * bit i. You can assume that the bits j through i have enough space to fit
 * all of M. That is, if M = 10011, you can assume that there are at least 5
 * bits between j and i. You would not, for example have j = 3 and i = 2,
 * because M could not fully fit between bit 3 and bit 2.
 * EXAMPLE:
 * Input:  N = 10000000000, M = 10011, i = 2, j = 6
 * Output: N = 10001001100
 */
int main() {
    std::cout << "============================================================================\n"
                 "Program for inserting M into N such that M starts at bit j and ends at bit i\n"
                 "============================================================================\n";
    int N, M, i, j;
    std::string bin_N, bin_M;
    std::cout << "Enter N:\n";
    std::cin >> bin_N;
    std::cout << "Enter M:\n";
    std::cin >> bin_M;
    binary_to_decimal(bin_N, N);
    binary_to_decimal(bin_M, M);
    std::cout << "Enter i (start index):\n";
    std::cin >> i;
    std::cout << "Enter j (end index):\n";
    std::cin >> j;
    std::cout << "Result number = " << decimal_to_binary(insert(N, M, i, j)) << '\n';
}
