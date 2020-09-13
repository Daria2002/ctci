#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

// there are 3^9 = 20000 tic-tac-toe boards -> tic-tac-toe boards can be represented
// as an int
enum Piece { Empty = 0, Red = 1, Blue = 2 };

struct MatrixHasher {
    std::size_t operator()(const std::vector<std::vector<Piece>>& matrix) const {
        std::size_t h = 0;
        for (std::vector<Piece> row : matrix) {
            for(Piece p : row) {
                if(p == Empty) {
                    h ^= std::hash<int>{}(0)  + 0x9e3779b9 + (h << 6) + (h >> 2); 
                } else if(p == Red) {
                    h ^= std::hash<int>{}(1)  + 0x9e3779b9 + (h << 6) + (h >> 2); 
                } else {
                    h ^= std::hash<int>{}(2)  + 0x9e3779b9 + (h << 6) + (h >> 2); 
                }
            }
        }
        return h;
    }   
};

std::string piece_to_str(Piece piece) {
    if(piece == Empty) return "E";
    else if(piece == Red) return "R";
    return "B";
}

void print_board(const std::vector<std::vector<Piece>>& board) {
    for(int i = 0; i < board.size(); i++) {
        for(int j = 0; j < board[0].size(); j++) {
            std::cout << piece_to_str(board[i][j]) << " ";
        }
        std::cout << "\n";
    }
}

int convertBoardToInt(const std::vector<std::vector<Piece>>& board) {
    int sum = 0;
    for(int i = 0; i < board.size(); i++) {
        for(int j = 0; j < board[0].size(); j++) {
            // each value in enum has an integer associated with it. We can just use that.
            int value = board[i][j];
            sum = sum * 3 + value;
        }
    }
    return sum;
}

bool has_won_row(Piece& winner, const std::vector<std::vector<Piece>>& board) {
    bool has_solution = true;
    for(auto row : board) {
        for(int column_index = 1; column_index < row.size(); column_index++) {
            if(row[0] != row[column_index]) {
                has_solution = false;
                break;
            }
        }
        if(!has_solution || row[0] == Piece::Empty) has_solution = true;
        else {
            winner = row[0];
            return true;
        }
    }
    winner = Piece::Empty;
    return false;
}

bool has_won_column(Piece& winner, const std::vector<std::vector<Piece>>& board) {
    bool has_solution = true;
    for(int column = 0; column < board[0].size(); column++) {
        for(int row = 0; row < board.size(); row++) {
            if(board[0][column] != board[row][column]) {
                has_solution = false;
                break;
            }
        }
        if(!has_solution || board[0][column] == Piece::Empty) {
            has_solution = true;
            continue;
        }
        winner = board[0][column];  
        return true;
    }
    winner = Piece::Empty;
    return false;
}

bool has_won_diagonal(Piece& winner, const std::vector<std::vector<Piece>>& board) {
    int start = 0;
    int end = board.size() - 1;
    bool first = true;
    bool second = true;
    for(int i = 0; i < board.size() && (first || second); i++) {
        // check first diagonal
        if(first && board[start][start] != board[i][i]) {
            first = false;
        }
        // check second diagonal
        if(second && board[start][end] != board[start + i][end - i]) {
            second = false;
        }
    }
    if(first || second) { // winner found
        winner = first ? board[start][start] : board[start][end];
        return true;
    }
    winner = Piece::Empty;
    return false;
}

Piece get_winner(const std::vector<std::vector<Piece>>& board) {
    Piece winner;
    if(has_won_row(winner, board) && winner != Piece::Empty) return winner;
    if(has_won_column(winner, board) && winner != Piece::Empty) return winner;
    if(has_won_diagonal(winner, board) && winner != Piece::Empty) return winner;
    std::cout << "There is no winner.\n";
    return Piece::Empty;
}

std::vector<std::vector<Piece>> initialize_3x3_board() {
    std::vector<std::vector<Piece>> board;
    constexpr int n = 3;
    constexpr int options = 3;
    int rand_num;
    std::vector<Piece> row;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            rand_num = rand() % options;
            switch (rand_num) {
                case 0:
                    row.push_back(Piece::Empty);
                    break;
                case 1:
                    row.push_back(Piece::Red);
                    break;
                default:
                    row.push_back(Piece::Blue);
                    break;
            }
        }
        board.push_back(row);
        row.clear();
    }
    return board;
}

