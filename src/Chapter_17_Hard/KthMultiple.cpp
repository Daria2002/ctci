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

class Result
{
    public:
        Result() = default;
        Result(int m, int q) : min(m), q_num(q) {}
        int min, q_num;
};

Result remove_min(std::deque<int>& q3, std::deque<int>& q5, std::deque<int>& q7)
{
    int q3_front = q3.front();
    int q5_front = q5.front();
    int q7_front = q7.front();
    if((!q3.empty() && q5.empty() && q7.empty()) || (q3_front < q5_front && q3_front < q7_front))
    {
        q3.pop_front();
        return Result(q3_front, 3);
    }
    else if((q3.empty() && !q5.empty() && q7.empty()) || (q5_front < q3_front && q5_front < q7_front))
    {
        q5.pop_front();
        return Result(q5_front, 5);
    }
    // q7 min
    q7.pop_front();
    return Result(q7_front, 7);
}

void add_products(int min, int q_num, std::deque<int>& q3, std::deque<int>& q5, std::deque<int>& q7)
{
    if(q_num == 3)
    {
        q3.push_back(min * 3);
    }
    if(q_num == 3 || q_num == 5)
    {
        q5.push_back(min * 5);
    }
    q7.push_back(min * 7);
}

int kth_multiple_optimal(const int k)
{
    if(k < 0) return 0;
    std::deque<int> q3, q5, q7;
    q3.push_back(1); // ini
    Result result;
    for(int i = 0; i < k; i++)
    {
        result = remove_min(q3, q5, q7);
        add_products(result.min, result.q_num, q3, q5, q7);
    }
    return result.min;
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