#include <iostream>
#include <array>

int search(std::array<std::string, 13> arr, std::string str, int start, int end) {
    if(start > end) return -1;
    int mid_index = (start + end) / 2;
    // if mid is empty, find closest non-empty str
    if(arr[mid_index].empty()) {
        int left = mid_index - 1;
        int right = mid_index + 1;
        while (true)
        {
            if(left < start && right > end) return -1;
            else if(right <= end && !arr[right].empty()) {
                mid_index = right;
                break;
            } else if(left >= start && !arr[left].empty()) {
                mid_index = left;
                break;
            }
            right++;
            left--;
        }
        
    }
    if(arr[mid_index].compare(str) == 0) return mid_index;
    else if(arr[mid_index].compare(str) > 0) return search(arr, str, 0, mid_index - 1);
    else return search(arr, str, mid_index + 1, end);
}

int search(std::array<std::string, 13> arr, std::string str) {
    if(str.empty()) return -1;
    return search(arr, str, 0, arr.size() - 1);
}

/**
 * Given a sorted array of strings that is interspersed with empty strings, write a
 * method to find the location of a given string.
 * EXAMPLE:
 * Input: ball, {"at", "", "", "", "ball", "", "", "car", "", "", "dad", "", ""}
 * Output: 4 
 */
int main() {
    std::array<std::string, 13> arr = {"at", "", "", "", "ball", "", "", "car", "", "", "dad", "", ""};
    std::string str = "ball";
    std::cout << "Index of string \"" << str << "\" is " << search(arr, str) << ".\n";
}