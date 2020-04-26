#include <iostream>
#include <stack>
#include "StackExceptions.hpp"
#include <map>
#include <vector>
#include <functional>
#include <sstream>

template <typename T>
class MyQueue {
    public:
        MyQueue() {}
        void add(const T& value) {
            stack_newest.push(value);
        }
        T remove() {
            if(is_empty()){
                empty_stack_exception e;
                throw e;
            }
            if(stack_oldest.empty()) {
                move_elements_to_stack_newest();
            }
            int value = stack_oldest.top();
            stack_oldest.pop();
            std::cout << "Removed value = " << value << '\n';
            return value;
        }
        T peek() {  
            if(is_empty()){
                empty_stack_exception e;
                throw e;
            }
            if(stack_oldest.empty()) {
                move_elements_to_stack_newest();
            }
            int value = stack_oldest.top();
            std::cout << "Peeked value = " << value << '\n';
            return value;
        }
        bool is_empty() {
            return (stack_newest.empty() && stack_oldest.empty());
        }
        int size() {
            return (stack_newest.size() + stack_oldest.size());
        }
    private:
        std::stack<T> stack_newest;
        std::stack<T> stack_oldest;
        void move_elements_to_stack_newest() {
            while (!stack_newest.empty()) {
                stack_oldest.push(stack_newest.top());
                stack_newest.pop();
            }
        }
};

template <typename T>
std::map<std::string, std::function<int(MyQueue<T>&, int)>> get_functions() {
    std::map<std::string, std::function<int(MyQueue<T>&, int)>> functions;
    functions.emplace("ADD", [&](MyQueue<T>& queue, int value) {
        queue.add(value);
        return 0;
    });
    functions.emplace("REMOVE", [&](MyQueue<T>& queue, int value) {
        return queue.remove();
    });
    functions.emplace("PEEK", [&](MyQueue<T>& queue, int value) {
        return queue.peek();
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
void process_queue_operations(MyQueue<T>& queue) {
    std::map<std::string, std::function<int(MyQueue<T>&, int)>> functions = get_functions<T>();
    std::string input;
    while(true) {
        std::cout << "Please enter command:\n";
        std::getline(std::cin, input);
        if(input == "STOP") {
            std::cout << "Program stopped.\n";
            return;
        }
        std::vector<std::string> command_and_args = str_to_arr(input, ' ');
        std::string command = command_and_args.at(0);
        if((command != "ADD" && command != "REMOVE" && command != "PEEK") || command_and_args.size() < 1) {
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
        functions[command](queue, arg);
    }
    return;
}

/**
 * Implement a MyQueue class which implements a queue using two stacks.
 */
int main() {
    std::cout << "=======================================================\n"
                 "This program represents Queue Via Stack data structure.\n"
                 "=======================================================\n"
                 "Available commands:\n"
                 "1) ADD arg\n2) REMOVE\n3) PEEK\n4) STOP\n";
    MyQueue<int> queue;
    process_queue_operations(queue);
}