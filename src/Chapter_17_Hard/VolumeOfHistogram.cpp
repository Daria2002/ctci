#include <iostream>
#include <vector>

int find_max_index(const std::vector<int>& histogram, const int start, const int end)
{
    int max_index = start;
    for(int i = start + 1; i <= end; i++) if(histogram[i] > histogram[max_index]) max_index = i;
    return max_index;
}

int bordered_vol(const std::vector<int>& histogram, const int start, const int end)
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

int subgraph_vol(const std::vector<int>& histogram, const int start, const int end, bool is_left)
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

int volume1(const std::vector<int>& histogram)
{
    int start = 0;
    int end = histogram.size() - 1;
    int max = find_max_index(histogram, start, end);
    int left_vol = subgraph_vol(histogram, start, max, true);
    int right_vol = subgraph_vol(histogram, max, end, false);
    return left_vol + right_vol;
}

class Histogram 
{
    public:
        Histogram(int h) : height(h) {}
        Histogram() = default;
        int height;
        int leftMaxIndex = -1;
        int rightMaxIndex = -1;
};

int bordered_vol(const std::vector<Histogram>& histogram, const int start, const int end)
{
    if(start >= end) return 0;
    int min = std::min(histogram.at(start).height, histogram.at(end).height);
    int sum = 0;
    for(int i = start + 1; i < end; i++)
    {
        sum += min - histogram.at(i).height;
    }
    return sum;
}

int subgraph_vol(const std::vector<Histogram>& histogram, const int start, const int end, bool is_left)
{
    if(start >= end) return 0;
    int sum = 0;
    if(is_left)
    {
        int max = histogram.at(end - 1).leftMaxIndex;
        sum += bordered_vol(histogram, max, end);
        sum += subgraph_vol(histogram, start, max, is_left);
    }
    else 
    {
        int max = histogram.at(start + 1).rightMaxIndex;
        sum += bordered_vol(histogram, start, max);
        sum += subgraph_vol(histogram, max, end, is_left);
    }
    return sum;
}

std::vector<Histogram> create_histogram(const std::vector<int>& h)
{
    std::vector<Histogram> histogram(h.size());
    for(int i = 0; i < h.size(); i++) histogram[i] = Histogram(h[i]);
    int max_index = 0;
    // set left max index
    for(int i = 0; i < h.size(); i++) 
    {
        if(h.at(max_index) < h.at(i)) max_index = i;
        histogram[i].leftMaxIndex = max_index;
    }
    // set right max index
    max_index = h.size() - 1;
    for(int i = h.size() - 1; i >= 0; i--) 
    {
        if(h.at(max_index) < h.at(i)) max_index = i;
        histogram[i].rightMaxIndex = max_index;
    }
    return histogram;
}

int volume2(const std::vector<int>& histogram)
{
    int start = 0;
    int end = histogram.size() - 1;
    std::vector<Histogram> h = create_histogram(histogram);
    int max = h[0].rightMaxIndex;
    int left_vol = subgraph_vol(h, start, max, true);
    int right_vol = subgraph_vol(h, max, end, false);
    return left_vol + right_vol;
}

int volume3(const std::vector<int>& histogram)
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
    std::cout << "Enter 1 for solution #1, 2 for solution #2 or any other number for solution #3:\n";
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