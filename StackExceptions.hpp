#ifndef __STACKEXCEPTIONS_HPP
#define __STACKEXCEPTIONS_HPP

#include <exception>

class stack_full_exception : public std::exception {
    virtual const char* what() const throw() {
        return "Stack is full.";
    }
};

class empty_stack_exception : public std::exception {
    virtual const char* what() const throw() {
        return "Stack is empty.";
    }
};

class invalid_stack_command : public std::exception {
    virtual const char* what() const throw() {
        return "Inavlid stack command.";
    }
};


#endif