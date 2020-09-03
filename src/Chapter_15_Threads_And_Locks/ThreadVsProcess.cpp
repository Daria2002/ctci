#include <iostream>

/**
 * Thread vs. Process: What's the difference between a thread and a process? 
*/
int main() {
    std::cout <<
    "Processes and threads are related to each other but are fundamentally different.\n"
    "A process can be thought of as an instance of a program in execution. A process is an\n"
    "independent entity to which system resources (e.g., CPU time and memory) are allocated.\n"
    "Each process is executed in a separate address space, and one process cannot access the\n"
    "the variables and data structures of another process. If a process whishes to access\n"
    "another process variables, inter-process communications have to be used. These include\n"
    "pipes, files, sockets, and other forms. A thread exists within a process and shares the\n"
    "process resources (including its heap space). Multiple threads within the same process\n"
    "will share the same heap space. This is very different from processes, which cannot\n"
    "directly access the memory of another process. Each thread still has its own registers\n"
    "and its own stack, but other threads can read and write the heap memory. A thread is a\n"
    "particular execution path of a process. When one thread modifies a process resource, the\n"
    "change is immediately visible to sibling threads.\n";
}
