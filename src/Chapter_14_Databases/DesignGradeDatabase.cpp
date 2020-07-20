#include <iostream>

/**
 * Imagine a simple database storing information for students' grades. 
 * Design what this database might look like and provide a SQL query 
 * to return a list of the honor roll students (top 10%), sorted by 
 * their grade point average.
*/
int main() {
    std::cout << 
    "This db will have 3 objects: Students, Course and Course Enrollment.\n"
    "Course enrollment will pair Students and Courses. It has CourseID,\n"
    "StudentID, Grade and Term fields. The code needs to return 10% of rows,\n"
    "even if this means that our honor roll includes more than 10% of the class.\n"
    "DECLARE @GPACutOff float;\n"
    "SET @GPACutOff = (SELECT min(GPA) as 'GPAMin' FROM(\n"
    "     SELECT TOP 10 PERCENT AVG(CourseEnrollment.Grade) AS GPA\n"
    "     FROM CourseEnrollment\n"
    "     GROUP BY CourseEnrollment.StudentID\n"
    "     ORDER BY GPA desc) Grades);\n"
    "SELECT StudentName, GPA\n"
    "FROM (SELECT AVG(CourseEnrollment.Grade) AS GPA, CourseEnrollment.StudentID\n"
    "      FROM CourseEnrollment\n"
    "      GROUP BY CourseEnrollment.StudentID\n"
    "      HAVING AVG(CourseEnrollment.Grade) >= @GPACutOff) Honors\n"
    "INNER JOIN Students ON Honors.StudentID = Student.StudentID";
}
