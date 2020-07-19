#include <iostream>

/**
 * Write a SQL query to get a list of tenants who are renting
 * more than one apartment.
*/
int main() {
    std::cout << "Whenever you write a GROUP BY clause in an interview\n"
                 "(or in real life), make sure that anything in the SELECT\n"
                 "clause is either an aggregate function or contained within\n"
                 "the GROUP BY clause. count(*) in this example counts number of\n"
                 "rows for each TenantID. SQL query to get a list of tenants who\n"
                 "are renting more than one apartment:\n"
                 "SELECT TenantName\n"
                 "FROM Tenants\n"
                 "INNER JOIN\n"
                 "  (SELECT TenantID FROM AptTenants GROUP BY TenantID HAVING count(*) > 1) C\n"
                 "ON Tenants.TenantID = C.TenantID\n";
}