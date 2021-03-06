#include <iostream>
#include <vector>
#include <algorithm>
#include "heap/MaxHeap.hpp"
#include <cstdlib> // rand, srand
#include <ctime> // time

// O(nlogn)
std::vector<int> smallest_sort(std::vector<int> elements, const int k)
{
    if(elements.size() <  k) return elements;
    std::sort(elements.begin(), elements.end());
    return std::vector<int>(elements.begin(), elements.begin() + k);
}

std::vector<int> heap_to_vector(MaxHeap heap)
{
    std::vector<int> v;
    while (!heap.empty())
    {
        v.push_back(heap.top());
        heap.pop();
    }
    return v;
}

MaxHeap get_k_max_heap(const std::vector<int>& elements, const int k)
{
    MaxHeap heap;
    for(int element : elements)
    {
        if(heap.size() < k) heap.push(element);
        else if(element < heap.top())
        {
            heap.pop();
            heap.push(element);
        }
    }
    return heap;
}

std::vector<int> smallest_max_heap(const std::vector<int>& elements, const int k)
{
    if(elements.size() <  k) return elements;
    MaxHeap heap = get_k_max_heap(elements, k);
    return heap_to_vector(heap);
}

int random_index(const int left, const int right)
{
    return (rand() % (right - left + 1) + left);
}

int max(std::vector<int> elements, int left, int right)
{
    int max_el = std::numeric_limits<int>::min();
    for(int i = left; i <= right; i++)
    {
        if(elements[i] > max_el) max_el = elements[i];
    }
    return max_el;
}

void swap(std::vector<int>& elements, int n, int m)
{
    int tmp = elements[n];
    elements[n] = elements[m];
    elements[m] = tmp;
}

int partition(std::vector<int>& elements, int left, int right, int pivot)
{
    while (left <= right)
    {
        if(elements[left] > pivot) // left > pivot -> swap with right
        {
            swap(elements, left, right);
            right--;
        }
        else if(elements[right] <= pivot) // right < pivot -> swap with left
        {
            swap(elements, left, right);
            left++;
        }
        else // left and right in correct order
        {
            right--;
            left++;
        }
    }
    return left - 1;
}

int rank(std::vector<int> elements, int num_rank, int left, int right)
{
    int pivot = elements[random_index(left, right)];
    int left_end_index = partition(elements, left, right, pivot);
    int left_size = left_end_index - left + 1;
    if(num_rank == left_size - 1)
    {
        return max(elements, left, left_end_index);
    }
    else if(num_rank > left_size - 1)
    {
        return rank(elements, num_rank - left_size, left_end_index + 1, right);
    }
    return rank(elements, num_rank, left, left_end_index); // num_rank < left_size - 1
}

int rank(std::vector<int> elements, const int k)
{
    return rank(elements, k, 0, elements.size() - 1);
}

std::vector<int> smallest_selection_rank1(std::vector<int> elements, const int k)
{
    if(elements.size() <  k) return elements;
    int biggest = rank(elements, k - 1);
    std::vector<int> smallest;
    for(int i = 0; i < elements.size(); i++)
    {
        if(elements[i] <= biggest) smallest.push_back(elements[i]);
    }
    return smallest;
}

class PartitionResult
{
    public:
        PartitionResult() = default;
        PartitionResult(int l, int m) : left_size(l), middle_size(m) {}
        int left_size, middle_size;
};

PartitionResult partition2(std::vector<int> elements, int start, int end, int pivot)
{
    int left = start;
    int right = end;
    int middle = left;
    while (middle <= right)
    {
        if(elements[middle] < pivot)
        {
            swap(elements, middle, left);
            middle++;
            left++;
        }
        else if(elements[middle] > pivot)
        {
            swap(elements, middle, right);
            right--;
        }
        else if(elements[middle] == pivot)
        {
            middle++;
        }
    }
    return PartitionResult(left - start, right - left + 1);
}

int rank2(std::vector<int> elements, int num_rank, int left, int right)
{
    int pivot = elements[random_index(left, right)];
    PartitionResult partition = partition2(elements, left, right, pivot);
    if(num_rank < partition.left_size) // threshold is on left
    {
        return rank2(elements, num_rank, left, left + partition.left_size - 1);
    }
    else if(num_rank < partition.left_size + partition.middle_size) // threshold is in the middle
    {
        return pivot;
    }
    // threshold is on the right
    return rank2(elements, num_rank - partition.left_size - partition.middle_size, left + partition.left_size + partition.middle_size, right);
}

int rank2(std::vector<int> elements, int num_rank)
{
    return rank2(elements, num_rank, 0, elements.size() - 1);
}

std::vector<int> smallest_selection_rank2(std::vector<int> elements, const int k)
{
    if(k >= elements.size()) return elements;
    int threshold = rank2(elements, k - 1);
    std::vector<int> smallest;
    for(int el : elements) if(el < threshold) smallest.push_back(el);
    while (smallest.size() < k) smallest.push_back(threshold);
    return smallest;
}

/**
 * Smallest K : Design an algorithm to find the smallest K numbers in an array.
 */
int main()
{
    std::cout << "Enter 1 for approach using sorting, 2 for approach using max heap, 3 for selection rank algorithm\n"
    "(if elements are unique) or any other number for selection rank algorithm (if elements are not unique)\n";
    int method;
    std::cin >> method;
    std::cout << "Enter k:\n";
    int k;
    std::cin >> k;
    std::vector<int> elements = {8, 6, 17, 5, 1, 6, 12, 2};
    std::vector<int> smallest;
    srand(time(NULL));
    if(method == 1)
    {
        smallest = smallest_sort(elements, k);
    }
    else if(method == 2)
    {
        smallest = smallest_max_heap(elements, k);
    }
    else if(method == 3)
    {
        smallest = smallest_selection_rank1(elements, k);
    }
    else
    {
        // modify elements, so elements are not unique
        elements.push_back(5);
        elements.push_back(5);
        smallest = smallest_selection_rank2(elements, k);
    }
    std::cout << "Smallest k elements: ";
    for(int el : smallest) std::cout << el << ", ";
    std::cout << '\n';
}