#include <iostream>
#include <vector>

class Game {
    public:
        Game() = default;
        Game(int g_shots, int t_shots) : total_shots(t_shots), goal_shots(g_shots) {}
        int get_total_shots() const {
            return total_shots;
        }
        int get_goal_shots() const {
            return goal_shots;
        }
    private:
        int total_shots, goal_shots;
};

int count_1s(int n) {
    int count = 0, tmp = n;
    while(n != 0) {
        count++;
        tmp = n - 1;
        n = tmp & n;
    }
    return count;
}

std::vector<int> shots(const Game& game) {
    std::vector<int> v;
    int combinations = (1 << game.get_total_shots());
    for(int i = 0; i < combinations; i++) {
        v.push_back(0);
    }
    for(int i = 0; i < combinations; i++) {
        if(count_1s(i) >= game.get_goal_shots()) {
            v[count_1s(i)]++;
        }
    }
    return v;
}

int probability_bound(Game game1, Game game2) {
    double p = 0;
    std::vector<int> shots1 = shots(game1);
    std::vector<int> shots2 = shots(game2);
    // TODO : solve nonlinear equations
    return p;
}

/**
 * You have a basketball hoop and someone says that you can play one of two games.
 * Game 1: You get one shot to make the hoop.
 * Game 2: You get three shots and you have to make two of three shots.
 * If p is the probability of making a particular shot, for which values of p
 * should you pick one game or the other.
 */
int main() {
    std::cout << "=========================================================================\n"
                 "Calculating probability for which one game or the other should be picked.\n"
                 "=========================================================================\n";
    Game game1(1, 1);
    Game game2(2, 3);
    // int p_bound = probability_bound(game1, game2);
    std::cout << "After solving the problem on a paper:\n"
                 "Game 1 should be played for p in range (0, 0.5) and game 2 for p in "
                 "range (0.5, 1). It doesn't matter which game will be played for p = "
                 "0, 0.5 or 1.\n";
}       