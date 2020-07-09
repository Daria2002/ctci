#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

class Cache {
    public:
        // query cached
        bool get_result(const std::string query, std::vector<std::string> result) {
            if(map.find(query) == map.end()) return false;
            result = map[query];
            list.push_front(query);
            return true;
        }
        void insert_or_update_result(std::string query, std::vector<std::string> result) {
            // update if already in map
            if(map.find(query) != map.end()) {
                map[query] = result;
                list.push_front(query);
                return;
            }
            list.push_front(query);
            map[query] = result;
            size++;
            // remove the oldest element from hash table and linked list
            if(size > max_size) {
                map.erase(query);
                list.pop_back();
                size--;
            }
        }
    private:
        const int max_size = 10;
        int size = 0;
        std::unordered_map<std::string, std::vector<std::string>> map;
        std::list<std::string> list;
};

/**
 * Imagine a web server for a simplified search engine. This system has 100 machines to 
 * respond to search queries, which may then call out using processSearch(string query) 
 * to another cluster of machines to actually get the result. The machine which responds 
 * to a given query is chosen at random, so you cannot guarantee that the same machine will 
 * always respond to the same request.The method processSearch is very expensive. Design a 
 * caching mechanism for the most recent queries. Be sure to explain how you would update the 
 * cache when data changes.
*/
int main() {
    std::cout << "Step 1: Design a Cache for a Single System\n"
                 "  Obtain query, and call get_result function. If get_result == true\n"
                 "  query is already in the cache and result is saved in vector result.\n"
                 "  If get_result == false, query is not saved in the cache and result is\n"
                 "  obtained calling processSearch(query). Retrived result is saved in the\n"
                 "  cache calling insert_or_update_result function.\n"
                 "Step 2: Expand to Many Machines\n"
                 "  The question is to what extent the cache is shared across machines.\n"
                 "  Option 1: Each machine has its own cache.\n"
                 "  Option 2: Each machine has a copy of the cache.\n"
                 "  Option 3: Each machine stores a segment of the cache.\n - BEST!"
                 "Step 3: Updating results when contents change\n"
                 "  Impose a time out where no query, regardless of how popular it is, can sit\n"
                 "  in the cache for more than x minutes. Result is periodically refreshed data.\n"
                 "Step 4: Further Enhancements\n"
                 "  - Shared cache: An extreme popular queries can be stored in caches on multiple machines\n"
                 "  - Automatic time out: Each URL has a time out value based on how frequently\n"
                 "    the page has been updated in the past.\n";
}
