#include <iostream>
#include <stack>
#include <vector>
#include "StackExceptions.hpp"
#include <map>
#include <functional>
#include <sstream>

class SetOfStacks {
    public:
        SetOfStacks(int capacity) : _capacity(capacity) {}
        void push(const int value) {
            std::stack<int> stack;
            bool set_of_stacks_initialized = get_last_stack(stack);
            std::cout << "adr2 = " << &stack << '\n';
            if(!set_of_stacks_initialized || stack.size() == _capacity) {
                stack.push(value);
                stacks.push_back(stack);
            } else {
                stack.push(value);
            }
        }
        int pop() {
            if(stacks.empty()) {
                empty_stack_exception e;
                throw e;
            }
            std::stack<int> stack = stacks[stacks.size() - 1];
            int top_value = stack.top();
            stack.pop();
            if(stack.empty()) {
                stacks.pop_back();
            }
            return top_value;
        }

        void print_status() {
            std::cout << "==================\nStack status\n==================\n";
            std::cout << "Number of substacks = " << stacks.size() << '\n';
            for(int stack_num = 0; stack_num < stacks.size(); stack_num++) {
                std::stack<int> stack = stacks[stack_num];
                while(!stack.empty()) {
                    std::cout << stack.top() << '\n';
                    stack.pop();
                }
            }
        }
    private:
        std::vector<std::stack<int>> stacks;
        int _capacity;
        bool get_last_stack(std::stack<int>& last_stack) {
            if(stacks.size() == 0) {
                return false;
            }
            last_stack = stacks[stacks.size() - 1];
            std::cout << "adr original = " << &stacks[stacks.size() - 1] << '\n';
            std::cout << "adr1 = " << &last_stack << '\n';
            return true;
        }
};

std::map<std::string, std::function<int(SetOfStacks&, int)>> get_functions() {
    std::map<std::string, std::function<int(SetOfStacks&, int)>> functions;
    functions.emplace("PUSH", [&](SetOfStacks& stack, int value) {
        stack.push(value);
        return 0;
    });
    functions.emplace("POP", [&](SetOfStacks& stack, int value) {
        return stack.pop();
    });
    return functions;
}

std::vector<std::string> str_to_arr(const std::string& str, const char& regex) {
    std::stringstream ss(str);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, regex)) {
        if (item.length() > 0) {
            elems.push_back(item);  
        }
    }
    return elems;
}

void process_stack_operations(SetOfStacks& base_stack) {
    std::map<std::string, std::function<int(SetOfStacks&, int)>> functions = get_functions();
    std::string input;
    std::getchar();
    while(true) {
        std::cout << "Please enter command:\n";
        std::getline(std::cin, input);
        if(input == "STOP") {
            std::cout << "Program stopped.\n";
            return;
        }
        std::vector<std::string> command_and_args = str_to_arr(input, ' ');
        std::string command = command_and_args.at(0);
        if((command != "PUSH" && command != "POP") || command_and_args.size() < 1) {
            invalid_stack_command e;
            throw e;
        }
        int arg;
        try {
            if(command_and_args.size() > 1) {
                arg = std::stoi(command_and_args[1]);
            } else {
                arg = 0;
            }
        } catch(const std::exception& e) {
            invalid_stack_command exc;
            throw exc;
        }
        functions[command](base_stack, arg);
        base_stack.print_status();
    }
    return;
}

/**
 * Imagine a (literal) stack of plates. If the stack gets too high, it might topple.
 * Therefore, in real life, we would likely start a new stack when the previous stack exceeds some threshold.
 * Implement a data structure SetOfStacks that mimics this. SetOfStacks should be composed of several stacks
 * and should create a new stack once the previous one exceeds capacity. SetOfStacks.push() and SetOfStacks.pop()
 * should behave indentically to a single stack (taht is, pop() should return the same value as it would if there
 * were just a single stack.)
 * FOLLOW_UP:
 * Implement a function popAt(int index) whic
            std::cout << "adr2 = " << &stack << '\n';h performs a pop operation on a specific sub-stack
 */
int main() {
    std::cout << "Enter stack capacity:\n";
    int capacity;
    std::cin >> capacity;
    SetOfStacks set_of_stacks(capacity);
    process_stack_operations(set_of_stacks);
}