#include <iostream>
#include <array>
#include <limits>
#include <algorithm>

/**
 * The brute force way is to just iterate through all pairs, compute the difference, and 
 * compare it to the current minimum difference.
 * Time complexity: O(AB), A-size of 1st arr, B-size of 2nd arr
 */
int smallestDifferenceBruteForce(int a[], int size_a, int b[], int size_b) {
    if(size_a == 0 || size_b == 0) return -1;
    int smallest_diff = std::numeric_limits<int>::max();
    for(int i = 0; i < size_a; i++) {
        for(int j = 0; j < size_b; j++) {
            smallest_diff = std::min(smallest_diff, std::abs(a[i] - b[j]));
        }
    }
    return smallest_diff;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // pivot is element at the last index
    int i = (low - 1); // destination index of smaller element
    for(int j = low; j <= high - 1; j++) {
        if(arr[j] < pivot) { // if element smaller than the pivot, put on the left
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    // put pivot at index after subset od numbers which are smaller than it
    swap(&arr[i + 1], &arr[high]); 
    return i + 1; // pivot position
}

/**
 * This method implements quick sort algorithm.
 */
void quick_sort(int arr[], int low, int high) {
    if(low < high)
    {
        // element at partition_index will be at correct index
        int partitioning_index = partition(arr, low, high);
        // sort left part of partition index
        quick_sort(arr, low, partitioning_index - 1); 
        // sort right part of partition index
        quick_sort(arr, partitioning_index + 1, high); 
    }
}

/**
 * This method implements quick sort algorithm.
 */
void sort(int arr[], int size_arr) {
    quick_sort(arr, 0, size_arr - 1);
}

/**
 * Optimal: sort arrays. Iterate through array and find the min diff.
 * Big O comp. = sort_a + sort_b + iter_a + iter_b = O(AlogA + BlogB) + O(A + B) = O(AlogA + BlogB)
 */
int smallestDifferenceOptimal(int a[], int size_a, int b[], int size_b) {
    if(size_a == 0 || size_b == 0) return -1;
    sort(a, size_a);
    sort(b, size_b);
    int index_a = 0;
    int index_b = 0;
    int smallest_diff = std::numeric_limits<int>::max();
    while(index_a < size_a && index_b < size_b) {
        int diff = std::abs(a[index_a] - b[index_b]);
        smallest_diff = std::min(smallest_diff, diff);
        if(a[index_a] < b[index_b]) index_a++;
        else index_b++;
    }
    return smallest_diff;
}

int find_closest_el(int a[], int low, int high, int b_el) {
    if(high >= low) {
        int index_mid = (high - low) / 2;
        int diff_mid = std::abs(a[index_mid] - b_el);
        int diff_mid_minus_1 = std::numeric_limits<int>::max();
        if(index_mid - 1 >= low) {
            diff_mid_minus_1 = std::abs(a[index_mid - 1] - b_el);
        }
        int diff_mid_plus_1 = std::numeric_limits<int>::max();
        if(index_mid + 1 <= high) {
            diff_mid_plus_1 = std::abs(a[index_mid + 1] - b_el);
        }
        // call find_closest_el for plus or minus (depends which is smaller) or return diff_mid   
        if(diff_mid < diff_mid_minus_1 && diff_mid < diff_mid_plus_1) {
            return diff_mid;
        } else if(diff_mid > diff_mid_minus_1) {
            return find_closest_el(a, low, index_mid - 1, b_el);
        } else {
            find_closest_el(a, index_mid + 1, high, b_el);
        }      
    }
    return std::numeric_limits<int>::max();
}

/**
 * Optimal if arrays are significantly different in size
 */
int smallestDifferenceOptimalSize(int a[], int size_a, int b[], int size_b) {
    int smallest_diff = std::numeric_limits<int>::max();
    if(size_a < size_b) {
        sort(a, size_a);
        for(int i = 0; i < size_b; i++) {
            int closest_el = find_closest_el(a, 0, size_a - 1, b[i]);
            if(closest_el < smallest_diff) smallest_diff = closest_el;
        }
    } else {
        sort(b, size_b);
        for(int i = 0; i < size_a; i++) {
            int closest_el = find_closest_el(b, 0, size_b - 1, a[i]);
            if(closest_el < smallest_diff) smallest_diff = closest_el;
        }
    }
    return smallest_diff;
}

/**
 * Smallest Difference: Given two arrays of integers, compute the pair of values (one value in
 * each array) with the smallest (non-negative) difference. Return the difference.
 * EXAMPLE:
 * Input: {1, 3, 15, 11, 2}, {23, 127, 235, 19, 8}
 * Output: 3. That is, the pair (11, 8)
 */
int main() {
    constexpr int size_a = 5;
    constexpr int size_b = 5;
    int a[size_a] = {1, 3, 15, 11, 2};
    int b[size_b] = {23, 127, 235, 19, 8};
    std::cout << "Enter 1 to solve using brute force, 2 to solve using optimal approach or any other\n"
    "number to solve using optimal approach if the arrays are significantly different in size.\n";
    int method;
    std::cin >> method;
    int smallestDifference;
    if(method == 1) {
        smallestDifference = smallestDifferenceBruteForce(a, size_a, b, size_b);
    } else if(method == 2) {
        smallestDifference = smallestDifferenceOptimal(a, size_a, b, size_b);
    } else {
        smallestDifference = smallestDifferenceOptimalSize(a, size_a, b, size_b);
    }
    std::cout << "Smallest difference between arrays = " << smallestDifference << '\n';
}