#include <iostream>

/**
 * Draw an entity-relationship diagram for a database with companies, 
 * people, and professionals (people who work for companies).
*/
int main() {
    std::cout << 
    "People will have attributes PID, Pname, Sex, DOB, Phone and Address.\n"
    "Professional will have all attributes that People have and Degree and Experience.\n"
    "Works for relationship can store attributes such as date of joining and salary.\n"
    "Companies can have 3 attributes: CID, CName, Address. ISA = is a\n"
    "People <-(ISA) Professional -(N) /Works for\\ -(1) Companies.\n"
    "There is many to one relationship between pro and co.\n";
}
