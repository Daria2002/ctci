#include <iostream>
#include <cstring>
#include <cstdio>

struct Test {
    char* ptr;
};

void shallow_copy(Test& src, Test& dest) {
    dest.ptr = src.ptr;
}

void deep_copy(Test& src, Test& dest) {
    // allocate memory for new ponter
    dest.ptr = (char*)malloc(strlen(src.ptr) + 1); // one more space for \0
    strcpy(dest.ptr, src.ptr);
}

/**
 * What is the difference between deep copy and shallow copy? Explain how 
 * you would use each. 
 */
int main() {
    std::cout << "Shallow copy copies all the member values from one object\n"
    "to another. A deep copy does all this and also deep copies any pointer\n"
    "objects. The shallow copy can cause a lot of runtime errors, expecially\n"
    "with the creation and deletion of objects. Shallow copy is used when\n"
    "there is a need to pass information about a complex structure without\n"
    "actual duplication of data. Shallow copy is rarely used. Deep copy\n"
    "should be used in most cases, especially when the size of the copied\n"
    "structure is small because there is enough memory space.\n";
}
