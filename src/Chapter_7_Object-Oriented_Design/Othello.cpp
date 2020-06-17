#include <iostream>
#include <vector>
#include <memory>
#include <array>

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
            players[0] = std::make_shared<Player>(Color::black);
            players[1] = std::make_shared<Player>(Color::white);
        }
        Game& get_instance() {
            static Game g;
            return g;
        }
        std::shared_ptr<Board> get_board() {
            return board;
        }
    private:
        std::array<std::shared_ptr<Player>, 2> players;
        std::shared_ptr<Board> board;
};

class Player {
    public:
        Player(Color col) : c(col) {

        }
    private:
        Color c;
};

class Board {
    public:
        Board(int r, int c) : rows(r), columns(c) {
            for(int i = 0; i < r; i++) {
                std::vector<std::shared_ptr<Piece>> v;
                for(int j = 0; j < c; j++) {
                    v.push_back(std::make_shared<Piece>());
                }
                board.push_back(v);
            }
        }
        // initialize center black and white pieces
        void initialize() {
            board[rows/2 - 1][columns/2 - 1] = std::make_shared<Piece>(Color::black);
            board[rows/2][columns/2] = std::make_shared<Piece>(Color::black);
            board[rows/2 - 1][columns/2] = std::make_shared<Piece>(Color::white);
            board[rows/2][columns/2 - 1] = std::make_shared<Piece>(Color::white);
        }
    private:
        std::vector<std::vector<std::shared_ptr<Piece>>> board;
        int black_count = 0;
        int white_count = 0;
        int rows, columns;
};

class Piece {
    public:
        Piece() = default;
        Piece(Color col) : c(col) {}
    private:
        Color c;
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