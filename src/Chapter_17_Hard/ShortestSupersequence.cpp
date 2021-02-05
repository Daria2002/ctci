#include <iostream>
#include <vector>

class Range
{
    public:
        Range() = default;
        Range(int s, int e) : start(s), end(e) {}
        int start, end;
        int len() const
        {
            return end - start + 1;
        }
};

int find_next_instance(const std::vector<int>& shortest_arr, const int element, const int index)
{
    for(int i = index; i < shortest_arr.size(); i++) if(shortest_arr[i] == element) return i;
    return -1;
}

int find_closure(const std::vector<int>& longer_arr, const std::vector<int>& shorter_arr, const int index)
{
    int max = -1;
    // iterate through shorter arr and search each element in longer arr
    for(int i = 0; i < shorter_arr.size(); i++)
    {
        int next = find_next_instance(longer_arr, shorter_arr[i], index); // find 1st occurence of shorter_arr[i] in big_arr searching only from index to end
        if(next == -1) return -1;
        max = std::max(next, max); // remember current closure
    }
    return max;
}

Range shortest_range_bf(const std::vector<int>& shorter_arr, const std::vector<int>& longer_arr)
{
    int best_start = -1, best_end = -1;
    for(int i = 0; i < longer_arr.size(); i++)
    {
        int end = find_closure(longer_arr, shorter_arr, i);
        if(end == -1) break;
        if(best_start == -1 || (end - i < best_end - best_start))
        {
            best_start = i;
            best_end = end;
        }
    }
    return Range(best_start, best_end);
}

void sweep_for_closure(const int el, const std::vector<int>& longer_arr, std::vector<int>& closures)
{
    int next = -1;
    for(int i = longer_arr.size() - 1; i >= 0; i--)
    {
        if(longer_arr[i] == el) 
        {
            next = i;
        }
        // closures[i] == -1, there is an element in the smaller arr that still didn't occurred in the bigger arr
        if((next == -1 || closures[i] < next) && (closures[i] != -1)) 
        {
            closures[i] = next;
        }
    }
}

std::vector<int> get_closures(const std::vector<int>& shorter_arr, const std::vector<int>& longer_arr)
{
    std::vector<int> closures(longer_arr.size(), 0);
    for(int i = 0; i < shorter_arr.size(); i++)
    {
        sweep_for_closure(shorter_arr[i], longer_arr, closures);
    }
    return closures;
}

Range get_shortest_closure(const std::vector<int>& closures)
{
    Range shortest = Range(0, closures[0]);
    for(int i = 1; i < closures.size(); i++)
    {
        if(closures[i] == -1) break;
        Range r = Range(i, closures[i]);
        if(shortest.len() > r.len()) shortest = r;
    }
    if(shortest.len() <= 0) return Range(-1, -1);
    return shortest;
}

Range shortest_range_less_space(const std::vector<int>& shorter_arr, const std::vector<int>& longer_arr)
{
    std::vector<int> closures = get_closures(shorter_arr, longer_arr);
    return get_shortest_closure(closures);
}

Range shortest_range_optimal(const std::vector<int>& shorter_arr, const std::vector<int>& longer_arr)
{
    Range r;
    // todo
    return r;
}

/**
 * Shortest Supersequence: You are given two arrays, one shorter (with all distinct elements) and one longer.
 * Find the shortest subarray in the longer array that contains all the elements in the shorter array. The items
 * can appear in any order.
 * EXMAPLE:
 * Input:
 * {1, 5, 9}
 * {7, 5, 9, 0, 2, 1, 3, 5, 7, 9, 1, 1, 5, 8, 8, 9, 7}
 *                      ------------            
 * Putput: [7, 10] (the underlines portion above)
 **/
int main()
{
    std::cout << "Enter 1 to solve using bf approach, 2 to solve using pretty fast with less space approach\n"
    "or any other number to solve using optimal approach\n";
    int method;
    std::cin >> method;
    const std::vector<int> shorter_arr = {1, 5, 9};
    const std::vector<int> longer_arr = {7, 5, 9, 0, 2, 1, 3, 5, 7, 9, 1, 1, 5, 8, 8, 9, 7};
    Range shortest_range;
    if(method == 1)
    {
        shortest_range = shortest_range_bf(shorter_arr, longer_arr);
    }
    else if(method == 2)
    {
        shortest_range = shortest_range_less_space(shorter_arr, longer_arr);
    }
    else 
    {
        shortest_range = shortest_range_optimal(shorter_arr, longer_arr);
    }
    std::cout << "Shortest range is [" << shortest_range.start << ", " << shortest_range.end << "].\n";  
}