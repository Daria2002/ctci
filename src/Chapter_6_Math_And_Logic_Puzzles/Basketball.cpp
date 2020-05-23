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
    while(tmp != 0) {
        count++;
        tmp = n - 1;
        n = tmp & n;
    }
    return tmp;
}

std::vector<int> shots(const Game& game) {
    std::vector<int> v;
    for(int i = 0; i <= game.get_total_shots() - game.get_goal_shots(); i++) {
        v.push_back(0);
    }
    for(int i = 0; i < game.get_total_shots(); i++) {
        if(count_1s(i) >= game.get_goal_shots()) {
            v[game.get_total_shots() - game.get_goal_shots()]++;
        }
    }
    return v;
}

int probability_bound(Game game1, Game game2) {
    double p;
    std::vector<int> shots1 = shots(game1);
    std::vector<int> shots2 = shots(game2);
    // TODO
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
    int p_bound = probability_bound(game1, game2);
}       