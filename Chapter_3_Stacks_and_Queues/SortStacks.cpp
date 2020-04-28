#include <iostream>
#include <stack>

class Person {
    public:
        Person(int age, std::string name) : _age(age), _name(name) {}
        bool operator < (const Person& str) const {
            return (_age < str._age);
        }
        friend std::ostream& operator<<(std::ostream& os, const Person& p);
    private:
        int _age;
        std::string _name;
};

std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << p._name;
    return os;
}

template <typename T>
void sort_stack(std::stack<T>& stack) {
    std::stack<T> sorted_stack;
    while (!stack.empty()) {
        T value = stack.top();
        stack.pop();
        while (!sorted_stack.empty() && value < sorted_stack.top()) {
            T tmp = sorted_stack.top();
            sorted_stack.pop();
            stack.push(tmp);
        }
        sorted_stack.push(value);
    }
    while (!sorted_stack.empty()) {
        T value = sorted_stack.top();
        sorted_stack.pop();
        stack.push(value);
    }
}

template <typename T>
void print_stack_values(const std::stack<T>& stack) {
    std::stack<T> tmp = stack;
    while (!tmp.empty()) {
        std::cout << tmp.top() << '\n';
        tmp.pop();
    }
}

/**
 * Write a program to sort a stack such that the smallest items are on the top.
 * You can use an additional temporary stack, but you may not copy the elements
 * into any other data structure (such as an array). The stack supports the 
 * following operations: push, pop, peek and isEmpty.
 */
int main() {
    std::cout << "==========================\n"
                 "Program for sorting stack.\n"
                 "==========================\n";
    std::string input;
    std::stack<int> stack;
    std::cout << "Enter stack values:\n";
    while(true) {
        std::getline(std::cin, input);
        if(input == "STOP") {
            break;
        }
        try {
            stack.push(std::stoi(input));
        } catch(...) {
            break;
        }
    }   
    sort_stack(stack);
    std::cout << "Sorted stack values:\n";
    print_stack_values(stack);
    std::cout << "===================\n"
                 "Now test people :) \n"
                 "===================\n";
    Person p1(14, "ana");
    Person p2(9, "mario");
    Person p3(25, "lovro");
    std::stack<Person> people_stack;
    people_stack.push(p1);
    people_stack.push(p2);
    people_stack.push(p3);
    std::cout << "Sorted people:\n";
    sort_stack(people_stack);
    print_stack_values(people_stack);
}