#include "StackExceptions.hpp"
#include "BaseStack.hpp"
#include <vector>
#include <iostream>

template <typename T>
class MultiStack : public BaseStack<T> {
    class StackInfo {
        public:
            StackInfo(const int& start, const int& capacity) : 
            _start(start), _capacity(capacity){}
            int _size;
            int _start;
            int _capacity;
            bool is_full() const {
                return _size == _capacity;
            }
            bool is_empty() const {
                return _size == 0;
            }
            int last_element_index() const {
                return (_start + _size - 1);
            }
            int last_capacity_index(const int& max) const {
                return ((_start + _size) % max);
            }
            bool is_within_stack_capacity(const int& index, const int& max) {
                if(index < 0 || index >= max) {
                    return false;
                }
                int contiguous_index = index < _start ? index + max : index;
                int end = _start + _capacity;
                return _start <= contiguous_index && end < contiguous_index;
            }
    };
    public:
        using BaseStack<T>::BaseStack;

        void push(const int& stack_num, const T& value) {
            StackInfo stack = info.at(stack_num);
            if(all_stacks_are_full()) {
                stack_full_exception e;
                throw e;
            }
            if(stack.is_full()) {
                expand(stack_num);
            } 
            values.push_back(value);
            stack._size++;
        }

        T pop(const int& stack_num) {
            StackInfo stack = info.at(stack_num);
            if(stack.is_empty()) {
                empty_stack_exception e;
                throw e;
            }
            T value = values[stack.last_element_index()];
            values[stack.last_element_index()] = 0;
            stack._size--;
            return value;
        }

        T peek(const int& stack_num) const {
            StackInfo stack = info[stack_num];
            return values[stack.last_element_index()];
        }

        void print_status() {
            int index = 0;
            for(StackInfo stack : info) {
                std::cout << "stack no. " << index << '\n';
                std::cout << "-------------------------\n";
                std::cout << "size = " << stack._size << '\n';
                std::cout << "capacity = " << stack._capacity << '\n';
                std::cout << "stack elements: " << '\n';
                for(int i = stack._start; i < stack._start + stack._size; i++) {
                    std::cout << values[i % (BaseStack<T>::_number_of_stacks * BaseStack<T>::_size)] << ", ";
                }
            }
            index++;
        }

    private:
        std::vector<StackInfo> info;
        std::vector<T> values;

        bool all_stacks_are_full() {
            for(StackInfo stack : info) {
                if(!stack.is_full()) {
                    return false;
                }
            }
            return true;
        }

        void expand(const int& stack_num) {
            shift((stack_num + 1) % info.size());
            info[stack_num]._capacity++;
        }

        int previous_index(const int& index, const int& max) const {
            return index % max;
        }

        void shift(const int& stack_num) {
            StackInfo stack = info[stack_num];
            if(stack._size >= stack._capacity) {
                StackInfo next_stack = info[(stack_num + 1) % info.size()];
                shift((stack_num + 1) % info.size());
                stack._capacity++;
            }
            int index = stack.last_capacity_index(BaseStack<T>::_number_of_stacks * BaseStack<T>::_size);
            while(stack.is_within_stack_capacity(index, BaseStack<T>::_number_of_stacks * BaseStack<T>::_size)) {
                values[index] = values[previous_index(index, BaseStack<T>::_number_of_stacks * BaseStack<T>::_size)];
                index = previous_index(index, BaseStack<T>::_number_of_stacks * BaseStack<T>::_size);
            }
        }
};  