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
        void park_in_spot(std::shared_ptr<ParkingSpot>& spot);
        // remove vehicle from spot, notify spot that it's gone
        void clear_spots();
        bool can_fit_in_spot(ParkingSpot spot);
    private:
        std::vector<std::shared_ptr<ParkingSpot>> spots; // parking spots taken by this vehicle
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

class ParkingSpot {
    public:
        std::shared_ptr<Level> level;
        int row, number;
        SpotSize spot_size;
        ParkingSpot(std::shared_ptr<Level> l, int r, int n, SpotSize s) : level(l), row(r), number(n), spot_size(s) {}
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

class Level {
    public:
        std::vector<ParkingSpot> spots;
        const int spots_per_row = 10;
        Level(int f, int num_of_spots) : floor(f), number_of_spots(num_of_spots) {
            available_spots = number_of_spots; // at the begining all spots are available
        }
        int available_spots = 0;
        bool park_vehicle(Vehicle v) {
            int first_spot = find_available_spots(v);
            if(first_spot == -1) {
                std::cout << "There is no available spot\n";
                return false;
            }
            for(int i = first_spot; i < v.spots_needed; i++) {
                spots[i].park(v);
            }
            return true;
        }
        void spot_freed() {
            available_spots++;
        }
        int find_available_spots(Vehicle v) {
            for(int i = 0; i < spots.size() - v.spots_needed; i = i + v.spots_needed) {
                if([&] {
                    for(int j = i; j < i + v.spots_needed; j++) {
                        if(!spots[j].free) return -1;
                    }
                    return i;
                } () != -1) {
                    return i;
                } 
            }
            return -1;
        }
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
            for(Level& level : levels) {
                if(level.park_vehicle(vehicle)) {
                    return true;
                }
            }
            return false;
        }
};

bool Vehicle::can_fit_in_spot(ParkingSpot spot) {
    if(spot.spot_size >= spot_size) {
        return true;
    }
    return false;
}

void Vehicle::clear_spots() {
    for(std::shared_ptr<ParkingSpot>& spot : spots) {
        spot -> remove_vehicle();
    }
    spots.clear();
}

void Vehicle::park_in_spot(std::shared_ptr<ParkingSpot>& spot) {
    spot -> park(*this);
    spots.push_back(spot);
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