void hasWon_multiple_times() {
    constexpr int number_of_times = 5;
    // hashtable where key is board and value is int value
    std::unordered_map<std::vector<std::vector<Piece>>, int, MatrixHasher> board_int_hashtable;
    // hashtable where key is int value of the board and value is the winner
    std::unordered_map<int, Piece> int_piece_hashtable;
    std::vector<std::vector<Piece>> board = initialize_3x3_board();
    int iteration = 0;
    std::cout << "iteration no. " << iteration++ << ", board:\n";
    print_board(board);
    Piece winner = get_winner(board);
    int board_value = convertBoardToInt(board);
    board_int_hashtable[board] = board_value;
    int_piece_hashtable[board_value] = winner;
    std::cout << "winner = " << piece_to_str(winner) << '\n';
    std::vector<std::vector<Piece>> board_to_remember = board;
    while(iteration < number_of_times) {
        board = initialize_3x3_board();
        std::cout << "iteration no. " << iteration++ << ", board:\n";
        print_board(board);
        if(board_int_hashtable.find(board) != board_int_hashtable.end()) { // already calculated, just check hashtable for the result
            winner = int_piece_hashtable[board_int_hashtable[board]];
        } else { // new input, calculate and add in hash table
            winner = get_winner(board);
            board_value = convertBoardToInt(board);
            board_int_hashtable[board] = board_value;
            int_piece_hashtable[board_value] = winner;
        }
        std::cout << "winner = " << piece_to_str(winner) << '\n';
    }
    // check the first board, that we already calculated for sure 
    if(board_int_hashtable.find(board_to_remember) != board_int_hashtable.end()) { // board to remember should be in the hashtable
        std::cout << "iteration no. " << iteration << ", board:\n";
        print_board(board_to_remember);
        winner = int_piece_hashtable[board_int_hashtable[board_to_remember]];
        std::cout << "winner = " << piece_to_str(winner) << '\n';
    } else {    
        std::cout << "Something is wrong because board to remember is not in the hashtable.\n";
    }
}

// if we know the very last move that was made (and we've been checking for a winner up until 
// now), then we only need the row, column and diagonal that overlaps with this position
Piece hasWon_last_move() {
    return Piece::Empty;
}

// returns true if all Pieces have same value, but different than empty
bool hasWinner(Piece p1, Piece p2, Piece p3) {
    if(p1 == Piece::Empty) {
        return false;
    }
    return p1 == p2 && p2 == p3;
}

Piece hasWon_3x3(std::vector<std::vector<Piece>> board) {
    for(int i = 0; i < board.size(); i++) {
        // check rows 
        if(hasWinner(board[i][0], board[i][1], board[i][2])) return board[i][0];
        // check columns 
        if(hasWinner(board[0][i], board[1][i], board[2][i])) return board[0][i];
    }
    // check 1st diagonal
    if(hasWinner(board[0][0], board[1][1], board[2][2])) return board[0][0];
    // check 2nd diagonal        
    if(hasWinner(board[0][2], board[1][1], board[2][0])) return board[0][2];
    // no winner
    return Piece::Empty;
}

Piece hasWon_NxN() {
    return Piece::Empty;
}

std::vector<std::vector<int>> initialize_NxN_board(const int n) {
    std::vector<std::vector<int>> board;
    
    return board;
}

void simulate_3x3_method() {
    std::vector<std::vector<Piece>> board = initialize_3x3_board();
    std::cout << "Simulating method for 3x3 board:\n";
    print_board(board);
    Piece winner = hasWon_3x3(board);
    if(winner == Piece::Empty) std::cout << "There is no winner.\n";
    else std::cout << "Winner = " << piece_to_str(winner) << '\n';
}

/**
 * Tic Tac Win: Design an algorithm to figure out if someone has won a game of tic-tac-toe.
 */
int main() {
    srand((unsigned) time(0));
    auto method = 1;
    std::cout << "Enter 1 to id hasWon is called many times, 2 if we know the last move,\n"
    "3 if solution should be designed for just a 3x3 board and any other number if solution\n"
    "should be designed for an NxN board.\n", std::cin >> method;
    if(method == 1) {
        // i.e. as part of a tic-tac-toe website, do some preprocessing
        hasWon_multiple_times(); 
    } else if(method == 2) {
        hasWon_last_move();
    } else if(method == 3) {
        simulate_3x3_method();
    } else {
        hasWon_NxN();
    }
}
