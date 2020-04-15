#include "StackExceptions.hpp"
#include <vector>

class MultiStack {
    public:
        MultiStack(const int& number_of_stacks, const int& default_size) : 
        _number_of_stacks(number_of_stacks), _default_size(default_size) {
            total_capacity = number_of_stacks * default_size;
        }

        int pop(const int& stack_num) {
            StackInfo stack = info[stack_num];
            if(stack.is_empty()) {
                empty_stack_exception e;
                throw e;
            }
            int value = values[stack.last_element_index()];
            stack._size--;
            values[stack.last_element_index()] = 0;
            return value;
        }

        int peek(const int& stack_num) {
            StackInfo stack = info[stack_num];
            return values[stack.last_element_index()];
        }

        bool all_stacks_are_full() {
            for(StackInfo stack : info) {
                if(!stack.is_full()) {
                    return false;
                }
            }
            return true;
        }

        void shift(const int& stack_num) {

        }

        void expand(const int& stack_num) {
            shift((stack_num + 1) % info.size());
            info[stack_num]._capacity++;
        }

        void push(const int& stack_num, const int& value) {
            if(all_stacks_are_full()) {
                stack_full_exception e;
                throw e;
            }
            StackInfo stack = info[stack_num];
            if(stack.is_full()) {
                expand(stack_num);
            }
            values[stack.last_element_index()] = value;
            stack._size++;
        }

    private:
        class StackInfo {
            public: 
                int _start, _capacity, _size;
                StackInfo(const int& start, const int& capacity) : _start(start), _capacity(capacity) {

                }
                bool is_empty() {
                    return _size == 0;
                }
                bool is_full() {
                    return _capacity == _size;
                }
                int last_element_index() {
                    return adjust_index(_start + _size - 1);
                }
        };

        static int adjust_index(int index) {
            return (index % total_capacity);
        }

        int _number_of_stacks;
        int _default_size;
        std::vector<StackInfo> info;
        std::vector<int> values;
        static int total_capacity;
};