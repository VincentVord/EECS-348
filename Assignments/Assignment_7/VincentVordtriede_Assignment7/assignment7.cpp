// EECS 348 Assignment 7
// Purpose: A C++ program that uses mySQL to create SQL tables in my personal database and then performs 12 queries on those tables
// Inputs: 5 .SQL files given in the assignment description, but technically none since they are hard coded into the file
// Output: 12 tables resulting from 12 different queries on the input tables
// Collaborators: None
// Sources: ChatGPT, EECS 348 lecture and lab material
// Vincent Vordtriede
// 11/17/2025

#include <iostream> //for std::
#include <fstream> //for file reading
#include <string> //for using strings
#include <iomanip>  // for std::setw -- this was suggested to me by ChatGPT

#include <mysql_driver.h>        //Necessary imports for mySQL given in lecture
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>

void runSQLFile (sql::Statement* stmt, const std::string& filename) { //this function iterates through the file and executes each sql command 1 by 1
    std::ifstream file(filename); //open the file
    std::string line; //create empty line string variable
    std::string sql = ""; //this string holds the entire sql one-line command

    while (std::getline(file, line)) { //read from the file and skip the comments 
        if (line.size() == 0 || line[0] == '-') // Skip comments and empty lines
            continue;

        sql += line + " "; //concat the line to the sql string

        // If we reach ; then execute the accumulated statement
        if (line.find(';') != std::string::npos) { //looks for ';' in each line
            try { //if ';' found then
                stmt->execute(sql); //execute the statement
            } catch (sql::SQLException& e) { //if an error accurs in reading the SQL file
                std::cerr << "Error executing SQL in file: " << filename << std::endl; //print error statement and file name
                std::cerr << e.what() << std::endl; //print the error statement
            }
            sql.clear(); //clear command string -reset to empty for the next command
        }
    }
}

