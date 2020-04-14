#include "StackExceptions.hpp"
#include <iostream>
#include <vector>

/**
 * Implementation of three stacks using one array.
 * stack_num is 0, 1 or 2
 */
class FixedMultiStack {
    public:
        FixedMultiStack(const int& _stack_size) : stack_size(_stack_size) {}
        bool is_full(const int& stack_num) {
            return sizes[stack_num] == stack_size;
        }
        int get_top_position(const int& stack_num) {
            int offset = stack_size * stack_num;
            return (sizes[stack_num] - 1) + offset;
        }
        void push(const int& stack_num, const int& value) {
            if(is_full(stack_num)) {
                stack_full_exception e;
                throw e;
            }
            std::vector<int>::iterator position = values.begin() + get_top_position(stack_num);
            values.insert(position, value);
            sizes[stack_num]++;
        }
        bool is_empty(const int& stack_num) const {
            return sizes[stack_num] == 0;
        }
        int pop(const int& stack_num) {
            if(is_empty(stack_num)) {
                empty_stack_exception e;
                throw e;
            }
            int index = get_top_position(stack_num);
            int value = values[index];
            values[index] = 0; // clear value
            sizes[stack_num]--;
            return value;
        }
        int peek(const int& stack_num) {
            if(is_empty(stack_num)) {
                empty_stack_exception e;
                throw e;
            }
            return values[get_top_position(stack_num)];
        }
    private:
        const int number_of_stacks = 3;
        int stack_size;
        std::vector<int> values;
        std::vector<int> sizes;
};