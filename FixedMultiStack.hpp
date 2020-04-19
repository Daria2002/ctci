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
        FixedMultiStack(const int number_of_stacks, const int stack_size) : BaseStack<T>(number_of_stacks, stack_size) {
            initialize();
        }
        void push(const int& stack_num, const T& value) override {
            if(is_full(stack_num)) {
                stack_full_exception e;
                throw e;
            }
            int index = get_top_position(stack_num) + 1;
            if(index < values.size()) {
                values[index] = value;
            } else {
                // + 1 because we want to take next positon 
                values.insert(values.begin() + get_top_position(stack_num) + 1, value);
            }
            sizes[stack_num]++;
        }
        T pop(const int& stack_num) override {
            if(is_empty(stack_num)) {
                empty_stack_exception e;
                throw e;
            }
            int index = get_top_position(stack_num);
            T value = values.at(index);
            values.insert(values.begin() + index, 0);
            sizes[stack_num]--;
            return value;
        }
        T peek(const int& stack_num) override {
            if(is_empty(stack_num)) {
                empty_stack_exception e;
                throw e;
            }
            return values.at(get_top_position(stack_num));
        }
        void print_status() override {
            std::cout << "============\n";
            std::cout << "Stack status\n";
            std::cout << "============\n";
            for(int i = 0; i < BaseStack<T>::_number_of_stacks; i++) {
                std::cout << "\t-------------------------\n";
                std::cout << "\tstack no. " << i << '\n';
                std::cout << "\t-------------------------\n";
                std::cout << "\tsize = " << sizes[i] << '\n';
                std::cout << "\tcapacity = " << BaseStack<T>::_size << '\n';
                std::cout << "\tstack elements: " << '\n';
                int start_index = i * BaseStack<T>::_size;
                for(int j = start_index; j < start_index + BaseStack<T>::_size; j++) {
                    std::cout << "\t\t" << values[j] << "\n";
                }
            }
        }
    private:
        bool is_empty(const int& stack_num) const {
            return sizes[stack_num] == 0;
        }
        bool is_full(const int& stack_num) {
            return sizes[stack_num] == this -> _size;
        }
        int get_top_position(const int& stack_num) {
            int offset = BaseStack<T>::_size * stack_num;
            return (sizes[stack_num] - 1) + offset;
        }
        void initialize() {
            if(sizes.size() == 0) {
                for(int i = 0; i < BaseStack<T>::_number_of_stacks; i++) {
                    sizes.push_back(0);
                }
            }
        }
        std::vector<T> values;
        std::vector<int> sizes;
        bool initialized = false;
};