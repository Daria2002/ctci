#include <iostream>

/**
 * Dining Philosophers: In the famous dining philosophers problem, a bunch of 
 * philosophers are sitting around a circular table with one chopstick between each of them.
 * A philosopher needs both chopsticks to eat, and always picks up the left chopstick
 * before the right one. A deadlock could potentially occur if all the philosophers
 * reached for the left chopstick at the same time. Using threads and locks, implement
 * a simulation of the dining philosophers problem that prevents deadlocks.
*/
int main() {
    std::cout << "Running a simple code where each of the philosophers pick up a left chopstick and\n"
                 "wait for the right chopstick may lead to a deadlock if all the philosophers have a\n"
                 "left chopstick and are waiting for the right one.\n"
                 "Solution #1: All or Nothing\n"
                 "To prevent deadlocks, we can implement a strategy where a philosopher will put down\n"
                 "his left chopstick if he is unable to obtain the right one. We need to be sure to\n"
                 "release the left chopstick if we can't pick up the right one - and to not call putDown()\n"
                 "on the chopsticks if we never had them in the first place. One issue with this is that if\n"
                 "all the philosophers were perfectly synchronized, they could simultaneously pick up\n"
                 "their left chopstick, be unable to pick up the right one, and then put back down the\n"
                 "left one - only to have the process repeated again.\n"
                 "Solution #2: Prioritized Chopsick\n"
                 "Alternatively, we can label the chopsticks with a number from 0 to N - 1. Each philosopher,\n"
                 "attempts to pick up the lower numbered chopstick first. This essentially means that each\n"
                 "philosopher goes for the left chopstick before right one (assuming that's the way we labeled it),\n"
                 "except for the last philosopher who does this in reverse. This will break the cycle. With this\n"
                 "solution, a philosopher can never hold the larger chopstick without holding the smaller one.\n"
                 "This prevents the ability to have a cycle, since a cycle means that a higher chopstick would\n"
                 "\"point\" to the lower one.\n";
}
