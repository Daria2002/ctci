#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

std::vector<int> ini_elements(int n, int max) 
{
    std::vector<int> el;
    int sign;
    for(int i = 0; i < n/2 - 1; i++) 
    {  
        sign = rand() % 2 ? -1 : 1;
        el.push_back(sign * rand() % max);
    }
    return el;
}

int max_contiguous_sum(std::vector<int> elements) 
{
    int max_sum = 0;
    int tmp_sum = 0;
    for(int i = 0; i < elements.size(); i++) 
    {
        tmp_sum += elements[i];
        if(tmp_sum < 0)
        {
            tmp_sum = 0;
        } else if(tmp_sum > max_sum) {
            max_sum = tmp_sum;
        }
    }
    return max_sum;
}

/**
 * Contiguous Sequence: You are given an array of integers (both positive and negative). Find the
 * contiguous sequence with the largest sum. Return the sum.
 * EXAMPLE:
 * Input: 2, -8, 3, -2, 4, -10
 * Output: 5 (i.e., {3, -2, 4})
 */
int main() 
{
    constexpr int max = 15;
    constexpr int n = 10;
    // std::vector<int> elements = ini_elements(n, max);
    std::vector<int> elements = {2, -8, 3, -2, 4, -10};
    std::cout << "Max sum = " << max_contiguous_sum(elements) << '\n';
}