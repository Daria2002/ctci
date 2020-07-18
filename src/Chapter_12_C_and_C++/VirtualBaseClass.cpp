#include <iostream>

class Foo {
    public:
        void f() {
            std::cout << "Foo f\n";
        }
        virtual ~Foo() {
            std::cout << "Foo destructor\n";
        }
};

class Bar : public Foo {
    public:
        void f() {
            std::cout << "Bar f\n";
        }
        ~Bar() {
            std::cout << "Bar destructor\n";
        }
};

/**
 * Why does a destructor in base class need to be declared virtual? 
 */
int main() {
    Foo* p = new Bar();
    p -> f();
    delete p; // id Foo's destructor non-virtual, prints only "Foo destructor", otherwise both "Foo destructor" and "Bar destructor"
    std::cout << "Destructors are called to clean up memory and resources. If Foo's destructor were not virtual,\n"
    "then Foo's destructor would be called, even when p is really of type Bar. This is why we declare\n"
    "destructors to be virtual; we want to ensure that the destructor for the most derived class is called.\n";
}
