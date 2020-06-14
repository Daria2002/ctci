#include <iostream>
#include <unordered_map>
#include <memory>
// #include "jdbc/mysql_driver.h"
// #include "jdbc/cppconn/statement.h"

enum UserStatusType {
    Offline, Away, Idle, Available, Busy
};

enum RequestStatus {
    Unread, Read, Accepted, Rejected
};

class UserManager;
class User;
class Request;
class Conversation;
class GroupChat;
class PrivateChat;
class Message;
class UserStatus;
class System;

// singleton
class UserManager {
    public:
        static UserManager& get_instance() {
            static UserManager instance;
            return instance;
        }
        // send friendship request
        void add_user(std::shared_ptr<User> from_user, std::string to_account_name) {

        }
};

void test_private_chat() {

}

void test_group_chat() {

}

/**
 * Explain how you would design a chat server. In particular, provide details about the various
 * backend components, classes, and methods. What would be the hardest problems to solve?
 */
int main() {
    std::cout << "===========\nChat Server\n===========\n";
    test_private_chat();
    test_group_chat();
}

/**
 * example for db
int main()
{
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "daria", "5555");
    if(con->isValid()) {
        std::cout << "Connection is valid\n";
    } else {
        std::cout << "Connection is invalid\n";
    }

    stmt = con -> createStatement();
    stmt -> execute("USE my_test_db");
    stmt->execute("DROP TABLE IF EXISTS test");
    stmt->execute("CREATE TABLE test(id INT)");   
    stmt -> execute("INSERT INTO my_test_table(name, age) VALUES (\"daria\", 25)");
    
    delete stmt;
    delete con;
    return 0;
}
*/