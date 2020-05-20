#include <iostream>
#define MAX_SIZE 32
#define ERROR "ERROR"

std::string double_to_binary(double input) {
    if(input >= 1 || input <= 0) return ERROR;
    std::string bin = "0.";
    while(input != 0) {
        if(bin.size() == MAX_SIZE) return ERROR;
        input = input * 2;
        if(input >= 1) {
            bin += '1';
            input -= 1;
        } else {
            bin += '0';
        }
    }
    return bin;
}

/**
 * Given a real number between 0 and 1 (e.g., 0.72) that is passed in as a double, 
 * print the binary representation. If the number cannot be represented accurately
 * in binary with at most 32 characters, print "ERROR".
 */
int main() {
    std::cout << "=======================================\n"
                 "Program for converting binary to string\n"
                 "=======================================\n";
    std::cout << "Enter a number:\n";
    double input;
    std::cin >> input;
    std::string binary = double_to_binary(input);
    std::cout << "Result = " << binary << '\n';
}
