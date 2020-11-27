#include <iostream>
#include <vector>
#include <cstdlib> // rand, srand
#include <ctime> // time
#include <limits>

std::vector<int> ini_elements(int n, int max) 
{
    std::vector<int> el;
    // for testing, 1st el is smallest
    el.push_back(0);
    // 1st half of elements are smaller than 2nd half
    for(int i = 0; i < n/2 - 1; i++) 
    {
        el.push_back(rand() % (max/2));
    }
    for(int i = 0; i < n/2; i++) 
    {
        el.push_back(rand() % (max / 2) + max/2);
    }
    return el;
}

class Range {
    public:
        Range() = default;
        Range(int s, int e) : start(s), end(e) {}
        int start;
        int end;
};

int find_end_of_left(std::vector<int> elements) 
{
    for(int i = 1; i < elements.size(); i++) {
        if(elements[i] < elements[i - 1]) return i - 1;
    }
    return elements.size() - 1;
}
    
int find_start_of_right(std::vector<int> elements) 
{
    for(int i = elements.size() - 2; i >= 0; i--) {
        if(elements[i] > elements[i + 1]) return i + 1;
    }
    return 0;
}

int shrink_left(std::vector<int> elements, int min_index, int end_left) 
{
    int min = elements[min_index];
    // if int i = end_left in first iter, it would return start_mid, but mid is for sure smaller than el at min_index
    for(int i = end_left - 1; i >= 0; i--)
    {
        if(elements[i] <= min) return i + 1; // if in first iteration elements[i] <= min returns end_left 
    }
    return 0;
}

int shrink_right(std::vector<int> elements, int max_index, int start_right)
{
    int max = elements[max_index];
    for(int i = start_right; i < elements.size(); i++) 
    {
        if(elements[i] >= max) return i - 1;
    }
    return elements.size() - 1;
}

Range sub_sort(std::vector<int> elements) 
{
    int end_left = find_end_of_left(elements);
    if(end_left >= elements.size() - 1) return Range(-1, -1); // already sorted
    int start_right = find_start_of_right(elements);
    int max_index = end_left; // max of left
    int min_index = start_right; // min of right
    for(int i = end_left + 1; i < start_right ; i++) // check if middle contains elements that are bigger than end of left or smaller start of right
    {
        if(elements[i] < elements[min_index]) min_index = i;
        if(elements[i] > elements[max_index]) max_index = i;
    }
    int left_index = shrink_left(elements, min_index, end_left);
    int right_index = shrink_right(elements, max_index, start_right);
    return Range(left_index, right_index);
}

int find_right_seq_start(std::vector<int> elements) 
{
    int max = std::numeric_limits<int>::max();
    int last_index = 0;
    for(int i = 0; i < elements.size(); i++) 
    {
        if(max > elements[i]) 
        {
            last_index = i;
        }
        max = std::max(max, elements[i]);
    }

    return last_index;
}

int find_left_seq_end(std::vector<int> elements) 
{
    int min = std::numeric_limits<int>::min();
    int last_index = 0;
    for(int i = elements.size() - 1; i >= 0; i--) 
    {
        if(min > elements[i])
        {
            last_index = i;
        }
        min = std::min(elements[i], min);
    }
    return last_index;
}

Range sub_sort_better(std::vector<int> elements) 
{
    int left_seq_end = find_right_seq_start(elements);
    int right_seq_end = find_left_seq_end(elements);
    return Range(left_seq_end, right_seq_end);
}

template <class T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& v) 
{
    os << "[";
    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        os << " " << *ii;
    }
    os << "]";
    return os;
}

/**
 * Given an array of integers, write a method to find indices m and n such that if you sorted
 * elements m through n, the entire array would be sorted. Minimize n - m (that is, find the smallest
 * such sequence).
 * EXAMPLE:
 * Input: 1, 2, 4, 7, 10, 11, 8, 12, 5, 6, 16, 18, 19
 * Output: (3, 9)
 */
int main() {
    constexpr int n = 10;
    constexpr int max = 20;
    srand(time(NULL));
    std::vector<int> elements = ini_elements(n, max);
    std::cout << "Elements = " << elements << '\n';
    std::cout << "Enter 1 to solve using 1st approach or any other number to solve using 2nd approach\n";
    Range result;
    if(int method; std::cin >> method && method == 1) 
    {
        result = sub_sort(elements);
    } 
    else 
    {
        result = sub_sort_better(elements);
    }
    std::cout << "Range = " << "(" << result.start << ", " << result.end << ")\n";
}