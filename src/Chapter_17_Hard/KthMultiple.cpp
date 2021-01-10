#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <deque>
#include <algorithm>

typedef std::numeric_limits<int> int_limit;

std::vector<int> possibilities_bf(const int k)
{
    std::vector<int> possibilities;
    for(int a = 0; a <= k; a++)
    {
        int pow3 = std::pow(3, a);
        for(int b = 0; b <= k; b++)
        {
            int pow5 = std::pow(5, b);
            for(int c = 0; c <= k; c++)
            {
                int pow7 = std::pow(7, c);
                int val = pow3 * pow5 * pow7;
                // check if overflow
                if(val < 0 || pow3 == int_limit::max() || 
                pow5 == int_limit::max() || pow7 == int_limit::max())
                {
                    val = int_limit::max();
                }
                possibilities.push_back(val);
            }
        }
    }
    return possibilities;
}

int kth_multiple_bf(const int k)
{
    std::vector<int> possibilities = possibilities_bf(k);
    std::sort(possibilities.begin(), possibilities.end());
    return possibilities[k];
}

void add_products(std::deque<int>& q, int val)
{
    q.push_back(val * 3);
    q.push_back(val * 5);
    q.push_back(val * 7);
}

int remove_min(std::deque<int>& q)
{
    int min = std::numeric_limits<int>::max();
    for(int val : q)
    {
        if(val < min) min = val;
    }
    q.erase(std::remove(q.begin(), q.end(), min), q.end());
    return min;
}

int kth_multiple_improved(const int k)
{
    std::deque<int> multiples;
    int val = 1;
    multiples.push_back(val);
    for(int i = 0; i < k; i++)
    {
        val = remove_min(multiples);
        add_products(multiples, val);
    }
    return val;
}

int kth_multiple_optimal(const int k)
{
    // todo
    return 0;
}

/**
 * Kth Multiple: Design an algorithm to find the kth number such that the only 
 * prime factors are 3, 5 and 7. Note that 3, 5 and 7 do not have to be factors,
 * but it should not have any other prime factors. For example, the first several
 * multiples would be (in order) 1, 3, 5, 7, 9, 15, 21.
 */
int main()
{
    std::cout << "Enter 1 to solve using brute force approach, 2 to solve using improved\n"
    "approach or any other number using optimal approach:\n";
    int method; 
    std::cin >> method;
    int k;
    std::cout << "Enter k:\n";
    std::cin >> k;
    int num;
    switch (method)
    {
    case 1:
        num = kth_multiple_bf(k);
        break;
    case 2:
        num = kth_multiple_improved(k);
        break;
    default:
        num = kth_multiple_optimal(k);
        break;
    }
    std::cout << k << "th multiple is " << num << ".\n";
} 