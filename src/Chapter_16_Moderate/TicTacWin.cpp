#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
#include <list>

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
            row.push_back(Piece(rand() % options));
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
    std::cout << ((winner == Piece::Empty) ? "There is no winner.\n" : "winner = " + piece_to_str(winner) + '\n');
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
        std::cout << ((winner == Piece::Empty) ? "There is no winner.\n" : "winner = " + piece_to_str(winner) + '\n');
    }
    // check the first board, that we already calculated for sure 
    if(board_int_hashtable.find(board_to_remember) != board_int_hashtable.end()) { // board to remember should be in the hashtable
        std::cout << "iteration no. " << iteration << ", board:\n";
        print_board(board_to_remember);
        winner = int_piece_hashtable[board_int_hashtable[board_to_remember]];
        std::cout << ((winner == Piece::Empty) ? "There is no winner.\n" : "winner = " + piece_to_str(winner) + '\n');
    } else {    
        std::cout << "Something is wrong because board to remember is not in the hashtable.\n";
    }
}

bool has_won_row(const std::vector<std::vector<Piece>>& board, int row) {
    for(int column = 1; column < board[row].size(); column++) {
        if(board[row][column] != board[row][0]) return false;
    }
    return true;
}

bool has_won_column(const std::vector<std::vector<Piece>>& board, int column) {
    for(int row = 1; row < board.size(); row++) {
        if(board[row][column] != board[0][column]) return false;
    }
    return true;
}

bool has_won_diagonal(const std::vector<std::vector<Piece>>& board, int direction) {
    int row = 0; 
    int column = direction == 1 ? 0 : board.size() - 1;
    Piece first = board[0][column];
    for(int i = 0; i < board.size(); i++) {
        if(board[row][column] != first) return false;
        row++;
        column += direction;
    }
    return true;
}

Piece hasWon_last_move(const std::vector<std::vector<Piece>>& board, int row, int column) {
    Piece piece = board[row][column];
    if(piece == Piece::Empty) return Piece::Empty;
    if(has_won_row(board, row) || has_won_column(board, column)) {
        return piece;
    }
    if(row == column && has_won_diagonal(board, 1)) {
        return piece;
    }
    if(row == (board.size() - column - 1) && has_won_diagonal(board, -1)) {
        return piece;
    }
    return Piece::Empty;
}

std::vector<std::vector<Piece>> initialize_empty_board(const int size) {
    std::vector<std::vector<Piece>> board;
    for(int i = 0; i < size; i++) {
        std::vector<Piece> row;
        for(int j = 0; j < size; j++) {
            row.push_back(Piece::Empty);
        }
        board.push_back(row);
    }
    return board;
}

bool is_finished(const int iteration, const int num_of_el) {
    return iteration == num_of_el;
}

// if we know the very last move that was made (and we've been checking for a winner up until 
// now), then we only need the row, column and diagonal that overlaps with this position
void hasWon_last_move() {
    Piece winner = Piece::Empty;
    constexpr int size = 3;
    int position_index = 0;
    int num_of_elements = size * size; // 1st el in the 2nd row has index 3
    std::vector<int> taken_indices;
    std::vector<std::vector<Piece>> board = initialize_empty_board(size);
    int iteration = 1;
    while (winner == Piece::Empty && !is_finished(iteration, num_of_elements))
    {
        position_index = rand() % num_of_elements;
        while (std::find(taken_indices.begin(), taken_indices.end(), position_index) != taken_indices.end())
        {
            position_index = rand() % num_of_elements;
        }
        taken_indices.push_back(position_index);
        board[position_index / size][position_index % size] = Piece(iteration % 2 + 1); // iterative red and blue moves 
        std::cout << "\nIteration no. " << iteration << '\n';
        print_board(board);
        winner = hasWon_last_move(board, position_index / size, position_index % size);
        iteration++;
    }
    std::cout << ((winner == Piece::Empty) ? "There is no winner.\n" : "winner = " + piece_to_str(winner) + '\n');
}

