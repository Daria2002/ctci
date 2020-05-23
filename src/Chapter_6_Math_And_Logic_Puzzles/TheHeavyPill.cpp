#include <iostream>
#include <array>
#include <ctime>
#include <cstdlib>

#define NUM_OF_BOTTLES 20

std::array<double, NUM_OF_BOTTLES> initialize_weights() {
    std::array<double, NUM_OF_BOTTLES> bottle_weights;
    srand(std::time(NULL));
    int heaviest_bottle = rand() % NUM_OF_BOTTLES;
    std::cout << "Randomly selected heaviest bottle is bottle no. " << heaviest_bottle << '\n'; 
    for(int i = 0; i < NUM_OF_BOTTLES; i++) {
        bottle_weights[i] = i == heaviest_bottle ? 1.1 : 1; 
    }
    return bottle_weights;
}

double scale_bottles(std::array<double, NUM_OF_BOTTLES> bottles) {
    double weight = 0;
    for(int i = 0; i < NUM_OF_BOTTLES; i++) {
        weight += (i + 1) * bottles[i];
    }
    return weight;
}

int heaviest_bottle(std::array<double, NUM_OF_BOTTLES> bottles) {
    double weight_all_1g = NUM_OF_BOTTLES * (NUM_OF_BOTTLES + 1) / 2;
    double weight = scale_bottles(bottles);
    // i.e. if heaviest bottle is bottle no. 5, than sum = 210.5, and sum_all_1g = 210
    int heaviest = (weight - weight_all_1g) / 0.1; 
    return heaviest; 
}

/**
 * You have 20 bottles of pills. 19 bottles have 1.0 gram pills, but one has pills
 * of weight 1.1 grams. Given a scale that provides an exact measurement, how would
 * you find the heavy bottle? You can only use the scale once.
 */
int main() {
    std::cout << "=======================================================\n"
                 "Program for finding the bottle with the heaviest pills.\n"
                 "=======================================================\n";
    std::array<double, NUM_OF_BOTTLES> bottle_weights = initialize_weights();
    std::cout << "After calculation: the heaviest bottle is bottle no. " << heaviest_bottle(bottle_weights) << '\n'; 
}