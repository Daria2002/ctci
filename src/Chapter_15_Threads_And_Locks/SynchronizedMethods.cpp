#include <iostream>

/**
 * Synchronized Methods: You are given a class with synchronized method
 * A and a normal method B. If you have two threads in one instance of a
 * program, can they both execute A at the same time? Can they execute
 * A and B at the same time?
 */
int main() {
    std::cout << "The key concept to remember is that only one\n"
                 "synchronized method can be in execution per instance\n"
                 "of the object. Other threads can execute non-synchronized\n"
                 "methods on that instance, or they can execute any method\n"
                 "on a different instance of the object\n";
}