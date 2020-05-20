#include <iostream>
#include <string>

bool is_bin(int num) {
    while(num != 0) {
        if(num % 10 != 1 && num % 10 != 0) {
            return false;
        } 
        num /= 10;
    }
    return true;
}

void decimal_to_binary(int num, std::string& bin) {
    if(num / 2 != 0) {
        decimal_to_binary(num / 2, bin);
    }
    bin += num % 2 + '0';
}

std::string to_bin(int num) {
    if(is_bin(num)) {
        return std::to_string(num);
    }
    std::string bin;
    decimal_to_binary(num, bin);
    return bin;
}

int longest_sequence(std::string bin) {
    int max = 0, right = 0, left = 0;
    bool counting_right = false;
    for(int i = 0; i < bin.size(); i++) {
        if(bin[i] == '1' && !counting_right) {
            left++;
        } else if(bin[i] == '0' && !counting_right) {
            counting_right = true;
            left++;
        } else if(bin[i] == '0' && counting_right) {
            // counting_right = false;
            if(left + right > max) {
                max = left + right;
            }
            left = right + 1;
            right = 0;
        } else {
            right++;
        }
    }
    // check if the last sequence is longer than current max
    return left + right > max ? left + right : max;
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
    std::string bin = to_bin(num);
    std::cout << "The length of the longest sequence = " << longest_sequence(bin) << '\n'; 
}
