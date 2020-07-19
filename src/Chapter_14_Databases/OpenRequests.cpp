#include <iostream>

/**
 * Write a SQL query to get a list of all buildings and the number of 
 * open requests (Requests in which status equals 'Open').
*/
int main() {
    std::cout << "ISNULL(Weight, 50) substitutes all NULL entries in the\n"
                 "Weight with 50. The solution join Requests and Aoartmants\n"
                 "to get the list of the building IDs and the number of open\n"
                 "requests. Once we have this list, we join it again with\n"
                 "the building table:\n"
                 "SELECT BuildingName, ISNULL(Count, 0) as 'Count'\n"
                 "FROM Buildings\n"
                 "LEFT JOIN\n"
                 "  (SELECT Apartments.BuildingID, count(*) as 'Count'\n"
                 "   FROM Requests INNER JOIN Apartments\n"
                 "   ON Requests.AptID = Apartments.AptID\n"
                 "   WHERE Requests.Status = 'Open'\n"
                 "   GROUP BY Apartments.BuildingID) ReqCounts\n"
                 "ON ReqCounts.BuildingID = Buildings.BuildingID\n";
}