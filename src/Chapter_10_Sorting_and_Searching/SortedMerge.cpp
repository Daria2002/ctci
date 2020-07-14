#include <iostream>
#include <array>

void merge(std::array<int, 7>& a, std::array<int, 3>& b, int last_a, int last_b) {
    int current = last_a + last_b + 1; // end of merged array
    // merge a and b, starting from the last element
    while (last_b >= 0) {
        // last element in a is greater than the last element in b
        if(last_a >= 0 && a[last_a] > b[last_b]) {
            a[current] = a[last_a];
            last_a--;
        } else {
            a[current] = b[last_b];
            last_b--;
        }
        current--;
    }
    // there is no need to copy the contents of a after running out of b.
    // they are already in place.
}

/**
 * You are given two sorted arrays, A and B, where A has a large enough buffer at the 
 * end to hold B. Write a method to merge B into A in sorted order. 
 */
int main() {
    std::array<int, 7> a = {12, 34, 75, 92};
    std::array<int, 3> b = {10, 23, 54};
    merge(a, b, 3, 2);
    for(int i = 0; i < a.size(); i++) {
        std::cout << a[i] << '\n';
    }
}
