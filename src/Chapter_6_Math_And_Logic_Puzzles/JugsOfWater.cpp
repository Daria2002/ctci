#include <iostream>
#include <cmath>

class Jug {
    public:
        Jug() = default;
        Jug(int c) : capacity(c) {
            status = 0;
        }
        Jug(int c, std::string n) : capacity(c), name(n) {
            status = 0;
        }
        Jug(std::string n) : name(n) {
            status = 0;
        }
        int capacity, status;
        std::string name;
        bool pour_in(int quantity) {
            if(status + quantity > capacity) {
                return false;
            }
            status += quantity;
            std::cout << "Pour in " << quantity << " quarts into jug " << name << '\n' <<
                         "Current status : " << status << '\n' << 
                         "============================================================\n";
            return true;
        }
        int empty_quantity() const {
            return capacity - status;
        }
        bool pour_out(int quantity) {
            if(status - quantity < 0) {
                return false;
            }
            status -= quantity;
            std::cout << "Pour out " << quantity << " quarts from jug " << name << '\n' <<
                        "Current status int jug " << name << " : " << status << '\n' << 
                        "============================================================\n";
            return true;
        }
        bool is_full() const {
            return capacity == status;
        }
        bool is_empty() const {
            return status == 0;
        }
        void fill() {
            std::cout << "Pour in " << capacity - status << " quarts into jug " << name << '\n' <<
                         "Current status : " << status << '\n' << 
                         "============================================================\n";
            status = capacity;
        }
        void empty() {
            status = 0;
        }
};

void get_quantity(Jug a, Jug b, int goal) {
    if(goal == a.capacity) {
        a.fill();
        return;
    }
    if(goal == b.capacity) {
        b.fill();
        return;
    }
    if(goal == (a.capacity + b.capacity)) {
        a.fill();
        b.fill();
        return;
    }
    while(goal != a.status && goal != b.status && goal != (a.status + b.status)) {
        a.fill();
        int delta = b.empty_quantity();
        b.pour_in(delta);
        a.pour_out(delta);
        if(a.status == goal || b.status == goal || a.status + b.status == goal) {
            break;
        }
        b.empty();
        delta = b.empty_quantity() > a.status ? a.status : b.empty_quantity();
        b.pour_in(delta);
        a.pour_out(delta);
        if(a.status == goal || b.status == goal || a.status + b.status == goal) {
            break;
        }
    }
}

int are_relatively_primes(int a, int b) {
    int greater = a > b ? a : b;
    for(int i = 2; i < std::sqrt(greater); i++) {
        if(a % i == 0 && b % i == 0) {
            return false;
        }
    }
    return true;
}

// if a and b are relatively prime numbers and goal quantity is in range [1, a+b]
// it is possible to get goal quantity using jug a and jug b
bool check(int a, int b, int goal) {
    if(!are_relatively_primes(a, b)) {
        return false;
    }
    return (goal >= 1 && goal <= a + b);
}

/**
 * You have a five-quart jug, a three-quart jug, and an unlimited supply of water
 * (but no measuring cups). How would you come up with exactly four quarts of water?
 * Note that the jugs are oddly shaped, such that filling up exactly "half" of the jug
 * would be impossible.
 */
int main() {
    std::cout << "======================================\n"
                 "Program for jugs of water optimization\n"
                 "======================================\n";
    Jug a("a"), b("b");
    int goal;
    std::cout << "Enter capacity for jug a:\n";
    std::cin >> a.capacity;
    std::cout << "Enter capacity for jug b:\n";
    std::cin >> b.capacity;
    std::cout << "Enter goal quantity:\n";
    std::cin >> goal;
    if(!check(a.capacity, b.capacity, goal)) {
        std::cout << "a and b capacity must be relatively prime numbers and goal must be in range \n"
                     "[1, a capacity + b capacity] in order to be possible to obtain goal capacity \n"
                     "using a and b jug.\n";
        return 0;
    }
    get_quantity(a.capacity > b.capacity ? a : b, a.capacity > b.capacity ? b : a, goal);
}
