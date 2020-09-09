#include <iostream>
#include <unordered_map>
#include <vector>

// there are 3^9 = 20000 tic-tac-toe boards -> tic-tac-toe boards can be represented
// as an int
enum Piece { Empty = 0, Red = 1, Blue = 2 };

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

// set up hash table with all possible boards as keys and the value indicating who
// has won
std::unordered_map<int, Piece> do_preprocessing() {
    std::unordered_map<int, Piece> winnerHashtable;
    
    return winnerHashtable;
}

Piece hasWon_multiple_times(int board, std::unordered_map<int, Piece>& winnerHashtable) {
    return winnerHashtable[board];
}

// if we know the very last move that was made (and we've been checking for a winner up until 
// now), then we only need the row, column and diagonal that overlaps with this position
Piece hasWon_last_move() {
    
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
        // check 1st diagonal
        if(hasWinner(board[0][0], board[1][1], board[2][2])) return board[0][0];
        // check 2nd diagonal        
        if(hasWinner(board[0][2], board[1][1], board[2][0])) return board[0][2];
        // no winner
        return Piece::Empty;
    }
}

Piece hasWon_NxN() {
    
}

/**
 * Tic Tac Win: Design an algorithm to figure out if someone has won a game of tic-tac-toe.
 */
int main() {
    auto method = 1;
    Piece winner;
    std::cout << "Enter 1 to id hasWon is called many times, 2 if we know the last move,\n"
    "3 if solution should be designed for just a 3x3 board and any other number if solution\n"
    "should be designed for an NxN board.\n", std::cin >> method;
    if(method == 1) {
        std::unordered_map<int, Piece> winnerHashtable = do_preprocessing();
        // i.e. as part of a tic-tac-toe website, do some preprocessing
        winner = hasWon_multiple_times(); 
    } else if(method == 2) {
        winner = hasWon_last_move();
    } else if(method == 3) {
        winner = hasWon_3x3();
    } else {
        winner = hasWon_NxN();
    }
}
