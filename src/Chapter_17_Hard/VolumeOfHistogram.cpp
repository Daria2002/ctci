#include <iostream>
#include <vector>

int find_max_index(std::vector<int> histogram, int start, int end)
{
    int max_index = start;
    for(int i = start + 1; i <= end; i++) if(histogram[i] > histogram[max_index]) max_index = i;
    return max_index;
}

int bordered_vol(std::vector<int> histogram, int start, int end)
{
    if(start >= end) return 0;
    int min = std::min(histogram[start], histogram[end]);
    int sum = 0;
    for(int i = start + 1; i < end; i++)
    {
        sum += min - histogram[i];
    }
    return sum;
}

int subgraph_vol(std::vector<int> histogram, int start, int end, bool is_left)
{
    if(start >= end) return 0;
    int sum = 0;
    if(is_left)
    {
        int max = find_max_index(histogram, start, end - 1);
        sum += bordered_vol(histogram, max, end);
        sum += subgraph_vol(histogram, start, max, is_left);
    }
    else 
    {
        int max = find_max_index(histogram, start + 1, end);
        sum += bordered_vol(histogram, start, max);
        sum += subgraph_vol(histogram, max, end, is_left);
    }
    return sum;
}

int volume1(std::vector<int> histogram)
{
    int start = 0;
    int end = histogram.size() - 1;
    int max = find_max_index(histogram, start, end);
    int left_vol = subgraph_vol(histogram, start, max, true);
    int right_vol = subgraph_vol(histogram, max, end, false);
    return left_vol + right_vol;
}

int volume2(std::vector<int> histogram)
{
    // todo
    return 0;
}

int volume3(std::vector<int> histogram)
{
    // todo
    return 0;
}

/**
 * Volume of Histogram: Imagine a histogram (bar graph). Design an algorithm to compute the volume
 * of water it couldd hold if someone poured water across the top. You can assume that each histogram
 * has width 1.
 * EXAMPLE: {0, 0, 4, 0, 0, 6, 0, 0, 3, 0, 5, 0, 1, 0, 0, 0} 
 * Output: 26
 */
int main()
{
    std::cout << "Enter 1 for soluzion #1, 2 for solution #2 or any other number for solution #3:\n";
    int method;
    std::cin >> method;
    int volume;
    std::vector<int> histogram = {0, 0, 4, 0, 0, 6, 0, 0, 3, 0, 5, 0, 1, 0, 0, 0};
    if(method == 1)
    {
        volume = volume1(histogram);
    }
    else if(method == 2)
    {
        volume = volume2(histogram);
    }
    else 
    {
        volume = volume3(histogram);
    }
    std::cout << "Volume = " << volume << '\n';
}