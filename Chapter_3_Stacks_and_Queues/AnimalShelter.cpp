#include <iostream>
#include <queue>
#include <map>
#include <sstream>
#include <functional>
#include "../include/stack/StackExceptions.hpp"

class Animal {
    public:
        Animal(const std::string name) : _name(name) {
            order++;
            _animal_order = order;
        }
        Animal() {
            order++;
            _animal_order = order;
        }
        int get_order() const {
            return _animal_order;
        } 
        std::string _name;
    private:
        static int order;
        int _animal_order;
};

int Animal::order = 0;

std::map<std::string, std::function<Animal(
    std::queue<Animal>&, std::queue<Animal>&, std::vector<std::string>&)>> get_functions() {
    std::map<std::string, std::function<Animal(
        std::queue<Animal>&, std::queue<Animal>&, std::vector<std::string>&)>> functions;
    functions.emplace("enqueue", [&](std::queue<Animal>& cats, std::queue<Animal>& dogs,
     std::vector<std::string>& command_and_arguments) {
        Animal animal(command_and_arguments[2]);
        if(command_and_arguments[1] == "cat") {
            cats.push(animal);
        } else if(command_and_arguments[1] == "dog") {
            dogs.push(animal);
        } else {
            invalid_stack_command e;
            throw e;
        }
        return animal;
    });
    functions.emplace("dequeueAny", [&](std::queue<Animal>& cats, std::queue<Animal>& dogs,
     std::vector<std::string>&) {
        Animal oldest;
        if(cats.empty() && dogs.empty()) {
            empty_stack_exception e;
            throw e;
        } else if(cats.empty() && !dogs.empty()) {
            oldest = dogs.front();
            dogs.pop();
        } else if(!cats.empty() && dogs.empty()) {
            oldest = cats.front();
            cats.pop();
        } else if(cats.front().get_order() < dogs.front().get_order()) {
            oldest = cats.front();
            cats.pop();
        } else {
            oldest = dogs.front();
            dogs.pop();
        }
        std::cout << oldest.get_order() << '\n';
        std::cout << "Dequeue " << oldest._name << '\n';
        return oldest;
    });
    functions.emplace("dequeueDog", [&](std::queue<Animal>& cats, std::queue<Animal>& dogs,
     std::vector<std::string>&) {
        if(dogs.empty()) {
            empty_stack_exception e;
            throw e;
        }
        Animal oldest_dog = dogs.front();
        dogs.pop();
        std::cout << "Dequeue " << oldest_dog._name << '\n';
        return oldest_dog;
    });
    functions.emplace("dequeueCat", [&](std::queue<Animal>& cats, std::queue<Animal>& dogs,
     std::vector<std::string>&) {
        if(cats.empty()) {
            empty_stack_exception e;
            throw e;
        }
        Animal oldest_cat = cats.front();
        cats.pop();
        std::cout << "Dequeue " << oldest_cat._name << '\n';
        return oldest_cat;
    });
    return functions;
}

std::vector<std::string> str_to_arr(const std::string& str, const char& regex) {
    std::stringstream ss(str);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, regex)) {
        if (item.length() > 0) {
            elems.push_back(item);  
        }
    }
    return elems;
}

void process_queue_operations() {
    std::map<std::string, std::function<Animal(
        std::queue<Animal>&, std::queue<Animal>&, std::vector<std::string>&)>> functions = get_functions();
    std::string input;
    std::queue<Animal> cats;
    std::queue<Animal> dogs;
    while(true) {
        std::cout << "Please enter command:\n";
        std::getline(std::cin, input);
        if(input == "STOP") {
            std::cout << "Program stopped.\n";
            return;
        }
        std::vector<std::string> command_and_args = str_to_arr(input, ' ');
        std::string command = command_and_args.at(0);
        if((command != "enqueue" && command != "dequeueAny" && command != "dequeueDog" &&
            command != "dequeueCat") || command_and_args.size() < 1) {
            invalid_stack_command e;
            throw e;
        }
        functions[command](cats, dogs, command_and_args);
        std::cout << "Number of cats = " << cats.size() << '\n';
        std::cout << "Number of dogs = " << dogs.size() << '\n';
    }
    return;
}

/**
 * An animal shelter, which holds only dogs and cats, operates on a strictly "first in, first out" basis.
 * People must adopt either the "oldest" (based on arrival time) of all animals at the shelter, or they can
 * select whether they would prefer a dog or a cat (and will receive the oldest animal of that type).
 * They cannot select which specific animal they would like. Create the data structures to maintain this
 * system and implement operations such as enqueue, dequeueAny, dequeueDog and dequeueCat. You may use the 
 * built-in LinkedList data structure.
 * Available commands:
 * enqueue arg1 arg2 (arg1 - cat/dog, arg2 - animal name)
 * denqueueAny
 * denqueueCat
 * denqueueDog
 */
int main() {
    std::cout << "======================\n"
                 "Animal shelter program\n"
                 "======================\n";
    process_queue_operations();
}