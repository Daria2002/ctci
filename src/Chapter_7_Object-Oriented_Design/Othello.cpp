#include <iostream>
#include <vector>
#include <memory>

class Game;
class Player;
class Piece;
class Board;
class Game;

enum Color {
    white, black
    
};  

class Game {
    public:
        static constexpr int rows = 10;
        static constexpr int columns = 10;
        Game() {
            board = std::make_shared<Board>(rows, columns);
        }
        Game& get_instance() {
            static Game g;
            return g;
        }
    private:
        std::vector<std::shared_ptr<Player>> players;
        std::shared_ptr<Board> board;
};

class Board {
    public:
        Board(int rows, int columns) {
            // TODO ini board
        }
    private:
};

/**
 * Othello is played as follows: Each Othello piece is white on one side and black on the other. 
 * When a piece is surrounded by its opponents on both the left and right sides, or both the top and bottom, it is said to be captured and its color is flippeed.
 * On your turn, you must capture at least one of your opponent's pieces.
 * The game ends when either user has no more valid moves.
 * The win is assigned to the person with the most pieces. 
 * Implement the object-oriented design for Othello.
 */
int main() {
    std::cout << "Othello\n";
    // TODO store results in db
}