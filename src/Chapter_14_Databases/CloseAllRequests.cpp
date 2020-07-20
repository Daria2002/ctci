#include <iostream>

/**
 * Building #11 is undergoing a major renovation. Implement a query to 
 * close all requests from apartments in this building.
*/
int main() {
    std::cout << 
    "The UPDATE statement is used to modify the existing records in a table\n"
    "i.e. update the 1st customer (id = 1) with a new contact person and a new city:\n"
    "UPDATE Costumers\n"
    "SET ContactName = 'Alfred Schmidt', City = 'Frankfurt'\n"
    "WHERE CustomerID = 1\n"
    "WHERE IN returns values that matches values in a list or subquery.\n"
    "WHERE IN is shorthand for multiple OR conditions\n"
    "i.e. select all customers that are from the same countries as suppliers:\n"
    "SELECT * FROM Customers\n"
    "WHERE Country IN (SELECT Country FROM Suppliers)"
    "Solution for closing all requests for apartments in building #11:\n"
    "UPDATE Requests\n"
    "SET Status = 'Closed'\n"
    "WHERE AptId IN (SELECT AptID FROM Apartments WHERE BuildingID = 11)\n";
}
