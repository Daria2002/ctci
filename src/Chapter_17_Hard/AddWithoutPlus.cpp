#include <iostream>
#include <bitset>

int add1(int first, int second)
{
    if(second == 0) return first;
    int add_without_carry = first ^ second;
    int carry = (first & second) << 1;
    return add1(add_without_carry, carry);
}

int add2(int first, int second)
{
    while (second != 0)
    {
        int sum = first ^ second;
        int carry = (first & second) << 1;
        first = sum;
        second = carry;
    }
    return first;
}

/**
 * Add Without Plus: Write a function that adds two numbers. 
 * You should not use + or any arithmetic operators.
 */
int main()
{
    int method;
    std::cout << "Enter 1 for solution #1 or any other number for solution #2:\n";
    std::cin >> method;
    int first, second;
    std::cout << "Enter 1st num:\n";
    std::cin >> first;
    std::cout << "Enter 2nd num:\n";
    std::cin >> second;
    int result = (method == 1 ? add1(first, second) : add2(first, second));
    std::cout << first << " + " << second << " = " << result << '\n';
}