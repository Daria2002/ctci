#include <iostream>
#include <unordered_map>
#include <memory>
#include <mysql-cppconn-8/jdbc/mysql_driver.h>
#include <mysql-cppconn-8/jdbc/cppconn/statement.h>
#include <ctime>

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
            std::shared_ptr<User> to_user = users_by_account_name[to_account_name];
            std::shared_ptr<Request> req = std::make_shared<Request>(from_user, to_user, time(0));
            to_user -> received_add_request(req);
            from_user -> sent_add_request(req);
        }
        void approve_add_request(std::shared_ptr<Request> request) {
            request -> status = RequestStatus::Accepted;
            std::shared_ptr<User> from = request -> get_from_user();
            std::shared_ptr<User> to = request -> get_to_user();
            from -> add_contact(to);
            to -> add_contact(from);
        }
        void reject_add_request(std::shared_ptr<Request> request) {
            request -> status = RequestStatus::Rejected;
            std::shared_ptr<User> from = request -> get_from_user();
            std::shared_ptr<User> to = request -> get_to_user();
            from -> remove_add_req(to);
            to -> remove_add_req(from);
        }
        void user_signed_on(std::string account_name) {
            if(users_by_account_name.find(account_name) != users_by_account_name.end()) {
                std::shared_ptr<User> user = users_by_account_name[account_name];
                // continue..
            }
        }
        void user_signed_off(std::string  account_name) {

        }
    private:
        std::unordered_map<int, std::shared_ptr<User>> users_by_id; // maps from id to user
        std::unordered_map<std::string, std::shared_ptr<User>> users_by_account_name;
        std::unordered_map<int, std::shared_ptr<User>> online_user; // maps from id to online user
};

class Request {
    public:
        Request(std::shared_ptr<User> f_user, std::shared_ptr<User> t_user, std::time_t t) : 
        from_user(f_user), to_user(t_user), time(t) {}
        std::shared_ptr<User> get_from_user() {
            return from_user;
        }   
        std::shared_ptr<User> get_to_user() {
            get_to_user;
        }
        RequestStatus status;
    private:
        std::shared_ptr<User> from_user;
        std::shared_ptr<User> to_user;
        std::time_t time;
};

class User {
    public:
        void received_add_request(std::shared_ptr<Request> req) {
            int sender_id = req -> get_from_user() -> get_id();
            if(received_add_req.find(sender_id) == received_add_req.end()) {
                received_add_req[sender_id] = req;
            }
        }
        void sent_add_request(std::shared_ptr<Request> req) {
            int receiver_id = req -> get_to_user() -> get_id();
            if(sent_add_req.find(receiver_id) == sent_add_req.end()) {
                sent_add_req[receiver_id] = req;
            }
        }
        int get_id() {
            return id;
        }
        void add_contact(std::shared_ptr<User> new_contact) {

        }
        void remove_add_req(std::shared_ptr<User> new_contact) {
            
        }
    private:
        int id;
        UserStatusType status;
        std::unordered_map<int, std::shared_ptr<Request>> received_add_req;
        std::unordered_map<int, std::shared_ptr<Request>> sent_add_req;
};

void test_private_chat() {
    //TODO
}

void test_group_chat() {

}

/**
 * Explain how you would design a chat server. In particular, provide details about the various
 * backend components, classes, and methods. What would be the hardest problems to solve?
 */
int main() {
    std::cout << "===========\nChat Server\n===========\n";
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
    test_private_chat();
    test_group_chat();
}

/**
 * example for db
 * g++ -I/usr/include -I/usr/include/mysql-cppconn-8 test_db.cpp -lmysqlcppconn -o app 
 * "/usr/include/mysql-cppconn-8"
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