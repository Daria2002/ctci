#include <iostream>

void reverse(char** str) {
    char* end = *str;
    char tmp;
    if(str) {
        while(*end != '\0') {
            ++end;
        }
        --end; // go back, last char is \0
        // swap chars
        int size = 0;
        while(*str < end) {
            tmp = **str;
            **str = *end;
            *end = tmp;
            std::cout << "**str = " << **str << '\n';
            std::cout << "*end = " << *end << '\n';
            --(end);
            ++(*str);
            size++;
        }
        (*str) -= size; // return pointer to str to the beginning
    }
}

/**
 * Implement a function void reverse( char* str) in C or C++ which 
 * reverses a null-terminated string.  
 */
int main() {
    const int max = 100;
    char* c = new char[max];
    std::cout << "Enter a string to reverse:\n";
    std::cin >> c;
    c += '\0';
    reverse(&c); 
    std::cout << "Reversed string: " << c << '\n';
}
