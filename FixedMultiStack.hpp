#include "StackExceptions.hpp"
#include <iostream>
#include <vector>
#include "BaseStack.hpp"

/**
 * Implementation of three stacks using one array.
 * stack_num is 0, 1 or 2
 */
template <typename T>
class FixedMultiStack : public BaseStack<T> {
    public:
        using BaseStack<T>::BaseStack;
        void push(const int& stack_num, const T& value) {
            if(is_full(stack_num)) {
                stack_full_exception e;
                throw e;
            }
            values[get_top_position(stack_num)] = value;
            sizes[stack_num]++;
        }
        T pop(const int& stack_num) {
            if(is_empty(stack_num)) {
                empty_stack_exception e;
                throw e;
            }
            int index = get_top_position(stack_num);
            T value = values[index];
            values[index] = 0; // clear value
            sizes[stack_num]--;
            return value;
        }
        T peek(const int& stack_num) {
            if(is_empty(stack_num)) {
                empty_stack_exception e;
                throw e;
            }
            return values[get_top_position(stack_num)];
        }
    private:
        bool is_empty(const int& stack_num) const {
            return sizes[stack_num] == 0;
        }
        bool is_full(const int& stack_num) {
            return sizes[stack_num] == BaseStack<T>::_size;
        }
        int get_top_position(const int& stack_num) {
            int offset = BaseStack<T>::_size * stack_num;
            return (sizes[stack_num] - 1) + offset;
        }
        std::vector<T> values;
        std::vector<int> sizes;
};