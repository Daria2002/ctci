#include <iostream>
#include <vector>
#include "../include/stack/StackExceptions.hpp"
#include <map>
#include <functional>
#include <sstream>
#include <memory>
#include <exception>

class StackNode {
    public:
        StackNode() {}
        StackNode(int value) : _value(value) {}
        StackNode* _below;
        StackNode* _above;
        int _value;
};

class Stack {
    public:
        int _capacity;
        StackNode _top;
        StackNode _bottom;
        int _size = 0;

        Stack() {}
        Stack(int capacity) : _capacity(capacity) {}
        
        bool empty() {
            return _size == 0;
        }

        bool push(const int value) {
            if(_size >= _capacity) {
                return false;
            }
            _size++;
            StackNode* new_stack_node = new StackNode(value);
            if(_size == 1) {
                _bottom = *new_stack_node;
            }
            if(_size != 1) {
                new_stack_node->_below = new StackNode(_top._value);
            }
            _top = *new_stack_node;
            return true;
        }

        int size() {
            return _size;
        }

        int top() {
            return _top._value;
        }
        
        int pop() {
            int old_top_value = _top._value;
            _size--;
            if(_top._below != nullptr) {
                _top = *(_top._below);
            }
            _top._above = nullptr;
            return old_top_value;
        }

        int remove_bottom() {
            int bottom_value = _bottom._value;
            if(_bottom._above != nullptr) {
                _bottom = *(_bottom._above);
            }
            if(&_bottom != nullptr) {
                _bottom._below == nullptr;
            }
            _size--;
            return bottom_value;
        }
};

class SetOfStacks {
    public:
        SetOfStacks(int capacity) : _capacity(capacity) {}

        void push(const int value) {
            std::shared_ptr<Stack> top_stack = get_top_stack();
            if(top_stack == nullptr || (*top_stack).empty() || (*top_stack).size() == _capacity) {
                std::shared_ptr<Stack> new_stack = std::make_shared<Stack>(_capacity);
                (*new_stack).push(value);
                stacks.push_back(new_stack);
            } else {
                (*top_stack).push(value);
            }
        }

        int pop() {
            if(stacks.empty()) {
                empty_stack_exception e;
                throw e;
            }
            std::shared_ptr<Stack> top_stack = get_top_stack();
            int top_value = (*top_stack).top();
            (*top_stack).pop();
            if((*top_stack).empty()) {
                stacks.erase(stacks.begin() + stacks.size() - 1);
            }
            return top_value;
        }

        int pop_at(const int substack_index) {
            left_shift(substack_index, true);
        }

        int left_shift(const int substack_index, const bool remove_top) {
            std::shared_ptr<Stack> stack = stacks.at(substack_index);
            int removed_item;
            if(remove_top) {
                removed_item = (*stack).pop();
            } else {
                removed_item = (*stack).remove_bottom();
            }
            if((*stack).empty()) {
                stacks.erase(stacks.begin() + substack_index);
            } else if(substack_index + 1 < stacks.size()) {
                int value = left_shift(substack_index + 1, false);
                (*stack).push(value);
            }
            return removed_item;
        }

        void print_status() {
            std::cout << "==================\nStack status\n==================\n";
            std::cout << "Number of substacks = " << stacks.size() << '\n';
            for(int stack_num = 0; stack_num < stacks.size(); stack_num++) {
                std::cout << "Substack no. " << stack_num << '\n';
                Stack stack = *(stacks.at(stack_num));
                while(!stack.empty()) {
                    std::cout << stack.pop() << '\n';
                }
            }
        } 
    private:
        std::vector<std::shared_ptr<Stack>> stacks;
        int _capacity;
        std::shared_ptr<Stack> get_top_stack() {
            if(stacks.empty()) {
                return nullptr;
            }
            return stacks.at(stacks.size() - 1);
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
    functions.emplace("POPAT", [&](SetOfStacks& stack, int value) {
        return stack.pop_at(value);
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
        if((command != "PUSH" && command != "POP" && command != "POPAT") || command_and_args.size() < 1) {
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