#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int missing_number(const std::vector<int>& elements)
{
    long long actual_sum = 0; // sum is long long because it might be very large number
    std::for_each(elements.begin(), elements.end(), [&](auto el) { actual_sum += el; });
    int n = elements[elements.size() - 1];
    long long full_sum = n * (n + 1) / 2;
    return full_sum - actual_sum;
}

std::pair<int, int> solve(const int k1, const int k2)
{
    /*
        ax^2 + bx + c -> x = [-b +- sqrt(b^2 - 4ac)] / 2a
        2x^2 - 2sx + s^2 - t = 0 (see missing_numbers function)
    */
   int a = 2;
   int b = -2 * k1;
   int c = k1 * k1 - k2;
   double part1 = -b;
   double part2 = sqrt(b*b - 4*a*c);
   double part3 = 2 * a;
   int x = (int) ((part1 + part2) / part3);
   int y = k1 - x;
   std::cout << "x = " << x << '\n';
   std::cout << "y = " << y << '\n';
   return std::make_pair(x, y);
}

int square_sum(int n, int power)
{
    int sum = 0;
    for(int i = 1; i <= n; i++) sum += pow(i, power);
    return sum;
}

std::pair<int, int> missing_numbers(const std::vector<int>& elements)
{
    /*
        x + y = s
        x^2 + y^2 = t
        y = s - x
        x^2 + (s - x)^2 = t
        2x^2 - 2sx + s^2 - t = 0
        k1 = s
        k2 = t
    */
    int n = elements.size() + 2; // last element can be calculated from elements size because numbers are in range [1, n], where 2 nums are missing in size, so there is +2
    int s = n * (n + 1) / 2; // initialize to expected value, and in for loop decrement to get sum of missing numbers
    int t = square_sum(n, 2);  // initialize to expected value
    for(int i = 0; i < elements.size(); i++)
    {
        t -= (elements[i] * elements[i]);
        s -= elements[i];
    }
    return solve(s, t);
}

/**
 * Missing Two: You are given an array with all the numbers from 1 to N appearing exactly once, except for one number
 * that is missing. How can you find the missing number in O(N) time and O(1) space? What if there were two numbers missing?
 */
int main()
{
    std::cout << "Enter 1 to find 1 missing num or any other number to find 2 missing numbers:\n";
    int method;
    std::cin >> method;
    if(method == 1)
    {
        std::vector<int> elements = {1, 2, 3, 5, 6, 7, 8, 9, 10};
        std::cout << "Missing number is " << missing_number(elements) << ".\n";
    }
    else 
    {
        std::vector<int> elements = {1, 2, 3, 5, 6, 7, 8, 10};
        std::pair<int, int> missing = missing_numbers(elements);
        std::cout << "Missing numbers are " << missing.first << ", " << missing.second << '\n';
    }
}