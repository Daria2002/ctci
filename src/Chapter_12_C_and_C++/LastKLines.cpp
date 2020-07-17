#include <iostream>
#include <array>
#include <string>

void print_last_K_lines(const int k) {
    std::string input;
    std::string* arr = new std::string[k];
    // initialize array
    for(int i = 0; i < k; i++) arr[i] = "";
    int index = 0;
    std::cin >> input;
    // read lines
    while(input != "s") {
        arr[index % k] = input;
        index++;
        std::cin >> input;
    }
    std::cout << "Last " << k << " lines:\n";
    for(int i = 0; i < k; i++) {
        std::cout << arr[i] << '\n';
    }
}

/**
 * Write a method to print the last K lines of an input file using C++. 
 */
int main() {
    // for this solution circular array is used
    std::cout << "Type in input line, write s to stop.\n";
    const int k = 10;
    print_last_K_lines(k);
}
