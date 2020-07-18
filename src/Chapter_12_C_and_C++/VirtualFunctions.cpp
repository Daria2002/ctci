#include <iostream>

class Shape {
    public:
        int edge_len;
        virtual int circumference() {
            std::cout << "Circumference of Base Class\n";
            return 0;
        }
};

class Triangle : public Shape {
    public:
        int circumference() {
            std::cout << "Circumference of Triangle Class\n";
            return 3 * edge_len;
        }
};

/**
 * How do virtual functions work in C++? 
 */
int main() {
    Shape* x = new Shape();
    x -> circumference(); // "Circumference of Base Class"
    Shape* y = new Triangle();
    y -> circumference(); // "Circumference of Triangle Class"
    std::cout << "A virtual function depends on virtual function or vtable. If any function\n"
    "of a class is declared to be virtual, a vtable is constructed which stores addressed of\n"
    "the virtual functions of this class. The compiler also adds a hidden vptr variable in\n"
    "all such classes which points to the vtable of that class. If a virtal function is not\n"
    "overridden in the derived class, the vtable of the derived class stores address of the\n"
    "in its parent class. The vtable is used to resolve the address of the function when the\n"
    "virtual function is called. Dynamic binding in C++ is performed through the vtable mechanism.\n"
    "Thus, when we assign the derived class object to the base class pointer, the vptr variable\n"
    "points to the vtable of the derived class. This assignment ensures that the most derived\n"
    "virtual function gets called. In the above example, circumference is a virtual function in\n"
    "the Shape class, so it becomes virtual in each of the derived classes (Triangle, etc.).\n"
    "C++ non-virtual function calls are resolved at compile time with static binding, while\n"
    "virtual function calls are resolved at runtime with dynamic binding.\n";
}
