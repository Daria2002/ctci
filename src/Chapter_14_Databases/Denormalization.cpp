#include <iostream>

/**
 * What is denormalization? Explain the pros and cons.
*/
int main() {
    std::cout << 
    "Denormalization is a db optimization technique in which we add redundant data to\n"
    "one or more tables. This can help us avoid costly joins in a relational db. In a\n"
    "traditional normalized dbs, we store data in separate logical tables and attempt to\n"
    "minimize redundant data. We may strive to have only one copy of each piece of data in\n"
    "the db. In a normalized db, there would be Courses and Teachers table. Each entry in\n"
    "Courses would store TeachersID for a Course but not the teacherName. When we need to\n"
    "retrieve a list of all Courses with the Teacher name, we would do a join between these\n"
    "two tables. In some ways, this is great; if a teacher changes name, we have to update\n"
    "the name only in one place. The drawback, is that if the tables are large, we may spend\n"
    "an unnecessarily long time doing joins on tables. Denormalization, then, strikes a different\n"
    "compromise. Under denormalization, we decide that we're okay with some redundancy and some\n"
    "extra effort to update the db in order to get the efficiency advantages of fewer joins.\n"
    "Cons of Denormalization: updates and inserts are more expensive, update and insert code is\n"
    "                         harder to write, data may be inconsistent, data redundancy\n"
    "                         necessitates more storage.\n"
    "Pros of Denormalization: retrieving data is faster since we do fewer joins, queries to\n"
    "                         to retrieve can be simpler (and therefore less likely to have bugs),\n"
    "                         since we need to look at fewer tables.\n"
    "In a system thet demands scalability, we almost always use elements of both normalized and\n"
    "denormalized dbs.";
}
