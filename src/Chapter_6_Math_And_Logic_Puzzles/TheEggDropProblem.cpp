#include <iostream>
#include <cmath>

int first_drop(const int floors) {
    // minimizing the number of drops for the worst case
    // 1st egg drop from xth floor, if it's broken 2nd egg should drop from [1, 2, ..., (x-1)] till it's broken (x drops total)
    // if 1st egg is not broken after dropping from xth floor it will drop from x + (x-1) floor
    // why (x-1)? because we want to have constant number of drops for every case. so, 1st egg had 2 drops and if it's broken
    // 2nd egg would have to check (in the worst case) x - 2 drops (total x drops). If the 2nd drop floor is x + x and 1st egg 
    // broke on x + x floor, 2nd egg would need to (int the worst case) drop x - 1 time to check where is the break-floor. In that
    // case there would be 2 drops for the 1st egg (xth floor, x+x th floor) and x - 1 drops for the 2nd egg, total x + 1 drops
    // the main goal is to have x drops in worst case (worst case: break-floor is right before the one where 1st egg got broken, 
    // so 2nd egg needs to check(drop) previous_floor_1st_egg - break_floor_1st_egg number of floors), best case would be that 2nd 
    // egg checks 1st floor after previous_floor_1st_egg and obtain that it's the break-floor
    // x + (x-1) + (x-2) + ... + 2 + 1 = 100 -> x(x + 1)/2 = 100
    double root = std::sqrt(1 + 4 * 1 * 2 * floors);
    int result = std::round((-1 + root) / 2.);
    return result;
}

bool drop(const int breaking_floor, const int current_floor) {
    return current_floor >= breaking_floor;
}

int drop_to_find_breaking_point(const int breaking_floor, const int floors, int step) {
    int egg1_floor = step, egg2_floor = 0;
    // while egg1 is not broken
    while(!drop(breaking_floor, egg1_floor) && egg1_floor <= floors) {
        step--;
        egg2_floor = egg1_floor + 1;
        egg1_floor += step;
    }
    // looking for a drop floor
    while (egg2_floor < egg1_floor && egg2_floor <= floors && !drop(breaking_floor, egg2_floor)) {
        egg2_floor++;
    }
    return ((egg2_floor > floors) ? floors : egg2_floor);
}

/**
 * There is a building of 100 floors. If an egg drops from the Nth floor or above it will break.
 * If it's dropped from any floor below, it will not break. You're given 2 eggs. Find N, and 
 * minimize the number of drops for the worst case.
 */
int main() {
    std::cout << "==========================================\n"
                 "Program for minimizing number of egg drops\n"
                 "==========================================\n";
    std::cout << "Enter the number of floors:\n";
    int floors, breaking_floor;
    std::cin >> floors;
    const int step = first_drop(floors);
    std::cout << "First drop floor should be " << step << ".\n";
    std::cout << "Enter breaking floor:\n";
    std::cin >> breaking_floor;
    std::cout << "After dropping check, breaking floor = " << drop_to_find_breaking_point(breaking_floor, floors, step) << ".\n";
}
