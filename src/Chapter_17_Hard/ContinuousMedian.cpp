#include <iostream>
#include <cstdlib> // rand
#include <ctime> // time
#include <queue>

// max heap for values below the median
std::priority_queue<int, std::vector<int>, std::less<int>> max_heap;
// min heap for values above the median
std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

double get_median()
{
    if(max_heap.empty()) return 0;
    if(max_heap.size() == min_heap.size()) return (double) ((max_heap.top() + min_heap.top()) / 2.);
    return max_heap.top();
}

/**
 * Max heap contains values below the median. Max_heap.top is the biggest of the smallest elements.
 * If Max_heap.top > value -> biggest of small elements is bigger than value. move max_heap top to min_heap and store value in max_heap.
 * Min heap contains values above the median. Min heap.top is the biggest of the biggest elements.
 * If Min_heap.top < value -> smallest of big elements is smaller than value. move min_heap top to max_heap and store value in min_heap.
 */
void add_number(int num)
{
    if(max_heap.size() == min_heap.size())
    {
        if(min_heap.size() > 0 && num > min_heap.top())
        {
            max_heap.push(min_heap.top());
            min_heap.pop();
            min_heap.push(num);
        }
        else
        {
            max_heap.push(num);
        }
    }
    else
    {
        if(max_heap.size() > 0 && num < max_heap.top())
        {
            min_heap.push(max_heap.top());
            max_heap.pop();
            max_heap.push(num);
        }
        else 
        {
            min_heap.push(num);
        }
    }
}

void print_heaps()
{
    std::priority_queue<int, std::vector<int>, std::less<int>> max_heap_tmp = max_heap;
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap_tmp = min_heap;
    std::cout << "max heap:";
    while (!max_heap_tmp.empty())
    {
        std::cout << max_heap_tmp.top() << ", ";
        max_heap_tmp.pop();
    }
    std::cout << "\nmin heap:";
    while (!min_heap_tmp.empty())
    {
        std::cout << min_heap_tmp.top() << ", ";
        min_heap_tmp.pop();
    }
    std::cout << '\n';
}

/**
 * Continuous Median: Numbers are randomly generated and passed to a method. 
 * Write a program to find and maintain the median values as new values are generated.
 */
int main()
{
    // median - the number for which half the numbers are larger and half the numbers are smaller
    srand(time(NULL));
    constexpr int size = 4;
    for(int i = 0; i < size; i++)
    {
        int rand_num = rand() % 15;
        std::cout << rand_num << ", ";
        add_number(rand_num);
        print_heaps();
    }
    std::cout << "\nMedian = " << get_median() << '\n';
}