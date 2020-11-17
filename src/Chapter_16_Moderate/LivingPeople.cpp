#include<iostream>
#include<vector>

class Person {
    public:
        Person(int b, int d): birth(b), death(d) {}
        int birth, death; 
};

/**
 * Time complexity = O(RP), R-range of years, P-num of people
 */
int max_alive_year_bf(const std::vector<Person>& people, const int min, const int max) {
    int max_alive = 0; 
    int max_alive_year = min;
    for(int year = min; year <= max; year++) {
        int alive = 0;
        for(const Person person : people) {
            if(person.birth <= year && person.death >= year) alive++;
        }
        if(alive > max_alive) {
            max_alive = alive;
            max_alive_year = year;
        }
    }
    return max_alive_year;
}

void increment_range(std::vector<int>& years, int start, int end) {
    for(int i  = start; i <= end; i++) {
        years[i]++;
    }
}

std::vector<int> create_year_map(const std::vector<Person>& people, int min, int max) {
    std::vector<int> years(max - min + 1, 0);
    for(Person person : people) increment_range(years, person.birth - min, person.death - min);
    return years;
}

int get_max_index(const std::vector<int>& years) {
    int max = 0; 
    for(int i = 0; i < years.size(); i++) {
        if(years[i] > years[max]) {
            max = i;
        }
    }
    return max;
}

/**
 * Time complexity: O(P*Y + R), P-num of people, Y-years that person is alive, R-range of years [max-min]
 * in worst case Y = R -> O(P*Y + R) = O(P*R + R) = O(PR)
 */
int max_alive_year_better_bf(std::vector<Person> people, const int min, const int max) {
    std::vector<int> years = create_year_map(people, min, max);
    int best = get_max_index(years);
    return min + best;
}

void swap(int& el1, int& el2) {
    int tmp = el1;
    el1 = el2;
    el2 = tmp;
}

int partition(std::vector<int>& years, int low, int high) {
    int pivot = years[high];
    int i = low - 1; // i - index of smaller element
    for(int j = low; j <= high - 1; j++) {
        if(years[j] < pivot) {
            i++;
            swap(years[j], years[i]);
        }
    }
    swap(years[i + 1], years[high]);
    return (i + 1);
}

void quick_sort(std::vector<int>& years, int low, int high) {
    if(low < high) {
        int pivot = partition(years, low, high);
        quick_sort(years, low, pivot - 1);
        quick_sort(years, pivot + 1, high);
    }
}

std::vector<int> get_sorted_years(std::vector<Person> people, bool births) {
    std::vector<int> years(people.size());
    for(int i = 0; i < people.size(); i++) {
        years[i] = births ? people[i].birth : people[i].death;
    }
    quick_sort(years, 0, years.size() - 1);
    return years;
}

/**
 * Time complexity: O(PlogP), P-num of people
 * PlogP + PlogP - sorting, P + P - while loop
 * O(PlogP + PlogP + P + P) = O(2PlogP + 2P) = O(PlogP)
 */
int max_alive_year_optimal(std::vector<Person> people, int min, int max) {
    std::vector<int> sorted_births = get_sorted_years(people, true);
    std::vector<int> sorted_deaths = get_sorted_years(people, false);

    int birth_index = 0;
    int death_index = 0;
    int alive = 0;
    int max_alive = 0; 
    int max_alive_year = min;

    while (birth_index < sorted_births.size()) {
        if(sorted_births[birth_index] <= sorted_deaths[death_index]) {
            alive++;
            if(alive > max_alive) {
                max_alive = alive;
                max_alive_year = sorted_births[birth_index];
            }
            birth_index++;
        } else {
            alive--;
            death_index++;
        }
    }
    return max_alive_year;
}

std::vector<int> get_population_change(std::vector<Person> people, int min, int max) {
    std::vector<int> population_change(max - min + 1);
    for(int i = 0; i < people.size(); i++) {
        population_change[people[i].birth - min] += 1;
        // still alive in people[i].death year, decrement in people[i].death + 1
        population_change[people[i].death - min + 1] -= 1; 
    }
    return population_change;
}

int get_max_alive_year(std::vector<int> delta) {
    int max = 0;
    int alive = 0;
    int max_year = 0;
    for(int i = 0; i < delta.size(); i++) {
        alive += delta[i];
        if(alive > max) {
            max = alive;
            max_year = i;
        }
    }
    return max_year;
}

/**
 * More optimal: get rid of the sorting step
 */
int max_alive_year_more_optimal(std::vector<Person> people, int min, int max) {
    std::vector<int> population_change = get_population_change(people, min, max);
    int max_alive_year = get_max_alive_year(population_change);
    return max_alive_year + min;
}

std::vector<Person> get_living_people_list() {
    std::vector<Person> people;
    people.push_back(Person(1900, 1950));
    people.push_back(Person(1920, 1927));
    people.push_back(Person(1901, 1981));
    people.push_back(Person(1950, 2000));
    people.push_back(Person(1913, 1978));
    people.push_back(Person(1905, 1977));
    people.push_back(Person(1944, 1964));
    people.push_back(Person(1989, 1976));
    people.push_back(Person(1901, 1984));
    people.push_back(Person(1902, 1990));
    people.push_back(Person(1918, 1999));
    people.push_back(Person(1915, 2000));
    return people;
}

/**
 * Living People: Given a list of people with their birth and death years, implement a method to
 * compute the year with the most number of people alive. You may assume that all people were born
 * between 1900 and 2000 (inclusive). If a person was alive during any portion of that year, they should
 * be included in that year's count. For example, Person (birth = 1908, death = 1909) is included in the
 * counts for both 1908 and 1909.
 */
int main() {
    std::cout << "Computing the year with the most number of people alive: Enter 1 if you want to use BF approach,\n"
    "2 for slightly better BF approach, 3 for optimal approach and any other number for even more optimal approach.\n";
    int method;
    std::cin >> method;
    std::vector<Person> people = get_living_people_list();
    int year;
    switch (method)
    {
    case 1:
        year = max_alive_year_bf(people, 1900, 2000);
        break;
    case 2:
        year = max_alive_year_better_bf(people, 1900, 2000);
        break;
    case 3:
        year = max_alive_year_optimal(people, 1900, 2000);
        break;
    default:
        year = max_alive_year_more_optimal(people, 1900, 2000);
        break;
    }
    std::cout << "The year with the most number of people alive is " << year << ".\n";
}