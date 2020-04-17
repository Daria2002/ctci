#include <iostream>
#include "FixedMultiStack.hpp"
#include "MultiStack.hpp"
#include <map>
#include <bits/stdc++.h>
#include <algorithm>

template <typename T>
void process_stack_operations(BaseStack<T>& base_stack) {
    return;
}

template <typename T>
std::map<std::string, std::function<int(BaseStack<T>, int, int)>> get_functions() {
    std::map<std::string, std::function<int(BaseStack<T>, int, int)>> functions;
    functions.emplace("PUSH", [&](BaseStack<T> stack, int stack_num, int value) {
        stack.push(stack_num, value);
        return 0;
    });
    functions.emplace("PEEK", [&](BaseStack<T> stack, int stack_num, int value = 0) {
        return stack.peek(stack_num);
    });
    functions.emplace("POP", [&](BaseStack<T> stack, int stack_num, int value = 0) {
        return stack.pop(stack_num);
    });
    return functions;
}

/**
 * Describe how you could use a single array to implement three stacks.
 */
int main() {

    std::cout << "Enter 1 to use FixedMultiStack or 2 to use MultiStack with stack flexible size:\n";
    int stack_type;
    std::cin >> stack_type;
    if(stack_type != 1 && stack_type != 2) {
        std::cout << "Non of the proposed stack types was selected.\n";
        return 0; 
    }
    std::cout << "Enter stack size:\n";
    int stack_size;
    std::cin >> stack_size;
    std::cout << "Enter number of stacks:\n";
    int number_of_stacks;
    std::cin >> number_of_stacks;
    BaseStack<int> stack;
    if(stack_type == 1) {
        stack = FixedMultiStack<int>(number_of_stacks, stack_size);
    } else {
        stack = MultiStack<int>(number_of_stacks, stack_size);
    }
    std::map<std::string, std::function<int(BaseStack<int>, int, int)>> functions = get_functions<int>();
    process_stack_operations(stack);
}