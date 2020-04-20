#ifndef __BASESTACK_HPP
#define __BASESTACK_HPP

template <typename T>
class BaseStack {
    public:
        BaseStack() {}
        BaseStack(const int& number_of_stacks, const int& default_size) :
        _number_of_stacks(number_of_stacks), _size(default_size) {}
        virtual void push(const int& stack_num, const T& value) = 0;
        virtual T pop(const int& stack_num) = 0;
        virtual T peek(const int& stack_num) const = 0; // pure virtual function (without "=0" is virtual function)
        virtual void print_status() const = 0;
    protected:
        int _number_of_stacks;
        int _size;
};
#endif