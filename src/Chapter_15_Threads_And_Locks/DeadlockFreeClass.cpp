#include <iostream>

/**
 * Deadlock-Free Class: Design a class which provides a lock only if there are no possible
 * deadlocks.
*/
int main() {
    std::cout << "One of the popular ways is to require a process to declare upfront what\n"
                 "locks it will need. We can then verify if a deadlock would be created by\n"
                 "issuing these locks, and we can fail if so. With these constraints in mind,\n"
                 "let's investigate how we can detect deadlocks. Suppose this was the order\n"
                 "of locks requested:\n"
                 "A = {1, 2, 3, 4}\n"
                 "B = {1, 3, 5}\n"
                 "C = {7, 5, 9, 2}\n"
                 "This may create a deadlock because we could have the following scenario:\n"
                 "A locks 2, waits on 3\n"
                 "B locks 3, waits on 5\n"
                 "C locks 5, waits on 2\n"
                 "We can think about this as a graph, where 2 is connected to , 3 is connected\n"
                 "to 5, and 5 is connected to 2. A deadlock is represented by a cycle. An edge\n"
                 "(w, v) exists in the graph if a process declares that it will request lock v\n"
                 "immediately after lock w. For the earlier example, the following edges would\n"
                 "exist in the graph: (1, 2), (2, 3), (3, 4), (1, 3), (3, 5), (7, 5), (5, 9)\n"
                 "(9, 2). The \"owner\" of the edge does not matter. Depth-first search can be\n"
                 "used to detect a cycle.\n";
}
