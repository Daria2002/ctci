#include <iostream>
#include <array>
#include <algorithm>
#include <limits>

void swap(std::array<int, 5>& arr, int l, int r) {
    int tmp = arr[l];
    arr[l] = arr[r];
    arr[r] = tmp;
}

void sort_valley_peak_suboptimal(std::array<int, 5>& arr) {
    std::sort(arr.begin(), arr.end());
    for(int i = 1; i < arr.size(); i += 2) swap(arr, i - 1, i);
}

int max_index(std::array<int, 5>& arr, int previous, int current, int next) {
    int len = arr.size();
    int prev_val = (previous >= 0 && previous < len) ? arr[previous] : std::numeric_limits<int>::min();
    int curr_val = (current >= 0 && current < len) ? arr[current] : std::numeric_limits<int>::min();
    int next_val = (next >= 0 && next < len) ? arr[next] : std::numeric_limits<int>::min();
    int max = std::max(prev_val, std::max(curr_val, next_val));
    if(max == curr_val) return current;
    return (max == prev_val ? previous : next);
}

void sort_valley_peak_optimal(std::array<int, 5>& arr) {
    for(int i = 1; i < arr.size(); i += 2) {
        int biggest_index = max_index(arr, i - 1, i, i + 1);
        if(biggest_index != i) {
            swap(arr, i, biggest_index);
        }
    }
}

/**
 * In an array of integers, a "peak" is an element which is greater than or equal to
 * the adjacent integers and a "valley" is an element which is less than or equal to 
 * the adjacent integers. For example, in the array {5, 8, 6, 2, 3, 4, 6}, {8, 6} are 
 * peaks and {S, 2} are valleys. Given an array of integers, sort the array into an 
 * alternating sequence of peaks and valleys.
 * EXAMPLE:
 * Input: {5, 3, 1, 2, 3}
 * Output: {5, 1, 3, 2, 3} 
 */
int main() {
    std::array<int, 5> arr = {5, 3, 1, 2, 3};
    sort_valley_peak_suboptimal(arr);
    std::cout << "Enter 1 for suboptimal solution or any other number for optimal\n";
    int method;
    std::cin >> method;
    switch (method)
    {
    case 1:
        sort_valley_peak_suboptimal(arr);
        break;
    default:
        sort_valley_peak_optimal(arr);
        break;
    }
    for(int i = 0; i < 5; i++) std::cout << arr[i] << ", ";
    std::cout << '\n';
}
