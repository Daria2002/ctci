#include <iostream>
#include <cmath>

int count_2s(int input)
{
    int count = 0;
    while (input > 0)
    {
        if(input % 10 == 2) count++;
        input /= 10;
    }
    return count;
}

int count_2s_bf(int input)
{
    int count = 0;
    for(int i = 0; i <= input; i++) 
    {
        count += count_2s(i);
    }
    return count;
}

int count_2s_at_digit(int number, int d)
{
    int power_of_10 = std::pow(10, d);
    int next_power_of_10 = power_of_10 * 10;
    int right = number % power_of_10;
    int round_down = number - number % next_power_of_10;
    int round_up = round_down + next_power_of_10;
    int digit = (number / power_of_10) % 10;
    if(digit < 2)
    {
        return round_down / 10; // 1/10 numbers in rounded number are 2
    }
    else if(digit > 2)
    {
        return round_up / 10;
    }
    // digit == 2
    return round_down / 10 + right + 1;
}

int count_2s_improved(int input)
{
    int count = 0;
    int len = std::to_string(input).size();
    for(int digit = 0; digit < len; digit++)
    {
        count += count_2s_at_digit(input, digit);
    }
    return count;
}

/**
 * Count of 2s: Write a method to count the number of 2s that appear in all the numbers
 * between 0 and n (inclusive).
 * EXAMPLE:
 * Input: 25
 * Output: 9 (2, 12, 20, 21, 22, 23, 24 and 25. Note that 22 counts for two 2s.)
 */ 
int main()
{
    std::cout << "Enter 1 to solve using brute force or any other number for improved approach:\n";
    int method;
    std::cin >> method;
    std::cout << "Enter input:\n";
    int input;
    std::cin >> input;
    std::cout << "Count of 2s = " << (method == 1 ? count_2s_bf(input) : count_2s_improved(input)) << '\n'; 
}