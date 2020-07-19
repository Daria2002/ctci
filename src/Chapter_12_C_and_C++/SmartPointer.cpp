#include <iostream>

template <class T>
class SmartPointer {
    public:
        SmartPointer(T* ptr) {
            ref = ptr;
            ref_count = (unsigned*) malloc(sizeof(unsigned));
            *ref_count = 1;
        }
        // this constructor creates new smart pointer that points to
        // an existing object
        SmartPointer(SmartPointer<T>& sptr) {
            ref = sptr.ref;
            ref_count = sptr.ref_count;
            ++(*ref_count);
        }
        // override the equal operator, so that when one smart ptr is
        // set to another, old smart pointer decrements its ref count,
        // and the new smart ptr increment its ref count
        SmartPointer<T>& operator=(SmartPointer<T>& sptr) {
            if(this == sptr) return *this;
            // if already assigned to an object, remove one ref
            if(*ref_count > 0) remove();
            ref = sptr.ref;
            ref_count = sptr.ref_count;
            ++(*ref_count);
            return *this;
        }
        ~SmartPointer() {
            remove();
        }
        T getValue() {
            return *ref;
        }
    protected:
        void remove() {
            --(*ref_count);
            if(*ref_count == 0) {
                // delete is used for the mem allocated using new or for a NULL ptr
                // free is used for the mem allocated using malloc or for a NULL ptr
                free(ref_count);
                delete ref;
                ref = NULL;
                ref_count = NULL;
            }
        }
        T* ref; 
        // must be a pointer because the ref count is tracked across
        // multiple smart pointers to one object
        unsigned* ref_count; 
};

/**
 * Write a smart pointer class. A smart pointer is a data type, usually implemented with
 * templates, that simulates a pointer while also providing automatic garbage collection. 
 * It automatically counts the number of references to a SmartPointer<T*> object and frees 
 * the object of type T when the reference count hits zero. 
 */
int main() {
    std::cout << 
    "Smart pointers provide safety via automatic memory managment. They avoid\n"
    "issues like dangling pointers, memory leaks and allocation failures.\n";
    int* x = new int(5);
    SmartPointer<int> sptr = SmartPointer<int>(x);
    std::cout << "Smart pointer value = " << sptr.getValue() << '\n';
}
