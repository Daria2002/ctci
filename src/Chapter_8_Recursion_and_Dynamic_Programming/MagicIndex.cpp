#include <iostream>
#include <algorithm>

int magic_index_bf(int arr[], int size) {
    for(int i = 0; i < size; i++) {
        if(arr[i] == i) {
            return i;
        }
    }
    return -1;
}

int magic_index_optimized(int arr[], int start, int stop) {
    if(stop < start) {
        return -1;
    }
    int mid = (start + stop) / 2;
    if(arr[mid] == mid) {
        return mid;
    }
    if(arr[mid] > mid) { // on left
        return magic_index_optimized(arr, start, mid - 1);
    } else { // on right
        return magic_index_optimized(arr, mid + 1, stop);
    }
}

int magic_index_optimized(int arr[], int size) {
    return magic_index_optimized(arr, 0, size - 1);
}

int magic_index_not_distict_el(int arr[], int start, int stop) {
    if(stop < start) return -1;
    int mid =  (start + stop) / 2;
    if(mid == arr[mid]) return mid;
    int index = magic_index_not_distict_el(arr, 0, std::min(mid - 1, arr[mid]));
    if(index != -1) {
        return index;
    }
    index = magic_index_not_distict_el(arr, std::max(mid + 1, arr[mid]), stop);
    if(index != -1) {
        return index;
    }
    return -1;
}

int magic_index_not_distict_el(int arr[], int size) {
    return magic_index_not_distict_el(arr, 0, size - 1);
}

/**
 * A magic index in an array A[1..n-1] is defined to be an index such that A[i] = i.
 * Given a sorted array of distinct integers, write a method to find a magic index,
 * if one exists, in array A.
 * FOLLOWUP:
 * What if the values are not distinct?
 */ 
int main() {
    constexpr int size = 11;
    int arr[size] = {-10, -5, 2, 2, 2, 3, 4, 5, 9, 12, 13};
    int index, method;
    std::cout << "Enter 1 for brute force, 2 for optimized or any other number for "
                 "algorithm that can handle elements that are not distinct\n";
    std::cin >> method;
    switch (method)
    {
    case 1:
        index = magic_index_bf(arr, size);
        break;
    case 2:
        index = magic_index_optimized(arr, size);
        break;
    default:
        index = magic_index_not_distict_el(arr, size);
        break;
    }
    if(index == -1) {
        std::cout << "Magic index is not found.\n";
        return 0;
    }
    std::cout << "Magic index is " << index << ".\n";
}
