#include <iostream>
#include <vector>
#include <bitset>

constexpr int size = 32;

int find_missing(std::vector<std::bitset<size>> numbers, int column)
{
    if(column >= size) return 0; 
    std::vector<std::bitset<size>> zero_bits, one_bits;
    for(std::bitset<size> number : numbers)
    {
        if(number[column] == 0) zero_bits.push_back(number);
        else one_bits.push_back(number);
    }
    int v = find_missing(zero_bits.size() <= one_bits.size() ? zero_bits : one_bits, column + 1);
    return (v << 1) | (zero_bits.size() <= one_bits.size() ? 0 : 1); // (v << 1) | 0 or (v << 1) | 1
}

int find_missing(std::vector<std::bitset<size>> numbers)
{
    return find_missing(numbers, 0);
}

/**
 * Missing Number: An array A contains all the integers from 0 to n, 
 * except for one number which is missing. In this problem, we cannot 
 * access an entire integer in A with a single operation. The elements 
 * of A are represented in binary, and the only operation we can use to 
 * access them is "fetch the jth bit of A[i]," which takes constant time.
 * Write code to find the missing integer. Can you do it in O(n) time?
 */
int main()
{
    std::vector<std::bitset<size>> numbers;
    constexpr int missing_number = 3;
    for(int i = 0; i < 8; i++) 
    {
        if(i == missing_number) continue;
        numbers.push_back(std::bitset<size>(i));
    }
    std::cout << "Missing number = " << find_missing(numbers) << '\n';
}