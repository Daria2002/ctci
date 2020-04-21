#include <iostream>
#include "BaseStack.hpp"
#include <vector>
#include <map>
#include <functional>
#include <sstream>
#include "StackExceptions.hpp"
#include <memory>
#include <limits>

class StackNode {
    public:
        StackNode(const int value, const int min) : _value(value), _min(min) {}
        int _min;
        int _value;
};

class Stack {
    public:
        virtual void push(const int value) = 0;
        virtual int peek() const = 0;
        virtual int pop() = 0;
        virtual void print_status() const {}
};

class StackWithMins : public Stack {
    public:
        virtual void push(const int value) {
            mins.push_back(value);
        }
        virtual int peek() const {
            if(is_empty()) {
                empty_stack_exception e;
                throw e;
            }
            return mins[mins.size() - 1];
        }
        virtual int pop() {
            if(is_empty()) {
                empty_stack_exception e;
                throw e;
            }
            int value = mins[mins.size() - 1];
            mins.pop_back();
            return value;
        }
    private:
        inline bool is_empty() const {
            return mins.empty();
        }
        std::vector<int> mins;
};

class StackMin : public Stack {
    public:
        StackMin() {}
        virtual int get_min() const = 0;
};

class StackMinWithSpecialStackNode : public StackMin {
    public:
        StackMinWithSpecialStackNode() : StackMin() {}

        int get_min() const override {
            return values[values.size() - 1]._min;
        }

        void push(const int value) override {
            int min = std::numeric_limits<int>::max();
            if(!is_empty()) {
                min = get_min();
            }
            StackNode new_stack(value, ((min < value) ? min : value));
            values.push_back(new_stack);
        }

        int peek() const override {
            if(is_empty()) {
                empty_stack_exception e;
                throw e;
            }
            int value = values[values.size() - 1]._value;
            return value;
        }

        int pop() override {
            if(is_empty()) {
                empty_stack_exception e;
                throw e;
            }
            int value = values[values.size() - 1]._value;
            values.pop_back();
            return value;
        }

        void print_status() const override {
            if(is_empty()) {
                std::cout << "Stack is empty.\n";
                return; 
            }
            std::cout << "Top value = " << peek() << '\n';
            std::cout << "Min value = " << get_min() << '\n';
        }

    private:
        std::vector<StackNode> values;
        bool is_empty() const {
            return values.size() == 0;
        }
};

class StackMinWithExtraStack : public StackMin {
    public:
        StackMinWithExtraStack() : StackMin() {}

        int get_min() const override {
            return mins.peek();
        }

        void push(const int value) override {
            if(values.empty() || value <= mins.peek()) {
                mins.push(value);
            }
            values.push_back(value);
        }

        int peek() const override {
            return values[values.size() - 1];
        }

        int pop() override {
            int value = values[values.size() - 1];
            values.pop_back();
            if(value == get_min()) {
                mins.pop();
            } 
            return value;
        }

        void print_status() const override {
            if(is_empty()) {
                std::cout << "Stack is empty.\n";
                return;
            }       
            std::cout << "Top value = " << peek() << '\n';
            std::cout << "Min value = " << get_min() << '\n';
        }

    private:
        std::vector<int> values;
        StackWithMins mins;
        inline bool is_empty() const {
            return values.empty();
        }
};

std::map<std::string, std::function<int(StackMin&, int)>> get_functions() {
    std::map<std::string, std::function<int(StackMin&, int)>> functions;
    functions.emplace("PUSH", [&](StackMin& stack, int value) {
        stack.push(value);
        return 0;
    });
    functions.emplace("PEEK", [&](StackMin& stack, int value) {
        return stack.peek();
    });
    functions.emplace("POP", [&](StackMin& stack, int value) {
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

void process_stack_operations(StackMin& base_stack) {
    std::map<std::string, std::function<int(StackMin&, int)>> functions = get_functions();
    std::string input;
    std::getline(std::cin, input);
    while(true) {
        std::cout << "Please enter command:\n";
        std::getline(std::cin, input);
        if(input == "STOP") {
            std::cout << "Program stopped.\n";
            return;
        }
        std::vector<std::string> command_and_arg = str_to_arr(input, ' ');
        std::string command = command_and_arg.at(0);
        if((command != "PUSH" && command != "POP" && command != "PEEK") || command_and_arg.size() < 1) {
            invalid_stack_command e;
            throw e;
        }
        int arg;
        try {
            if(command_and_arg.size() > 1) {
                arg = std::stoi(command_and_arg[1]);
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

int main() {
    std::cout << "===========================================\n";
    std::cout << "Program to process operations with StackMin\n";
    std::cout << "===========================================\n";
    
    int method;
    std::cout << "Enter 1 to use stack with special StackNode(value and min of"
    << " substack). Enter 2 to use stack with help stack used to track min:\n";
    std::shared_ptr<StackMin> stack_ptr;
    switch (method){
        case 1:
            stack_ptr = std::make_shared<StackMinWithSpecialStackNode>();
            break;
        case 2:
            stack_ptr = std::make_shared<StackMinWithExtraStack>();
            break;
        default:
            std::cout << "Non of the proposed methods has not been choosen.\n";
            return 0;
    }
    process_stack_operations(*stack_ptr);
}