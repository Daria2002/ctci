#include <iostream>
#include <list>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <vector>
#include <memory>

class Person {
    public:
        Person() = default;
        Person(int _id) : id(_id) {}
        int get_id() {
            return id;
        }
        void add_friends(std::vector<int> f) {
            friends = f;
        }
        std::vector<int> get_friends() {
            return friends;
        }
    private:
        int id;
        std::vector<int> friends;
};

class PathNode : public std::enable_shared_from_this<PathNode> {
    public:
        std::weak_ptr<PathNode> previous_node;
        PathNode() = default;
        PathNode(Person person, std::shared_ptr<PathNode> node) {
            previous_node = node;
            p = person;
        }
        Person get_person() {
            return p;
        }

        std::list<Person> collapse(bool starts_with_root) {
            std::list<Person> path;
            std::shared_ptr<PathNode> node = shared_from_this();
            while(node != nullptr) {
                if(starts_with_root) {
                    path.push_back(node -> get_person());
                } else {
                    path.push_front(node -> get_person());
                }
                node = (node -> previous_node).lock();
            }
            return path;
        }
    private:
        Person p;
};

class BFSData {
    public:
        BFSData(Person source) {
            std::shared_ptr<PathNode> source_path = std::make_shared<PathNode>(source, nullptr);
            to_visit.push(source_path);
            visited.emplace(source.get_id(), source_path);
        }
        bool is_finished() {
            return to_visit.empty();
        }
        std::queue<std::shared_ptr<PathNode>> to_visit;
        std::unordered_map<int, std::shared_ptr<PathNode>> visited;
};

std::list<Person> merge_paths(BFSData source_data, BFSData dest_data, int collision_id) {
    std::list<Person> source_path = source_data.visited[collision_id]->collapse(false);
    std::list<Person> dest_path = dest_data.visited[collision_id]->collapse(true);
    dest_path.pop_front(); // remove collision node
    for(Person p : dest_path) {
        source_path.push_back(p);
    }
    return source_path;
}

bool contains(std::unordered_map<int, std::shared_ptr<PathNode>> map, int id) {
    for(const auto& [key, val] : map) {
        if(key == id) return true;
    }
    return false;
}

std::shared_ptr<Person> search_level(std::unordered_map<int, Person> people, BFSData& primary, BFSData& secondary) {
    int count = primary.to_visit.size();
    for(int i = 0; i < count; i++) {
        std::shared_ptr<PathNode> pathNode = primary.to_visit.front();
        primary.to_visit.pop();
        Person person = pathNode->get_person();
        int person_id = person.get_id();
        if(contains(secondary.visited, person_id)) {
            return std::make_shared<Person>(person);
        }
        std::vector<int> friends = person.get_friends();
        for(int friend_id : friends) {
            if(!contains(primary.visited, friend_id)) {
                Person friend_ = people[friend_id];
                std::shared_ptr<PathNode> next = std::make_shared<PathNode>(friend_, pathNode);
                primary.visited[friend_id] = next;
                primary.to_visit.push(next);
            }
        }
    }
    return nullptr;
}

std::list<Person> findPathBiBFS(std::unordered_map<int, Person> people, int source, int dest) {
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
    std::list<Person> result;
    return result;
}

std::unordered_map<int, Person> initialize_network() {
    std::unordered_map<int, Person> people;
    Person m(1);
    Person a(2);
    Person d(3);
    Person c(4);
    Person l(5);
    Person k(6);
    m.add_friends({2, 3});
    a.add_friends({3, 4});
    d.add_friends({2, 5});
    c.add_friends({5, 6});
    l.add_friends({3, 4});
    k.add_friends({4});
    people[m.get_id()] = m;
    people[a.get_id()] = a;
    people[d.get_id()] = d;
    people[c.get_id()] = c;
    people[l.get_id()] = l;
    people[k.get_id()] = k;
    return people;
}

/**
 * How would you design the data structures for a very large social network like Facebook or Linkedln? 
 * Describe how you would design an algorithm to show the shortest path between two people 
 * (e.g., Me -> Bob -> Susan -> Jason -> You).
*/
int main() {
    std::cout << "Social network\n";
    std::unordered_map<int, Person> people = initialize_network();
    std::list<Person> path = findPathBiBFS(people, 3, 6);
    while(!path.empty()) {
        std::cout << path.front().get_id() << '\n';
        path.pop_front();
    }
    return 0;
}
