#ifndef __BASESTACK_HPP
#define __BASESTACK_HPP

template <typename T>
class BaseStack {
    public:
        BaseStack() {}
        BaseStack(const int& number_of_stacks, const int& default_size) :
        _number_of_stacks(number_of_stacks), _size(default_size) {}
        virtual void push(const int& stack_num, const T& value) {};
        virtual T pop(const int& stack_num) {};
        virtual T peek(const int& stack_num) {};
        virtual void print_status() {};
    protected:
        int _number_of_stacks;
        int _size;
};
#endif