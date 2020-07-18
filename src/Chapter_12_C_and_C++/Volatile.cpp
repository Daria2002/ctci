#include <iostream>

/**
 * What is the significance of the keyword "volatile" in C? 
 */
int main() {
    std::cout << 
    "Volatile informs the compiler that the value of variable it is applied to can change\n"
    "from the outside (by os, hardware or another thread), without any update done by the\n"
    "code. Because the value can change unexpectedly, the compiler will therefore reload\n"
    "the value each time from memory. Volatile variables are not optimized and that's very\n"
    "useful. I.e.\n"
    "int opt = 1;\n"
    "void Fn(void)\n"
    "   start:\n"
    "       if(opt == 1) goto start;\n"
    "       else return;\n"
    "At first glance, the code appears to loop infinitely. The compiler may optimize it to:\n"
    "void Fn(void)\n"
    "   start:\n"
    "       int opt = 1;\n"
    "       if(true)\n"
    "       goto start;\n"
    "This becomes an infinite loop, but an external operation might write 0 to the location\n"
    "of variable opt, thus breaking the loop. To prevent the compiler from performing such\n"
    "optimization, we want to signal the another element of the system could change the variable.\n"
    "We do this using the volatile keyword, as shown belown:\n"
    "volatile int opt = 1;\n"
    "void Fn(void)\n"
    "   start:\n"
    "       if(opt == 1) goto start;\n"
    "       else return;\n"
    "Volatile is useful for multi-threaded programs that have global variables and any thread can\n"
    "modify these shared variables. We may not want optimization on these variables\n";
}
