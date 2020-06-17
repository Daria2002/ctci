#include <iostream>
#include <vector>
#include <memory>
#include <array>

class Game;
class Player;
class Piece;
class Board;
class Game;

enum Direction {
    right, left, top, down
};  

enum Color {
    white, black
};  

class Board {
    public:
        Board() = default;
        Board(int r, int c) : rows(r), columns(c) {
            for(int i = 0; i < r; i++) {
                std::vector<std::shared_ptr<Piece>> v;
                for(int j = 0; j < c; j++) {
                    v.push_back(nullptr);
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
        bool place_color(int row, int column, Color color) {
            if(board[row][column] == nullptr) {
                board[row][column] = std::make_shared<Piece>(color);
                return true;
            }
            return false;
        }
        int get_score(Color color) {
            return color == Color::white ? white_count : black_count;
        }
        void update_score(Color new_color, int new_pieces) {
            // TODO
        }
        int flip_section(int row, int column, Color color, Direction direction) {
            // TODO
        }
    private:
        std::vector<std::vector<std::shared_ptr<Piece>>> board;
        int black_count = 0;
        int white_count = 0;
        int rows = 0;
        int columns = 0;
};

class Game {
    public:
        Game() {
            constexpr int rows = 10;
            constexpr int columns = 10;
            board = std::make_shared<Board>(rows, columns);
            players[0] = std::make_shared<Player>(Color::black);
            players[1] = std::make_shared<Player>(Color::white);
        }
        static Game& get_instance() {
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
        Player(Color col) : color(col) {}
        int get_score() {
            // TODO
        }
        Color get_color() {
            return color;
        }
        bool play_piece(int, int);
    private:
        Color color;
};

class Piece {
    public:
        Piece() = default;
        Piece(Color col) : color(col) {}
        void flip() {
            color = color == Color::black ? Color::white : Color::black;
        }
        Color get_color() {
            return color;
        }
    private:
        Color color;
};

bool Player::play_piece(int row, int column) {
    return Game::get_instance().get_board() -> place_color(row, column, get_color());
    return true;
}

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