// returns true if all Pieces have same value, but different than empty
bool hasWinner(Piece p1, Piece p2, Piece p3) {
    return p1 == Piece::Empty ? false : (p1 == p2 && p2 == p3);
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

Piece nested_for_loops_nxn(std::vector<std::vector<Piece>> board) {
    int size = board.size();
    if(board[0].size() != size ) return Piece::Empty;
    Piece first;
    // check rows
    for(int i = 0; i < size; i++) {
        first = board[i][0];
        if(first == Piece::Empty) continue;
        for(int j = 1; j < size; j++) {
            if(first != board[i][j]) break; // breaks if any el not equal to first
            else if(j == size - 1) return first; // executes only if current el is the last one, and it is equal to the first
        }
    }
    // check columns
    for(int i = 0; i < size; i++) {
        first = board[0][i];
        if(first != Piece::Empty) continue;
        for(int j = 1; j < size; j++) {
            if(board[j][i] != first) break;
            if(j == size - 1) return first;
        }
    }
    // check diagonal1
    first = board[0][0];
    if(first != Piece::Empty) {
        for(int i = 1; i < size; i++) {
            if(board[i][i] != first) break;
            else if(i == size - 1) return first;
        }
    }
    // check diagonal2
    first = board[0][size - 1];
    if(first != Piece::Empty) {
        for(int i = 1; i < size; i++) {
            if(board[i][size - i - 1] != first) break;
            else if(i == size - 1) return first;
        }
    }
    return Piece::Empty;
}

class Check {
    public:
        int column, row;
        Check() = default;
        Check(int r, int c, int rowI, int columnI) : 
        row(r), column(c), row_increment(rowI), column_increment(columnI) {}
        void increment() {
            row += row_increment;
            column += column_increment;
        }
        bool in_bounds(int size) const {
            return row >= 0 && row < size && column >= 0 && column < size;
        }
        private:
            int row_increment, column_increment;
};

Piece hasWon(std::vector<std::vector<Piece>> board, Check instruction) {
    Piece first = board[instruction.row][instruction.column];
    while (instruction.in_bounds(board.size()))
    {
        if(board[instruction.row][instruction.column] != first) return Piece::Empty;
        instruction.increment();
    }
    return first;
}

Piece increment_decrement_nxn(std::vector<std::vector<Piece>> board) {
    if(board.size() != board[0].size()) return Piece::Empty;
    const int size = board.size();
    std::vector<Check> instructions; // to be checked
    for(int i = 0; i < size; i++) {
        instructions.push_back(Check(0, i, 1, 0)); // checking each column
        instructions.push_back(Check(i, 0, 0, 1)); // checking each row
    }
    instructions.push_back(Check(0, 0, 1, 1)); // check first diagonal
    instructions.push_back(Check(0, size - 1, 1, -1)); // check second diagonal
    for(Check instruction : instructions) {
        Piece winner = hasWon(board, instruction);
        if(winner != Piece::Empty) return winner;
    }
    return Piece::Empty;
}

class Position {
    public:
        int _row;
        int _column;
        Position(int row, int column) : _row(row), _column(column) {}
};

class PositionIterator {
    public:
        PositionIterator(Position position, int row_increment, int column_increment, int size) :
        _position(position), _row_increment(row_increment), _column_increment(column_increment), _size(size) {}
        Position next() {
            _position._row += _row_increment;
            _position._column += _column_increment;
            return _position;
        }
        Position current() {
            return _position;
        }
        bool hasNext() {
            return (_position._row + _row_increment < _size && _position._column + _column_increment < _size);
        }
    private:
        Position _position;
        int _row_increment;
        int _column_increment;
        int _size;
};

Piece hasWon_iterator(std::vector<std::vector<Piece>> board, PositionIterator iterator) {
    Position firstPosition = iterator.current();
    Piece first = board[firstPosition._row][firstPosition._column];
    while (iterator.hasNext())
    {
        Position position = iterator.next();
        if(board[position._row][position._column] != first) return Piece::Empty;
    }
    return first;
}

Piece iterator_nxn(std::vector<std::vector<Piece>> board) {
    if(board.size() != board[0].size()) return Piece::Empty;
    int size = board.size();
    std::vector<PositionIterator> instructions;
    for(int i = 0; i < size; i++) {
        instructions.push_back(PositionIterator(Position(0, i), 1, 0, size)); // check each column
        instructions.push_back(PositionIterator(Position(i, 0), 0, 1, size)); // check each row
    }
    instructions.push_back(PositionIterator(Position(0, 0), 1, 1, size)); // check first diagonal
    instructions.push_back(PositionIterator(Position(0, size - 1), 1, -1, size)); // check second diagonal
    for(PositionIterator iterator : instructions) {
        Piece winner = hasWon_iterator(board, iterator);
        if(winner != Piece::Empty) return winner;
    }
    return Piece::Empty;
}

Piece hasWon_NxN(std::vector<std::vector<Piece>> board, const int method) {
    switch (method)
    {
    case 1:
        return nested_for_loops_nxn(board);
    case 2:
        return increment_decrement_nxn(board);
    default:
        return iterator_nxn(board);
    }
}

std::vector<std::vector<Piece>> initialize_NxN_board(const int n) {
    std::cout << "Initializing " << n << "x" << n << " board\n";
    constexpr auto options = 3;
    std::vector<std::vector<Piece>> board;
    std::vector<Piece> row_elements;
    for(int row = 0; row < n; row++) {
        for(int column = 0; column < n; column++) {
            row_elements.push_back(Piece(rand() % options));
        }
        board.push_back(row_elements);
        row_elements.clear();
    }
    return board;
}

void simulate_NxN_method() {
    constexpr auto number_of_simulations = 10;
    constexpr auto max_n = 4;
    constexpr auto min_n = 2;
    std::vector<std::vector<Piece>> board;
    Piece winner;
    auto method = 1;
    std::cout << "Enter 1 to solve NxN board using Nested For-Loops, 2 for Increment\n"
                 "and Decrement Function and any other number for solution using Iterator.\n";
    std::cin >> method;
    for(int i = 0; i < number_of_simulations; i++) {
        std::cout << "Iteration no. " << i << '\n';
        board = initialize_NxN_board(rand() % (max_n - min_n + 1) + min_n);
        print_board(board);
        winner = hasWon_NxN(board, method);
        std::cout << ((winner == Piece::Empty) ? "There is no winner.\n" : "winner = " + piece_to_str(winner) + '\n');
    }
}

void simulate_3x3_method() {
    std::vector<std::vector<Piece>> board = initialize_3x3_board();
    std::cout << "Simulating method for 3x3 board:\n";
    print_board(board);
    Piece winner = hasWon_3x3(board);
    std::cout << ((winner == Piece::Empty) ? "There is no winner.\n" : "winner = " + piece_to_str(winner) + '\n');
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
        simulate_NxN_method();
    }
}