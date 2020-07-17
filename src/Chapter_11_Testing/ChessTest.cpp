#include <iostream>

/**
 * We have the following method used in a chess game: boolean canMoveTo(int x, int y). 
 * This method is part of the Piece class and returns whether or not the piece can move to
 * position (x, y). Explain how you would test this method. 
 */
int main() {
    std::cout << 
    "In this problem, there are two types of testing: extreme case validation and\n"
    "general case testing. We should ask our interviewer if we should return false\n"
    "or throw an exception for the error cases.\n"
    "Testing Type #1: Extreme Case Validation:\n"
    "- check that program handles bad or unusual input gracefully\n"
    "+ test with negative values for x and y\n"
    "+ test with x larger than width\n"
    "+ test with y larger than height\n"
    "+ test with a completely full board\n"
    "+ test with an empty or nearly empty board\n"
    "+ test with far more white pieces than black\n"
    "+ test with far more black pieces than white\n"
    "Testing Type #2: General Testing:\n"
    "- more expensive, perform a reasonable coverage of different boards\n"
    "- there are 6 pieces, so we can test each piece against every other piece\n"
    "foreach piece a:\n"
    "   for each other type of piece b (6 types + empty space)\n"
    "       foreach direction d\n";
    "           Create a board with piece a\n";
    "           Place piece b in direction d\n";
    "           Try to move - check return value\n";
}
