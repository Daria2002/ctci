#include <iostream>
#include <vector>
#include <algorithm>

class BitSet {
    public:
        BitSet(int s) : size((s >> 5) + 1) {
            // initialize elements to 0
            for(int i = 0; i < size; i++) elements.push_back(0);
        }
        bool get(int position) {
            int int_index = (position >> 5); // divide by 32
            int bit_index = (position & 0x1F); // mod 32
            return (elements[int_index] & (1 << bit_index)) != 0;
        }
        void set(int position) {
            int int_index = (position >> 5);
            int bit_index = (position & 0x1F);
            elements[int_index] |= (1 << bit_index);
        }
    private:
        int size;
        std::vector<int> elements;
};

void check_duplicates(std::vector<int> nums) {
    BitSet bitset(32000);
    for(int i = 0; i < nums.size(); i++) {
        int num = nums[i];
        int num0 = num - 1; // bitset starts at 0 and nums at 1
        if(bitset.get(num0)) std::cout << num << '\n';
        else bitset.set(num0);
    }
}

/**
 * You have an array with all the numbers from 1 to N, where N is at most 32,000. The
 * array may have duplicate entries and you do not know what N is. With only 4 kilobytes 
 * of memory available, how would you print all duplicate elements sin the array? 
 */
int main() {
    std::vector<int> nums; 
    int n = 0;
    int index = 0;
    for(int i = 0; i < 20; i++) {
        // push twice dups(5, 18, 20)
        if(i == 5 || i == 18 || i == 19) nums.push_back(i); 
        nums.push_back(i);
    }
    check_duplicates(nums);
}
