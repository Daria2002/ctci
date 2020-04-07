#include <stdio.h>
#include <iostream>

int get_compressed_size(const std::string&);
std::string get_compressed_string(const std::string&);

/**
 * Implement a method to perform a basic string compression using the counts 
 * of repeated characters. For example, the string aabcccccaaa would become
 * a2b1c5a3. If the 'compressed' string would not become smaller than the original 
 * string, yout method should return the original string. You can assume the string 
 * has only uppercase and lowercase letters (a-z).
 */
int main() {

    std::cout << "Enter string that you would like to compress: " << std::endl;
    std::string input;
    std::cin >> input;
    int compressed_size = get_compressed_size(input);
    if(compressed_size > input.size()) {
        std::cout << "Compressed string is not smaller than original one." << std::endl;
        return 0;
    }
    std::string compressed_string = get_compressed_string(input);
    std::cout << "Compressed string is: " << compressed_string << std::endl;
    return 0;
}

int get_compressed_size(const std::string& input) {
    int compressed_size = 0;
    int counter = 0;
    for(int i = 0; i < input.size(); i++) {
        counter++;
        if(i + 1 >= input.size() || input[i] != input[i+1]) {
            compressed_size += 1 + std::to_string(counter).size();
            counter = 0;
        }
    }
    return compressed_size;
}

std::string get_compressed_string(const std::string& input) {
    int counter = 0;
    std::string output;
    for(int i = 0; i < input.size(); i++) {
        counter++;
        if(i + 1 >= input.size() || input[i] != input[i+1]) {
            output.append(1, input[i]);
            output.append(std::to_string(counter));
            counter = 0;
        }
    }
    return output;
}