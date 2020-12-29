#include <iostream>
#include <bitset>

int add1(int first, int second)
{
    std::bitset<32> first_bit(first);
    std::bitset<32> second_bit(second);
    std::bitset<32> add_without_carry = first_bit ^ second_bit;
    std::cout << "first bit = " << first_bit << '\n';
    std::cout << "second bit = " << second_bit << '\n';
    std::cout << "xor = " << add_without_carry << '\n';
    std::bitset<32> carry = (first_bit & second_bit) << 1;
    std::bitset<32> result = add_without_carry ^ carry;
    return (int)result.to_ulong();
}

int add2(int first, int second)
{
    int result;
    // todo
    return result;
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