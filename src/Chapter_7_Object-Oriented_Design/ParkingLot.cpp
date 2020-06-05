#include <iostream>
#include <vector>
#include <memory>

class ParkingSpot;
class Level;
class Vehicle;
class Car;
class Motorcycle;
class Bus;
class Parkinglot;
class ParkingSpot;

enum SpotSize {
    Motorcycle, Compact, Large
};

class Vehicle {
    public:
        int spots_needed;
        SpotSize spot_size;
        std::string license_plate;
        void park_in_spots(std::shared_ptr<ParkingSpot> spot) {
            spots.push_back(spot);
        }
        bool can_fit_in_spot(ParkingSpot spot) {
            if(spot.spot_size >= spot_size) {
                return true;
            }
        }
    private:
        std::vector<std::shared_ptr<ParkingSpot>> spots;
};

class Car final : public Vehicle {
    public: 
        Car() {
            spots_needed = 1;
            spot_size = SpotSize::Compact;
        }
};

class Motorcycle final : public Vehicle {
    public: 
        Motorcycle() {
            spots_needed = 1;
            spot_size = SpotSize::Motorcycle;
        }   
};

class Bus final : public Vehicle {
    public: 
        Bus() {
            spots_needed = 5;
            spot_size = SpotSize::Large;
        }   
};

class Level {
    public:
        Level(int f, int num_of_spots) : floor(f), number_of_spots(num_of_spots) {}
    private:
        int floor, number_of_spots;
};

class ParkingLot final {
    public:
        std::vector<Level> levels;
        static constexpr int NUM_LEVELS = 5;
        ParkingLot() {

        }
        bool park_vehicle(Vehicle vehicle) {

        }
};

class ParkingSpot {
    public:
        Level level;
        int row, number;
        SpotSize spot_size;
        ParkingSpot(Level l, int r, int n, SpotSize s) : level(l), row(r), number(n), spot_size(s) {}
        Vehicle vehicle;
        bool free = true;
        void park(Vehicle v) {
            vehicle = v;
            free = false;
        }
        void remove_vehicle() {
            free = true;
        }
};

/**
 * Design a parking lot using object-oriented principles.
 * Assumptions:
 * - the parking lot has multiple levels. Each level has multiple rows of spots.
 * - the parking lot can park motorcycles, cars, and buses. 
 * - the parking lot has motorcycle spots, compact spots, and large spots
 * - a motorcycle can park in any spot
 * - a car can park in either a single compact spot or a single large spot
 * - a bus can park in five large spots that are consecutive and within the same row. It cannot park in small spots.
 */
int main() {
    std::cout << "===========\n"
                 "Parking lot\n"
                 "===========\n";
}
