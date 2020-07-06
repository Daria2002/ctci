#include <iostream>
#include <list>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <memory>
#include <vector>

class Person {
    public:
        int get_id() {
            return id;
        }
        std::vector<int> get_friends() {
            // TODO
        }
    private:
        int id;
};

class PathNode {
    public:
        PathNode(Person person, PathNode node) {

        }
        Person get_person() {

        }
};

class BFSData {
    public:
        BFSData(Person person) {
            // TODO
        }
        bool is_finished() {
            // TODO
        }
        std::queue<PathNode> to_visit;
        std::unordered_map<int, PathNode> visited;
};

std::list<std::shared_ptr<Person>> merge_paths(BFSData source_data, BFSData dest_data, int id) {
    // TODO
}

std::shared_ptr<Person> search_level(std::unordered_map<int, Person> people, BFSData primary, BFSData secondary) {
    int count = primary.to_visit.size();
    for(int i = 0; i < count; i++) {
        PathNode pathNode = primary.to_visit.front();
        primary.to_visit.pop();
        Person person = pathNode.get_person();
        int person_id = person.get_id();
        if(std::find(secondary.visited.begin(), secondary.visited.end(), person_id) != secondary.visited.end()) {
            return std::make_shared<Person>(person);
        }
        std::vector<int> friends = person.get_friends();
        for(int friend_id : friends) {
            if(std::find(primary.visited.begin(), primary.visited.end(), person_id) == primary.visited.end()) {
                Person friend_ = people[friend_id];
                PathNode next(friend_, pathNode);
                primary.visited[friend_id] = next;
                primary.to_visit.push(next);
            }
        }
    }
    return nullptr;
}

std::list<std::shared_ptr<Person>> findPathBiBFS(std::unordered_map<int, Person> people, int source, int dest) {
    BFSData source_data(people[source]);
    BFSData dest_data(people[dest]);
    while (!source_data.is_finished() && !dest_data.is_finished()) {
        std::shared_ptr<Person> collision_person = search_level(people, source_data, dest_data);
        if(collision_person != nullptr) {
            return merge_paths(source_data, dest_data, collision_person -> get_id());
        }
        collision_person = search_level(people, dest_data, source_data);
        if(collision_person != nullptr) {
            return merge_paths(source_data, dest_data, collision_person -> get_id());
        }
    }
    std::list<std::shared_ptr<Person>> result;
    return result;
}

/**
 * How would you design the data structures for a very large social network like Facebook or Linkedln? 
 * Describe how you would design an algorithm to show the shortest path between two people 
 * (e.g., Me -> Bob -> Susan -> Jason -> You).
*/
int main() {

}
