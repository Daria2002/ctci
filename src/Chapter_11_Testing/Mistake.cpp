#include <iostream>

/**
 * Mistake: Find the mistake(s) in the following code:
 * unsigned int i;
 * for (i = 100; i >= 0; --i)
 *      printf("%d\n", i);
 */
int main() {
    unsigned int i;
    for (i = 100; i > 0; --i)
        printf("%u\n", i);
    printf("%u\n", i);
}
