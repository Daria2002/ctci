#include <iostream>
#include <vector>

class Listy {
    public:
        int elementAt(int i) {
            return i > v.size() ? -1 : v[i];
        }
        void add(std::vector<int> elements) {
            v = elements;
        }
    private:
        std::vector<int> v;
};

int binary_search(Listy listy, int element, int start, int end) {
    if(start <= end) {
        int mid_index = (start + end) / 2;
        int mid = listy.elementAt(mid_index);
        if(mid == element) return mid_index;
        else if(listy.elementAt(mid) < element) return binary_search(listy, element, start, mid_index - 1);
        else return binary_search(listy, element, mid_index + 1, end);
    }
}

int search(Listy listy, int element) {
    int index = 1;
    while (listy.elementAt(index) != -1 && listy.elementAt(index) < element) {
        index *= 2;
    }
    return binary_search(listy, element, index/2, index);
}

/**
 * You are given an array-like data structure Listy which lacks a size
 * method. It does, however, have an elementAt (i) method that returns the element at index i in 
 * 0(1) time. If i is beyond the bounds of the data structure, it returns -1. (For this reason, the data 
 * structure only supports positive integers.) Given a Listy which contains sorted, positive integers,
 * find the index at which an element x occurs. If x occurs multiple times, you may return any index. 
 */
int main() {
    Listy listy;
    std::vector<int> v = {1, 2, 7, 9, 10, 13, 18};
    listy.add(v);
    int element = 9;
    std::cout << "Index of " << element << " is " << search(listy, element) << ".\n";
}