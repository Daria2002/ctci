#include <iostream>
#include <stack> 

class Tower {
    public:
        Tower(std::string n) : name(n) {}
        std::string name;
        std::stack<int> disks;
        bool add(int el) {
            if(!disks.empty() && disks.top() <= el) {
                return false;
            }
            disks.push(el);
            return true;
        }
        int move_top() {
            int el = disks.top();
            disks.pop();
            return el;
        }
};

void move_top(Tower& origin, Tower& dest) {
    int el = origin.move_top();
    std::cout << "Move element " << el << " from " << origin.name << " to " << dest.name << ".\n";
    dest.add(el);
}

void move_disks(int n, Tower& origin, Tower& dest, Tower& buffer) {
    if(n <= 0) return;
    move_disks(n - 1, origin, buffer, dest);
    move_top(origin, dest);
    move_disks(n - 1, buffer, dest, origin);
}

/**
 * In the classic problem of the Towers of Hanoi, you have 3 towers and N disks of
 * different sizes which can slide onto any tower. The puzzle starts with disks sorted in
 * ascending order of size from top to bottom (i.e., each disk sits on top of an even larger one).
 * You have the following constraints:
 * (1) Only one disk can be moved at a time.
 * (2) A disk is slid off the top of one tower onto another tower.
 * (3) A disk cannot be placed on top of a smaller disk.
 * Write a program to move the disks from the first tower to the last using Stacks.
 */
int main() {
    Tower origin("origin");
    Tower dest("dest");
    Tower buffer("buffer");
    int size;
    std::cout << "Enter size:\n";
    std::cin >> size;
    for(int i = size; i >= 1; i--) {
        origin.add(i);
    }
    move_disks(size, origin, dest, buffer);
    std::cout << "Destination elements:\n";
    while (!dest.disks.empty()) {
        std::cout << dest.disks.top() << ", ";
        dest.disks.pop();
    }
    std::cout << '\n';
}
