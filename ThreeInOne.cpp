#include <iostream>
#include "FixedMultiStack.hpp"
#include "MultiStack.hpp"
#include <map>
#include <algorithm>
#include <functional>
#include <sstream>
#include <memory>

template <typename T>
std::map<std::string, std::function<int(BaseStack<T>, int, int)>> get_functions() {
    std::map<std::string, std::function<int(BaseStack<T>, int, int)>> functions;
    functions.emplace("PUSH", [&](BaseStack<T> stack, int stack_num, int value) {
        stack.push(stack_num, value);
        return 0;
    });
    functions.emplace("PEEK", [&](BaseStack<T> stack, int stack_num, int value) {
        return stack.peek(stack_num);
    });
    functions.emplace("POP", [&](BaseStack<T> stack, int stack_num, int value) {
        return stack.pop(stack_num);
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

template <typename T>
void process_stack_operations(BaseStack<T>& base_stack) {
    std::map<std::string, std::function<int(BaseStack<int>, int, int)>> functions = get_functions<int>();
    std::string input;
    std::getchar();
    while(input != "STOP") {
        std::cout << "Please enter command:\n";
        std::getline(std::cin, input);
        std::vector<std::string> command_and_args = str_to_arr(input, ' ');
        std::string command = command_and_args.at(0);
        if((command != "PUSH" && command != "POP" && command != "PEEK") || command_and_args.size() < 2) {
            invalid_stack_command e;
            throw e;
        }
        std::vector<std::string> args(command_and_args.begin() + 1, command_and_args.end());
        try {
            if(args.size() > 1) {
                functions[command](base_stack, std::stoi(args[0]), std::stoi(args[1]));
            } else {
                std::cout << "result = " << functions[command](base_stack, std::stoi(args[0]), 0) << "\n";
            }
        } catch(const std::exception& e) {
            invalid_stack_command exc;
            throw exc;
        }
        base_stack.print_status();
    }
    return;
}

/**
 * Describe how you could use a single array to implement three stacks.
 * This program is uses FixedMultiStack ot MultiStack and pushes, pulls and peeks values.
 * example of command to push on stack 2 value 3 : PUSH 2 3 
 * example of command to pop from stack 2 : POP 2 
 * example of command to PEEK from stack 2 : PEEK 2 
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
    if(stack_type == 1) {
        std::shared_ptr<FixedMultiStack<int>> stack(new FixedMultiStack<int>(number_of_stacks, stack_size));
        process_stack_operations(*stack);
    } else {
        std::shared_ptr<MultiStack<int>> stack(new MultiStack<int>(number_of_stacks, stack_size));
        process_stack_operations(*stack);
    }
}