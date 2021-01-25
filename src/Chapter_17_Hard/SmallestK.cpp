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
    int biggest = rank(elements, k);
    std::vector<int> smallest;
    for(int i = 0; ((i < elements.size()) && (smallest.size() < k)); i++)
    {
        if(elements[i] <= biggest) smallest.push_back(elements[i]);
    }
    return smallest;
}

std::vector<int> smallest_selection_rank2(std::vector<int> elements, const int k)
{
    // todo
    return elements;
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
        smallest = smallest_selection_rank2(elements, k);
    }
    std::cout << "Smallest k elements: ";
    for(int el : smallest) std::cout << el << ", ";
    std::cout << '\n';
}