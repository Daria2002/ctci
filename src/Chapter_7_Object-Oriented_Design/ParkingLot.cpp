#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>

class ParkingSpot;
class Level;
class Vehicle;
class Car;
class Motorcycle;
class Bus;
class Parkinglot;
class ParkingSpot;

enum SpotSize {
    Tiny, Compact, Large
};

class Vehicle {
    public:
        int spots_needed;
        int id;
        SpotSize spot_size;
        std::string license_plate;
        void park_in_spots(std::shared_ptr<ParkingSpot> spot) {
            spots.push_back(spot);
        }
        bool can_fit_in_spot(ParkingSpot spot);
    private:
        std::vector<std::shared_ptr<ParkingSpot>> spots;
};

class Car final : public Vehicle {
    public: 
        Car(int i) {
            id = i;
            spots_needed = 1;
            spot_size = SpotSize::Compact;
        }
};

class Motorcycle final : public Vehicle {
    public: 
        Motorcycle(int i) {
            id = i;
            spots_needed = 1;
            spot_size = SpotSize::Tiny;
        }   
};

class Bus final : public Vehicle {
    public: 
        Bus(int i) {
            id = i;
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
            // todo
            return true;
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

bool Vehicle::can_fit_in_spot(ParkingSpot spot) {
    if(spot.spot_size >= spot_size) {
        return true;
    }
    return false;
}

std::vector<Vehicle> generate_random_vehcles() {
    std::vector<Vehicle> vehicles;
    srand(time(0));
    constexpr int max_num_of_one_type_vehicles = 10;
    const int num_of_motorcycles = rand() % max_num_of_one_type_vehicles;
    const int num_of_cars = rand() % max_num_of_one_type_vehicles;
    const int num_of_buses = rand() % max_num_of_one_type_vehicles;
    for(int i = 0; i < num_of_motorcycles; i++) {
        vehicles.push_back(Motorcycle(i));
    }
    for(int i = num_of_motorcycles; i < num_of_cars + num_of_motorcycles; i++) {
        vehicles.push_back(Car(i));
    }
    for(int i = num_of_motorcycles + num_of_cars; i < num_of_buses + num_of_motorcycles + num_of_cars; i++) {
        vehicles.push_back(Bus(i));
    }
    return vehicles;
}

ParkingLot build_parking_lot() {
    ParkingLot parking_lot;
    return parking_lot;
}

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
    std::vector<Vehicle> vehicles = generate_random_vehcles();
    ParkingLot parking_lot = build_parking_lot();
}