int main() { //main entry point for this program
    try { //use try except block to catch SQL errors
        sql::mysql::MySQL_Driver *driver; //create driver pointer using mySQL library
        sql::Connection *con; //create connection pointer using mySQL library
        sql::Statement *stmt; //create statement pointer using mySQL library
        sql::ResultSet *res; //create response pointer using mySQL library

        driver = sql::mysql::get_mysql_driver_instance(); //get mySQL driver
        con = driver->connect("mysql.eecs.ku.edu", "348f25_v731v861", "Eegh3ish");
        stmt = con->createStatement(); //to execute sql statement
        stmt->execute("USE 348f25_v731v861");

        // Load 5 tables from SQL files -- pass in the statement to be executed from the file and the name of the file
        runSQLFile(stmt, "course7.SQL"); 
        runSQLFile(stmt, "enrollment7.SQL");
        runSQLFile(stmt, "faculty7.SQL");
        runSQLFile(stmt, "offering7.SQL");
        runSQLFile(stmt, "student7.SQL");

        //1: Retrieve all student information for those whose major is 'IS' from the Student table
        res = stmt->executeQuery("SELECT * FROM Student7 WHERE StdMajor = 'IS'");
        
        std::cout << "\n1: Retrieve all students majoring in 'IS'\n"; //print query instructions
        std::cout << std::left // Print table header -- use setw to from the iomanip library to give each row a defined width
                << std::setw(15) << "StdNo" //print all necessary column names to the console:
                << std::setw(15) << "FirstName"
                << std::setw(15) << "LastName"
                << std::setw(15) << "City"
                << std::setw(8)  << "State"
                << std::setw(8)  << "Major"
                << std::setw(8)  << "Class"
                << std::setw(6)  << "GPA"
                << std::setw(10) << "Zip"
                << "\n";
        std::cout << std::string(100, '-') << "\n"; // Print separator line
        while (res->next()) { // Print rows
            std::cout << std::left //use std::left to put the text on the left side of the setw
                    << std::setw(15) << res->getString("StdNo") //print all necesary column entries to the console in order:
                    << std::setw(15) << res->getString("StdFirstName")
                    << std::setw(15) << res->getString("StdLastName")
                    << std::setw(15) << res->getString("StdCity")
                    << std::setw(8)  << res->getString("StdState")
                    << std::setw(8)  << res->getString("StdMajor")
                    << std::setw(8)  << res->getString("StdClass")
                    << std::setw(6)  << res->getString("StdGPA")
                    << std::setw(10) << res->getString("StdZip")
                    << "\n";
        }
        delete res; //delete the response so it can be reassigned for the next query

        //2: Retrieve the student numbers of students who have enrolled in more than two courses from the Enrollment table
        res = stmt->executeQuery("SELECT StdNo FROM Enrollment7 GROUP BY StdNo HAVING COUNT(*) >=2"); 
        
        std::cout << "\n2: Retrieve the student numbers of students who have enrolled in 2+ courses from the Enrollment table\n"; //print query instructions
        std::cout << std::left // Print table header -- use setw to from the iomanip library to give each row a defined width
                << std::setw(15) << "StdNo" //print all necessary column names to the console:
                << "\n";
        std::cout << std::string(100, '-') << "\n"; // Print separator line
        while (res->next()) { // Print rows
            std::cout << std::left //use std::left to put the text on the left side of the setw
                    << std::setw(15) << res->getString("StdNo") //print all necesary column entries to the console in order:
                    << "\n";
        }
        delete res; //delete the response so it can be reassigned for the next query

        //3: List the first and last names of all professors from the Faculty table who have been employed for more than 15 years as of 2025, including those
        //hired in 2010 or earlier.
        res = stmt->executeQuery("SELECT FacFirstName, FacLastName FROM Faculty7 WHERE FacHireDate <= '2010-12-31' ");

        std::cout << "\n3: List names of all faculty who were hired more than 15 years ago\n"; //print query instructions
        std::cout << std::left // Print table header -- use setw to from the iomanip library to give each row a defined width
                << std::setw(15) << "FacFirstName" //print all necessary column names to the console:
                << std::setw(15) << "FacLastName"
                << "\n";
        std::cout << std::string(100, '-') << "\n"; // Print separator line
        while (res->next()) { // Print rows
            std::cout << std::left //use std::left to put the text on the left side of the setw
                    << std::setw(15) << res->getString("FacFirstName") //print all necesary column entries to the console in order:
                    << std::setw(15) << res->getString("FacLastName")
                    << "\n";
        }
        delete res; //delete the response so it can be reassigned for the next query

        //4: Retrieve all course numbers from the Offering table that were offered in Summer 2020. 
        res = stmt->executeQuery("SELECT CourseNo FROM Offering7 WHERE OffTerm = 'SUMMER' AND OffYear = '2020'");

        std::cout << "\n4: Retrieve all course numbers from the Offering table that were offered in Summer 2020\n"; //print query instructions
        std::cout << std::left // Print table header -- use setw to from the iomanip library to give each row a defined width
                << std::setw(15) << "CourseNo" //print all necessary column names to the console:
                << "\n";
        std::cout << std::string(100, '-') << "\n"; // Print separator line
        while (res->next()) { // Print rows
            std::cout << std::left //use std::left to put the text on the left side of the setw
                    << std::setw(15) << res->getString("CourseNo") //print all necesary column entries to the console in order:
                    << "\n";
        }
        delete res; //delete the response so it can be reassigned for the next query

        //5: List the first and last names of all professors from the Faculty table who live in ZIP code 98114
        res = stmt->executeQuery("SELECT FacFirstName, FacLastName FROM Faculty7 WHERE FacZipCode LIKE '98114%'");

        std::cout << "\n5: List names of all faculty who live in zip code 98114\n"; //print query instructions
        std::cout << std::left // Print table header -- use setw to from the iomanip library to give each row a defined width
                << std::setw(15) << "FacFirstName" //print all necessary column names to the console:
                << std::setw(15) << "FacLastName"
                << "\n";
        std::cout << std::string(100, '-') << "\n"; // Print separator line
        while (res->next()) { // Print rows
            std::cout << std::left //use std::left to put the text on the left side of the setw
                    << std::setw(15) << res->getString("FacFirstName") //print all necesary column entries to the console in order:
                    << std::setw(15) << res->getString("FacLastName")
                    << "\n";
        }
        delete res; //delete the response so it can be reassigned for the next query

        //6 Retrieve the second-highest GPA from the Student table
        res = stmt->executeQuery("SELECT StdGPA FROM Student7 ORDER BY StdGPA DESC LIMIT 1 OFFSET 1"); //orders in descending order, limits output to 1, and chooses the second item (offset 1)

        std::cout << "\n6: Retrieve the second-highest GPA from the Student table\n"; //print query instructions
        std::cout << std::left // Print table header -- use setw to from the iomanip library to give each row a defined width
                << std::setw(15) << "StdGPA" //print all necessary column names to the console:
                << "\n";
        std::cout << std::string(100, '-') << "\n"; // Print separator line
        while (res->next()) { // Print rows
            std::cout << std::left //use std::left to put the text on the left side of the setw
                    << std::setw(15) << res->getString("StdGPA") //print all necesary column entries to the console in order:
                    << "\n";
        }
        delete res; //delete the response so it can be reassigned for the next query

        //7 Retrieve the first and last names of individuals who appear in both the Student and Faculty tables.
        res = stmt->executeQuery("SELECT DISTINCT S.StdFirstName AS FirstName, S.StdLastName AS LastName FROM Student7 AS S INNER JOIN Faculty7 AS F ON S.StdFirstName = F.FacFirstName AND S.StdLastName = F.FACLastName ");

        std::cout << "\n7: List names individuals who appear in both the Student and Faculty tables\n"; //print query instructions
        std::cout << std::left // Print table header -- use setw to from the iomanip library to give each row a defined width
                << std::setw(15) << "FirstName" //print all necessary column names to the console:
                << std::setw(15) << "LastName"
                << "\n";
        std::cout << std::string(100, '-') << "\n"; // Print separator line
        while (res->next()) { // Print rows
            std::cout << std::left //use std::left to put the text on the left side of the setw
                    << std::setw(15) << res->getString("FirstName") //print all necesary column entries to the console in order:
                    << std::setw(15) << res->getString("LastName")
                    << "\n";
        }
        delete res; //delete the response so it can be reassigned for the next query

        //8 Retrieve the student number, first and last names, and the number of selected courses from the Student and Enrollment tables
        res = stmt->executeQuery("SELECT S.StdNo, S.StdFirstName, S.StdLastName, COUNT(E.StdNo) AS SelectedCourses FROM Student7 AS S INNER JOIN Enrollment7 AS E ON S.StdNo = E.StdNo GROUP BY S.StdNo, S.StdFirstName, S.StdLastName");
        //Need GROUP BY to require SQL to combine all enrollment rows that belong to a single student

        std::cout << "\n8: Retrieve the student number, first and last names, and the number of selected courses from the Student and Enrollment tables\n"; //print query instructions
        std::cout << std::left // Print table header -- use setw to from the iomanip library to give each row a defined width
                << std::setw(15) << "StdNo" //print all necessary column names to the console:
                << std::setw(15) << "StdFirstName"
                << std::setw(15) << "StdLastName"
                << std:: setw(15) << "SelectedCourses"
                << "\n";
        std::cout << std::string(100, '-') << "\n"; // Print separator line
        while (res->next()) { // Print rows
            std::cout << std::left //use std::left to put the text on the left side of the setw
                    << std::setw(15) << res->getString("StdNo") //print all necesary column entries to the console in order:
                    << std::setw(15) << res->getString("StdFirstName")
                    << std::setw(15) << res->getString("StdLastName")
                    << std::setw(15) << res->getString("SelectedCourses")
                    << "\n";
        }
        delete res; //delete the response so it can be reassigned for the next query

        //9 Retrieve the first and last names of professors, along with their salaries for the top three highest-paid professors from the Faculty table.
        res = stmt->executeQuery("SELECT FacFirstName, FacLastName, FacSalary FROM Faculty7 ORDER BY FacSalary DESC LIMIT 3");
        
        std::cout << "\n9: Retrieve the first and last names of professors, along with their salaries for the top three highest-paid professors from the Faculty table\n"; //print query instructions
        std::cout << std::left // Print table header -- use setw to from the iomanip library to give each row a defined width
                << std::setw(15) << "FacFirstName" //print all necessary column names to the console:
                << std::setw(15) << "FacLastName"
                << std:: setw(15) << "FacSalary"
                << "\n";
        std::cout << std::string(100, '-') << "\n"; // Print separator line
        while (res->next()) { // Print rows
            std::cout << std::left //use std::left to put the text on the left side of the setw
                    << std::setw(15) << res->getString("FacFirstName") //print all necesary column entries to the console in order:
                    << std::setw(15) << res->getString("FacLastName")
                    << std::setw(15) << res->getString("FacSalary")
                    << "\n";
        }
        delete res; //delete the response so it can be reassigned for the next query

        //10 Retrieve all student information from the Student table for students who do not have any enrollment records in the Enrollment table
        res = stmt->executeQuery("SELECT S.* FROM Student7 AS S LEFT JOIN Enrollment7 AS E ON S.StdNo = E.StdNo WHERE E.StdNo IS NULL");

        std::cout << "\n10: Retrieve all student information from the Student table for students who do not have any enrollment records in the Enrollment table\n"; //print query instructions
        std::cout << std::left // Print table header -- use setw to from the iomanip library to give each row a defined width
                << std::setw(15) << "StdNo" //print all necessary column names to the console:
                << std::setw(15) << "FirstName"
                << std::setw(15) << "LastName"
                << std::setw(15) << "City"
                << std::setw(8)  << "State"
                << std::setw(8)  << "Major"
                << std::setw(8)  << "Class"
                << std::setw(6)  << "GPA"
                << std::setw(10) << "Zip"
                << "\n";
        std::cout << std::string(100, '-') << "\n"; // Print separator line
        while (res->next()) { // Print rows 
            std::cout << std::left //use std::left to put the text on the left side of the setw
                    << std::setw(15) << res->getString("StdNo") //print all necesary column entries to the console in order:
                    << std::setw(15) << res->getString("StdFirstName")
                    << std::setw(15) << res->getString("StdLastName")
                    << std::setw(15) << res->getString("StdCity")
                    << std::setw(8)  << res->getString("StdState")
                    << std::setw(8)  << res->getString("StdMajor")
                    << std::setw(8)  << res->getString("StdClass")
                    << std::setw(6)  << res->getString("StdGPA")
                    << std::setw(10) << res->getString("StdZip")
                    << "\n";
        }
        delete res; //delete the response so it can be reassigned for the next query

        //11 Insert a junior CS student named Alice Smith from Topeka, Kansas (ZIP 66610), with student number 888-88-8888 and a GPA of 3.85 into the Student table. Then display the updated table using SELECT * FROM Student.
        stmt->executeUpdate("INSERT INTO Student7 VALUES('888-88-8888','ALICE', 'SMITH', 'TOPEKA', 'KS', '66610', 'CS', 'JR', 3.85)");
        res = stmt->executeQuery("SELECT * FROM Student7");

        std::cout << "\n11: Inserted Alice Smith and updated table\n"; //print query instructions
        std::cout << std::left // Print table header -- use setw to from the iomanip library to give each row a defined width
                << std::setw(15) << "StdNo" //print all necessary column names to the console:
                << std::setw(15) << "FirstName"
                << std::setw(15) << "LastName"
                << std::setw(15) << "City"
                << std::setw(8)  << "State"
                << std::setw(8)  << "Major"
                << std::setw(8)  << "Class"
                << std::setw(6)  << "GPA"
                << std::setw(10) << "Zip"
                << "\n";
        std::cout << std::string(100, '-') << "\n"; // Print separator line
        while (res->next()) { // Print rows
            std::cout << std::left //use std::left to put the text on the left side of the setw
                    << std::setw(15) << res->getString("StdNo") //print all necesary column entries to the console in order:
                    << std::setw(15) << res->getString("StdFirstName")
                    << std::setw(15) << res->getString("StdLastName")
                    << std::setw(15) << res->getString("StdCity")
                    << std::setw(8)  << res->getString("StdState")
                    << std::setw(8)  << res->getString("StdMajor")
                    << std::setw(8)  << res->getString("StdClass")
                    << std::setw(6)  << res->getString("StdGPA")
                    << std::setw(10) << res->getString("StdZip")
                    << "\n";
        }
        delete res; //delete the response so it can be reassigned for the next query

        //12 Student Bob Norbert has moved to Overland Park, Kansas. Update the StdCity and StdZip fields in the Student table to reflect this change, and then display the updated table using SELECT * FROM Student.
        stmt->executeUpdate("UPDATE Student7 SET StdCity = 'OVERLAND PARK', StdState = 'KS' WHERE StdNo = '124-56-7890'");

        res = stmt->executeQuery("SELECT * FROM Student7");

        std::cout << "\n12: Update Bob Norbert's City and State and then show all student data\n"; //print query instructions
        std::cout << std::left // Print table header -- use setw to from the iomanip library to give each row a defined width
                << std::setw(15) << "StdNo" //print all necessary column names to the console:
                << std::setw(15) << "FirstName"
                << std::setw(15) << "LastName"
                << std::setw(15) << "City"
                << std::setw(8)  << "State"
                << std::setw(8)  << "Major"
                << std::setw(8)  << "Class"
                << std::setw(6)  << "GPA"
                << std::setw(10) << "Zip"
                << "\n";
        std::cout << std::string(100, '-') << "\n"; // Print separator line
        while (res->next()) { // Print rows
            std::cout << std::left //use std::left to put the text on the left side of the setw
                    << std::setw(15) << res->getString("StdNo") //print all necesary column entries to the console in order:
                    << std::setw(15) << res->getString("StdFirstName")
                    << std::setw(15) << res->getString("StdLastName")
                    << std::setw(15) << res->getString("StdCity")
                    << std::setw(8)  << res->getString("StdState")
                    << std::setw(8)  << res->getString("StdMajor")
                    << std::setw(8)  << res->getString("StdClass")
                    << std::setw(6)  << res->getString("StdGPA")
                    << std::setw(10) << res->getString("StdZip")
                    << "\n";
        }
        delete res; //delete the response so it can be reassigned for the next query

        delete stmt; //delete the statement once all queries are done
        delete con; //delete the connection pointer once the queries are done

    } catch (sql::SQLException& e) { //if there was some error connecting to mySQL or running the query
        std::cerr << e.what() << std::endl; //print out the error
    }

    return 0; //end main function
}
