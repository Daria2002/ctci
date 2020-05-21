#include <iostream>
#include <string>
#include <algorithm>

int longest_sequence(int num) {
    if(~num == 0) return sizeof(int) * 8; 
    int max = 0, prev = 0, curr = 0;
    while(num != 0) {
        if((num & 1) == 1) {
            curr++;
        } else if((num & 1) == 0) {
            prev = curr; // update prev
            curr = 0; // start counting new sequence length
        }
        max = std::max(curr + prev + 1, max);
        num >>= 1;
    }
    return max;
}

/**
 * You have an integer and you can flip exactly one bit from a 0 to a 1.
 * Write a code to find the length of the longest sequence of 1s you could create.
 * EXAMPLE:
 * Input: 1775 (or: 11011101111)
 * Output: 8
 */
int main() {
    std::cout << "===============================================================================================\n"
                 "Program for flipping bit to find the length of the longest sequence of 1s that could be created\n"
                 "===============================================================================================\n";
    std::cout << "Enter input:\n";
    int num;
    std::cin >> num;
    std::cout << "The length of the longest sequence = " << longest_sequence(num) << '\n'; 
}
