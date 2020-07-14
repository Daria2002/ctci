#include <iostream>
#include <vector>

int search(std::vector<int>& nums, int x, int l, int r) {
    int mid = (l + r) / 2;
    if(x == nums[mid]) {
        return mid;
    }
    if(r < l) {
        return -1;
    }
    // find normally ordered half
    if(nums[l] < nums[mid]) {   // left half is normally ordered
        if(x >= nums[l] && x <= nums[mid]) { // search left
            return search(nums, x, l, mid - 1);
        } else { // search right
            return search(nums, x, mid + 1, r);
        }
    } else if(nums[mid] < nums[l]) { // right half is normally ordered
        if(x >= nums[mid] && x <= nums[r]) { // search right
            return search(nums, x, mid + 1, r);
        } else { // search left
            return search(nums, x, l, mid - 1);
        }
    } else if(nums[l] == nums[mid]) { // there are duplicates
        if(nums[mid] != nums[r]) { // if right different from mid el, search it
            return search(nums, x, mid + 1, r);
        } else { // search both halves
            int result = search(nums, x, l, mid - 1); // search left
            if(result == -1) return search(nums, x, mid + 1, r);
            else return result;
        }
    }
    return -1;
}

int search(std::vector<int>& nums, int x) {
    return search(nums, x, 0, nums.size() - 1);
}

/**
 * Given a sorted array of n integers that has been rotated an unknown 
 * number of times, write code to find an element in the array. 
 * You may assume that the array was originally sorted in increasing order.
 * EXAMPLE:
 * Input: find 5 in {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14}
 * Output: 8 (the index of 5 in the array) 
 */
int main() {
    std::vector<int> nums = {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14};
    int x = 5;
    std::cout << "Index of element " << x << " is " << search(nums, x) << ".\n";
}
