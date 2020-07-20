#include <iostream>

/**
 * What are the different types of joins? Please explain how they differ 
 * and why certain types are better in certain situations.
*/
int main() {
    std::cout << 
    "JOIN is used to combine the results of two tables. The join type\n"
    "defines which records will go into the result set. I.e. there are\n"
    "two tables 'regular' beverages and calorie-free beverages. Diet\n"
    "Coca-Cola and Coca-Cola have the same code COCACOLA.\n"
    "INNER JOIN: The result set would contain only the data where the\n"
    "            criteria match. In our example, we would get three records:\n"
    "            1 COCACOLA code and 2 PEPSI codes.\n"
    "OUTER JOIN: An OUTER JOIN will always contain the results of INNER JOIN,\n"
    "            but it may also contain some records that have no matching\n"
    "            record in the other table. OUTER JOIN's are divided into the\n"
    "            3 subtypes(LEFT OUTER JOIN, RIGHT OUTER JOIN, FULL OUTER JOIN):\n"
    "            LEFT (OUTER) JOIN - the result will contain all rcds from the left\n"
    "            table and if no matching rcds were found in the right table, then its\n"
    "            fields will contain the NULL values. In our example, there would be 4\n"
    "            rcds: the same as INNER JOIN and 1 BUDWEISER.\n"
    "            RIGHT (OUTER) JOIN - It will contain every rcd from right table, the\n"
    "            missing fields from the left table will be NULL. The result will contain\n"
    "            5 rcds: the same as INNER JOIN and 1 FRESCA code and 1 Water code.\n"
    "            FULL OUTER JOIN: all rcds from both tables will be included in the result\n"
    "            set. If no matching rcd found, corresponding result fields will be NULL. in\n"
    "            our example, the result will have 6 rcds (every code will appear 1 time, except\n"
    "            PEPSI, it will appear 2 times.\n";
}
