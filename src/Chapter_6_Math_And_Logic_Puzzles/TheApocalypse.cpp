#include <iostream>
#include <cstdlib>
#include <ctime>

struct Children {
    int g = 0, b = 0;
};

Children get_children() {
    srand(time(NULL));
    Children children;
    while (children.g == 0) {
        if(rand() % 2 == 1) { // 1 - girl
            children.g++;
        } else {    // 0 - boy
            children.b++;
        }
    }
    return children;
}

double gender_ratio(const int n) {
    int b = 0;
    int g = 0;
    for(int i = 0; i < n; i++) {
        Children c = get_children();
        g += c.g;
        b += c.b;
    }
    return (double)g/(b + g);
}

/** 
 * In the new post-apocalyptic world, the world queen is desperately concerned about the birth rate.
 * Therefore, she decrees that all families should ensure that they have one girl or else they face 
 * massive fines. If all families abide by this policy—that is, they have continue to have
 * children until they have one girl, at which point they immediately stop—what will the gender ratio
 * of the new generation be? (Assume that the odds of someone having a boy or a girl on any given
 * pregnancy is equal.) Solve this out logically and then write a computer simulation of it. 
 */
int main() {
    std::cout << "====================================\n"
                 "Program for calculating gender ratio\n"
                 "====================================\n";
    std::cout << "Enter number of families:\n";
    int n;
    std::cin >> n;
    std::cout << "Gender ratio (girls/(girls+boys)) = " << gender_ratio(n) << '\n';
}