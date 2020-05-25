#include <iostream>

/**
 * Imagine people sitting in the circle. Blue-eyed people need to deduce that they are the one who
 * need to leave. There is at least one blue-eyed person.
 * case n = 1 : a blue-eyed person sees that no one in the circle has blue eyes, so blue-eyed person
 *              deduce that he is a blue-eyed person and that he has to leave the circle.
 * case n = 2 : first day both of the blue-eyed people see only one person in the circle with a blue eyes.
 *              The rest of the people see two people with a blue eyes. After first day none of the blue-eyed
 *              people has left the circle because they expected that one person with a blue eyes to leave.
 *              After realising that there is someone with a blue eyes that another blue-eyed person expects 
 *              to leave, second person with a blue eyes can deduce that if he sees only one blue-eyed person, 
 *              and he doesn't see person which made first blue-eyed person stay in the circle, it's he/she who
 *              has blue-eyes and should leave the circle. The second day both of the blue-eyed people leaves.
 */
int leaving_time(int n) {
    return n;
}

/**
 * A bunch of people are living on an island, when a visitor comes with a strange order : all the blue-eyed people 
 * must leave the island as soon as possible. There will be a flight out at 8 PM every evening.Each person can see 
 * everyone else’s eye color, but they do not their own(nor is anyone allowed to tell them). Additionally they do 
 * not know how many people have blue eyes, although they do know that at least one person does. How many days will 
 * it take to blue-eyed people to leave?
 */
int main() {
    std::cout << "============================================================================================\n"
                 "Program for calculating the number of days that takes n blue eyed people to leave the island\n"
                 "============================================================================================\n";
    std::cout << "Enter the number of people with a blue eyes:\n";
    int n;
    std::cin >> n;
    std::cout << "It takes " << leaving_time(n) << " day(s) to leave the island.\n";
}