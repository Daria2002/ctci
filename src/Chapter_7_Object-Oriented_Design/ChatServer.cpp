#include <iostream>
#include <unordered_map>
#include <memory>
#include <mysql-cppconn-8/jdbc/mysql_driver.h>
#include <mysql-cppconn-8/jdbc/cppconn/statement.h>
#include <ctime>
#include <vector>
#include <algorithm>

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

class UserStatus {
    public:
        UserStatus() = default;
        UserStatus(UserStatusType t, std::string mess) : type(t), message(mess) {}
        std::string message;
        UserStatusType type;
};

// singleton
class UserManager {
    public:
        static UserManager& get_instance() {
            static UserManager instance;
            return instance;
        }
        // send friendship request
        void add_user(std::shared_ptr<User> from_user, std::string to_account_name);
        void approve_add_request(std::shared_ptr<Request>);
        void reject_add_request(std::shared_ptr<Request>);
        void user_signed_on(std::string);
        void user_signed_off(std::string);
    private:
        std::unordered_map<int, std::shared_ptr<User>> users_by_id; // maps from id to user
        std::unordered_map<std::string, std::shared_ptr<User>> users_by_account_name;
        std::unordered_map<int, std::shared_ptr<User>> online_users; // maps from id to online user
};

class Request {
    public:
        Request(std::shared_ptr<User> f_user, std::shared_ptr<User> t_user, std::time_t t) : 
        from_user(f_user), to_user(t_user), time(t) {}
        std::shared_ptr<User> get_from_user() {
            return from_user;
        }   
        std::shared_ptr<User> get_to_user() {
            return to_user;
        }
        RequestStatus status;
    private:
        std::shared_ptr<User> from_user;
        std::shared_ptr<User> to_user;
        std::time_t time;
};

class Message {

};

class Conversation {
    protected:
        std::vector<std::shared_ptr<User>> participants;
        int id;
        std::vector<std::shared_ptr<Message>> messages;
    public:
        std::vector<std::shared_ptr<Message>> get_messages() {
            return messages;
        }
        bool add_message(std::shared_ptr<Message> mess) {
            messages.push_back(mess);
            return true;
        }
        int get_id() {
            return id;
        }
};

class PrivateChat : public Conversation {

};

class GroupChat : public Conversation {
    public:
        void remove_participant(std::shared_ptr<User> user) {
            std::remove(participants.begin(), participants.end(), user);
        }
        void add_participant(std::shared_ptr<User> user) {
            participants.push_back(user);
        }
};

class User : std::enable_shared_from_this<User> {
    public:
        User(int i, std::string account, std::string name) : id(i), account_name(account), full_name(name) {
            status = UserStatus();
        }
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
        bool add_contact(std::shared_ptr<User> new_contact) {
            if(contacts.find(new_contact -> get_id()) != contacts.end()) {
                contacts[new_contact -> get_id()] = new_contact;
                return true;
            }
            return false;
        }
        void request_add_user(std::string account_name) {
            UserManager::get_instance().add_user(shared_from_this(), account_name);
        }
        void remove_add_req(std::shared_ptr<Request> req) {
            if(req -> get_to_user() == shared_from_this()) {
                received_add_req.erase(req -> get_from_user() -> get_id());
            } else if(req -> get_from_user() == shared_from_this()) {
                sent_add_req.erase(req -> get_to_user() -> get_id());
            }
        }
        std::string get_account_name() {
            return account_name;
        }
        std::string get_full_name() {
            return full_name;
        }
        int get_id() {
            return id;
        }
        void add_conversation(std::shared_ptr<PrivateChat>);
        void add_conversation(std::shared_ptr<GroupChat>);
        UserStatus status;
    private:
        std::string account_name;
        std::string full_name;
        int id;
        std::unordered_map<int, std::shared_ptr<PrivateChat>> private_chats;
        std::vector<std::shared_ptr<GroupChat>> group_chats;
        std::unordered_map<int, std::shared_ptr<User>> contacts;
        std::unordered_map<int, std::shared_ptr<Request>> received_add_req;
        std::unordered_map<int, std::shared_ptr<Request>> sent_add_req;
};

// send friendship request
void UserManager::add_user(std::shared_ptr<User> from_user, std::string to_account_name) {
    std::shared_ptr<User> to_user = users_by_account_name[to_account_name];
    std::shared_ptr<Request> req = std::make_shared<Request>(from_user, to_user, time(0));
    to_user -> received_add_request(req);
    from_user -> sent_add_request(req);
}
void UserManager::approve_add_request(std::shared_ptr<Request> request) {
    request -> status = RequestStatus::Accepted;
    std::shared_ptr<User> from = request -> get_from_user();
    std::shared_ptr<User> to = request -> get_to_user();
    from -> add_contact(to);
    to -> add_contact(from);
}
void UserManager::reject_add_request(std::shared_ptr<Request> request) {
    request -> status = RequestStatus::Rejected;
    std::shared_ptr<User> from = request -> get_from_user();
    std::shared_ptr<User> to = request -> get_to_user();
    from -> remove_add_req(request);
    to -> remove_add_req(request);
}
void UserManager::user_signed_on(std::string account_name) {
    if(users_by_account_name.find(account_name) != users_by_account_name.end()) {
        std::shared_ptr<User> user = users_by_account_name[account_name];
        user -> status = UserStatus(UserStatusType::Available, "");
        online_users[user -> get_id()] = user;
    }
}
void UserManager::user_signed_off(std::string  account_name) {
    if(users_by_account_name.find(account_name) != users_by_account_name.end()) {
        std::shared_ptr<User> user = users_by_account_name[account_name];
        user -> status = UserStatus(UserStatusType::Offline, "");
        online_users.erase(user -> get_id());
    }
}
void User::add_conversation(std::shared_ptr<PrivateChat> conversation) {
    // todo
}
void User::add_conversation(std::shared_ptr<GroupChat> conversation) {
    // todo
}

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