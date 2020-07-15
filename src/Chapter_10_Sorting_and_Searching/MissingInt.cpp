#include <iostream>
#include <algorithm>
#include <cstddef>
#include <vector>
#include <limits>

void initialize_nums(std::vector<int>& nums, int missing_int) {
    int x = 0; 
    std::generate(nums.begin(), nums.end(), [&] { 
        if(x == missing_int) x++; // skip missing_int
        return x++; 
    });
}

int find_open_num(std::vector<int> nums) {
    std::vector<std::byte> bit_field( std::numeric_limits<int>::max() / 8); // int8_t = 8 bits = 1 byte
    // initialize bit_field
    for(int i = 0; i < std::numeric_limits<int>::max() / 8; i++) {
        bit_field.push_back(std::byte(0));
    }
    // set 1 to bits with value same to the i
    for(int i = 0; i < nums.size(); i++) {
        bit_field[nums[i] / 8] |= std::byte((1 << (nums[i] % 8)));
    }
    for(int i = 0; i < bit_field.size(); i++) {
        for(int j = 0; j < 8; j++) {
            if((bit_field[i] & std::byte(1 << j)) == std::byte(0)) {
                return (i * 8 + j);
            }
        }
    }
    return -1;
}

std::vector<int> count_elements_in_range(std::vector<int> nums, int range_size) {
    std::vector<int> counter(1 << 21);
    for(int i = 0; i < nums.size(); i++) {
        counter[i/range_size]++;
    }
    return counter;
}

int find_block_with_missing(std::vector<int> blocks, int range_size) {
    for(int i = 0; i < blocks.size(); i++) {
        if(blocks[i] < range_size) return i; 
    }
    return -1;
}

std::vector<std::byte> get_bit_vector(std::vector<int> nums, int block_index, int range_size) {
    int start_range = block_index * range_size;
    int end_range = block_index + range_size;
    std::vector<std::byte> bit_vector(range_size/8);
    for(int i = 0; i < nums.size(); i++) {
        int val = nums[i];
        if(val >= start_range && val < end_range) {
            int offset = val - start_range;
            int mask = (1 << (offset % 8));
            bit_vector[offset / 8] |= std::byte(mask); 
        }
    }
    return bit_vector;
}

int find_zero(std::byte b) {
    for(int i = 0; i < 8; i++) {
        int mask = 1 << i;
        if((b & std::byte(mask)) == std::byte(0)) return i;
    }
    return -1;
 }
 
 int find_zero(std::vector<std::byte> bit_vector) {
    for(int i = 0; i < bit_vector.size(); i++) {
        int all_ones = ~0;
        if(bit_vector[i] != std::byte(all_ones)) { // if not all 1s
        int bit_index = find_zero(bit_vector[i]);
        return i * 8 + bit_index;
        }
    }
    return -1;
 }

int find_open_num_less_memory(std::vector<int> nums) {
    int range_size = (1 << 20); // 2^20 bits = 2^17 bytes
    std::vector<int> blocks = count_elements_in_range(nums, range_size);
    int block_index = find_block_with_missing(blocks, range_size);
    if(block_index < 0) return -1;
    std::vector<std::byte> bit_vector = get_bit_vector(nums, block_index, range_size);
    int offset = find_zero(bit_vector);
    if(offset < 0) return -1;
    return block_index * range_size + offset;
}

/**
 * Given an input file with four billion non-negative integers, provide an algorithm to
 * generate an integer that is not contained in the file. Assume you have 1 GB of memory available for
 * this task.
 * FOLLOW_UP:
 * What if you have only 10MB of memory? Assume that all the values are distinct and we now have
 * no more than one billion non-negative integers. 
 */
int main() {
    std::vector<int> nums(30);
    int missing_int = 16;
    initialize_nums(nums, 16);
    std::cout << "Detected missing int (1GB memory) is " << find_open_num(nums) << ".\n"; 
    std::cout << "Detected missing int (10MB memory) is " << find_open_num_less_memory(nums) << ".\n";
}
