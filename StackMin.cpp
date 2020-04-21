#include <iostream>
#include "BaseStack.hpp"
#include <vector>
#include <map>
#include <functional>
#include <sstream>
#include "StackExceptions.hpp"
#include <memory>

class StackNode {
    public:
        StackNode(const int value, const int min) : _value(value), _min(min) {}
        int _min;
        int _value;
};

class StackMin {
    public:
        StackMin() {}
        virtual int get_min() const = 0;
        virtual void push(const int value) = 0;
        virtual int peek() const = 0;
        virtual int pop() = 0;
        virtual void print_status() const = 0;
};

class StackMinWithSpecialStackNode : public StackMin {
    public:
        StackMinWithSpecialStackNode() : StackMin() {}

        int get_min() const override {
            return values[values.size() - 1]._min;
        }

        void push(const int value) override {
            int min = get_min();
            StackNode new_stack(value, ((min < value) ? min : value));
            values.push_back(new_stack);
        }

        int peek() const override {
            int value = values[values.size() - 1]._value;
            std::cout << "Peeked value = " << value << '\n';
            return value;
        }

        int pop() override {
            int value = values[values.size() - 1]._value;
            values.pop_back();
            std::cout << "Popped value = " << value << '\n';
            return value;
        }

        void print_status() const override {
            std::cout << "Top value = " << peek() << '\n';
            std::cout << "Min value = " << get_min() << '\n';
        }

    private:
        std::vector<StackNode> values;
};

class StackMinWithExtraStack : public StackMin {
    public:
        StackMinWithExtraStack() : StackMin() {}

        int get_min() const override {
            return values[values.size() - 1]._min;
        }

        void push(const int value) override {
            int min = get_min();
            StackNode new_stack(value, ((min < value) ? min : value));
            values.push_back(new_stack);
        }

        int peek() const override {
            return values[values.size() - 1]._value;
        }

        int pop() override {
            int value = values[values.size() - 1]._value;
            values.pop_back();
            return value;
        }

        void print_status() const override {

        }

    private:
        std::vector<StackNode> values;
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
    std::getchar();
    while(input != "STOP") {
        std::cout << "Please enter command:\n";
        std::getline(std::cin, input);
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
    }
    return;
}

int main() {
    std::cout << "===========================================\n";
    std::cout << "Program to process operations with StackMin\n";
    std::cout << "===========================================\n";
    
    int method;
    std::cout << "Enter 1 to use stack with special StackNode(value and min of"
    << " substack. Enter 2 to use stack with help stack used to track min:\n";
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