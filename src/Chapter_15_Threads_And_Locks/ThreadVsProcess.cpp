#include <iostream>

/**
 * Thread vs. Process: What's the difference between a thread and a process? 
*/
int main() {
    std::cout << 
    "A process is an instance of a program in execution. Each\n"
    "process is executed in a separated address space, and one\n"
    "process cannot access the variables and data structures of\n"
    "another process. To access the other process resources inter-process\n"
    "communication have to be used. These include pipes, files, sockets etc.\n"
    "A thread exists within a process and shares the process resource.\n"
    "Multiple threads within the same process will share the same heap space.\n";
}
