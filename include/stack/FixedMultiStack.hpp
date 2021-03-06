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
            values[get_top_position(stack_num) + 1] = value;
            sizes[stack_num]++;
        }
        T pop(const int& stack_num) override {
            bool empty = is_empty(stack_num);
            if(is_empty(stack_num)) {
                empty_stack_exception e;
                throw e;
            }
            int index = get_top_position(stack_num);
            T value = values.at(index);
            values[index] = 0;
            sizes[stack_num]--;
            std::cout << "Popped value = " << value << '\n';
            return value;
        }
        T peek(const int& stack_num) const override {
            if(is_empty(stack_num)) {
                empty_stack_exception e;
                throw e;
            }
            T value = values.at(get_top_position(stack_num));
            std::cout << "Peeked value = " << value << '\n';
            return value;
        }
        void print_status() const override {
            std::cout << "============\n";
            std::cout << "Stack status\n";
            std::cout << "============\n";
            for(int stack_num = 0; stack_num < BaseStack<T>::_number_of_stacks; stack_num++) {
                std::cout << "\t-------------------------\n";
                std::cout << "\tstack no. " << stack_num << '\n';
                std::cout << "\t-------------------------\n";
                std::cout << "\tsize = " << sizes[stack_num] << '\n';
                std::cout << "\tcapacity = " << BaseStack<T>::_size << '\n';
                std::cout << "\tstack elements: " << '\n';
                int start_index = stack_num * BaseStack<T>::_size;
                for(int j = start_index; j < start_index + sizes[stack_num]; j++) {
                    std::cout << "\t\t" << values[j] << "\n";
                }
            }
        }
    private:
        bool is_empty(const int& stack_num) const {
            return sizes[stack_num] == 0;
        }
        bool is_full(const int& stack_num) const {
            return sizes[stack_num] == this -> _size;
        }
        int get_top_position(const int& stack_num) const {
            int offset = BaseStack<T>::_size * stack_num;
            return (sizes[stack_num] - 1) + offset;
        }
        void initialize() {
            for(int i = 0; i < BaseStack<T>::_number_of_stacks; i++) {
                sizes.push_back(0);
            }
            for(int i = 0; i < BaseStack<T>::_number_of_stacks * BaseStack<T>::_size; i++) {
                values.push_back(0);
            }
        }
        std::vector<T> values;
        std::vector<int> sizes;
        bool initialized = false;
};