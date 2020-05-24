#include <iostream>

/**
 * There is an 8x8 chessboard in which two diagonally opposite corners have been cut off.
 * You are given 31 dominos, and a single domino can cover exactly two squares. Can you
 * use the 31 dominos to cover the entire board? Prove your answer (by providing an example
 * or showing why it's impossible).
 */
int main() {
    std::cout << "It's not possible to use the 31 dominos to cover the 8x8 chessboard where "
                 "two diagonally opposite corners have been cut off. It's not possible because "
                 "each domino covers one black and one white square. After cutting two diagonally "
                 "opposite corners there are 32 white squares and 30 black squares left. That means "
                 "that 30 dominos will cover 30 black and 30 white squares. After that we will have "
                 "one domino left and only 2 white squares, which means that the last one domino can't "
                 "be placed on the chessboard beacuse there is no black square left.\n";
}