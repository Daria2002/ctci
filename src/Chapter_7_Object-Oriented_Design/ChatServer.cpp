#include <iostream>
#include <unordered_map>
#include <memory>
#include <string>
#include <mysql-cppconn-8/jdbc/mysql_driver.h>
#include <mysql-cppconn-8/jdbc/cppconn/statement.h>
#include <mysql-cppconn-8/jdbc/cppconn/prepared_statement.h>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>

// singleton for sql connection
class DBConnection {
    public:
        static sql::Connection* get_instance() {
            static sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();
            static sql::Connection* con = driver->connect("tcp://127.0.0.1:3306", "daria", "5555");
            return con;
        }
};

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

void sleepcp(int milliseconds) // Cross-platform sleep function
{
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end)
    {
    }
}

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
        from_user(f_user), to_user(t_user), time(t) {
            status = RequestStatus::Unread;
        }
        std::shared_ptr<User> get_from_user() const {
            return from_user;
        }   
        std::shared_ptr<User> get_to_user() const {
            return to_user;
        }
        std::time_t time;
        RequestStatus status;
    private:
        std::shared_ptr<User> from_user;
        std::shared_ptr<User> to_user;
};

class Message {
    public:
        std::string content;
        std::time_t time;
        Message(std::string c) : content(c) {
            time = std::time(0);
        }
        Message(std::string c, std::time_t t) : content(c), time(t) {}
};

std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Message>& mess) {
    os << "==============\nTIME : " << mess -> time << '\n' << mess -> content << '\n';
    return os;
}

class Conversation {
    protected:
        int id;
        std::vector<std::shared_ptr<Message>> messages;
    public:
        Conversation() {
            id = object_order;
            object_order++;
        }
        std::vector<std::shared_ptr<User>> participants;
        std::vector<std::shared_ptr<Message>> get_messages() const {
            return messages;
        }
        bool add_message(std::shared_ptr<Message> mess) {
            sql::PreparedStatement *pstmt = DBConnection::get_instance() -> prepareStatement("INSERT INTO ChatServer(message, group_id) VALUES (?, ?)");
            pstmt -> setString(1, mess -> content);
            pstmt -> setInt(2, id);
            pstmt -> execute();
            messages.push_back(mess);
            return true;
        }
        int get_id() const {
            return id;
        }
        static int object_order;
};

int Conversation::object_order = 0;

class PrivateChat : public Conversation {
    public:
        PrivateChat(std::shared_ptr<User> user1, std::shared_ptr<User> user2) : Conversation() {
            participants.push_back(user1);
            participants.push_back(user2);
        }
        bool get_other_participant(std::shared_ptr<User> primary, std::shared_ptr<User>& other) const {
            if(participants[0] == primary) {
                other = participants[1];
            } else if(participants[1] == primary) {
                other = participants[0];
            } else {
                return false;
            }
            return true;
        }
};

class GroupChat : public Conversation {
    public:
        GroupChat() : Conversation() {}
        void remove_participant(std::shared_ptr<User> user) {
            std::remove(participants.begin(), participants.end(), user);
        }
        void add_participant(std::shared_ptr<User> user) {
            participants.push_back(user);
        }
};

class User : public std::enable_shared_from_this<User> {
    public:
        User() = default;
        User(int i, std::string account, std::string name) : id(i), account_name(account), full_name(name) {
            status = UserStatus();
        }
        void received_add_request(std::shared_ptr<Request> req) {
            int sender_id = req -> get_from_user() -> id;
            if(received_add_req.find(sender_id) == received_add_req.end()) {
                received_add_req.insert(std::make_pair(sender_id, req));
            }
        }
        void sent_add_request(std::shared_ptr<Request> req) {
            int receiver_id = req -> get_to_user() -> id;
            if(sent_add_req.find(receiver_id) == sent_add_req.end()) {
                sent_add_req.insert(std::make_pair(receiver_id, req));
            }
        }
        bool add_contact(std::shared_ptr<User> new_contact) {
            if(contacts.find(new_contact -> id) != contacts.end()) {
                contacts.insert(std::make_pair(new_contact -> id, new_contact));
                return true;
            }
            return false;
        }
        void request_add_user(std::string account_name) {
            UserManager::get_instance().add_user(shared_from_this(), account_name);
        }
        void remove_add_req(std::shared_ptr<Request> req) {
            if(req -> get_to_user() == shared_from_this()) {
                received_add_req.erase(req -> get_from_user() -> id);
            } else if(req -> get_from_user() == shared_from_this()) {
                sent_add_req.erase(req -> get_to_user() -> id);
            }
        }
        std::string get_account_name() const {
            return account_name;
        }
        std::string get_full_name() const {
            return full_name;
        }
        void add_conversation(std::shared_ptr<PrivateChat>);
        void add_conversation(std::shared_ptr<GroupChat>);
        int id;
        UserStatus status;
    private:
        std::string account_name;
        std::string full_name;
        std::unordered_map<int, std::shared_ptr<PrivateChat>> private_chats;
        std::vector<std::shared_ptr<GroupChat>> group_chats;
        std::unordered_map<int, std::shared_ptr<User>> contacts;
        std::unordered_map<int, std::shared_ptr<Request>> received_add_req;
        std::unordered_map<int, std::shared_ptr<Request>> sent_add_req;
};

std::ostream& operator<<(std::ostream& os, const std::shared_ptr<User>& user) {
    os << user -> get_account_name();
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::shared_ptr<PrivateChat>& private_chat) {
    os << "********Conversation between " << private_chat -> participants[0] << 
    " and " << private_chat -> participants[1] << "********\n";
    std::vector<std::shared_ptr<Message>> messages = private_chat -> get_messages();
    for(std::shared_ptr<Message> message : messages) {
        os << message;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::shared_ptr<GroupChat>& group_chat) {
    os << "********Conversation between ";
    for(std::shared_ptr<User> participant : group_chat -> participants) {
        os << participant << ", ";
    }
    os << "********\n";
    std::vector<std::shared_ptr<Message>> messages = group_chat -> get_messages();
    for(std::shared_ptr<Message> message : messages) {
        os << message;
    }
    return os;
}

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
        online_users.insert(std::make_pair(user -> id, user));
    }
}
void UserManager::user_signed_off(std::string  account_name) {
    if(users_by_account_name.find(account_name) != users_by_account_name.end()) {
        std::shared_ptr<User> user = users_by_account_name[account_name];
        user -> status = UserStatus(UserStatusType::Offline, "");
        online_users.erase(user -> id);
    }
}
void User::add_conversation(std::shared_ptr<PrivateChat> conversation) {
    std::shared_ptr<User> other_user;
    if(conversation -> get_other_participant(shared_from_this(), other_user)) {
        private_chats.insert(std::make_pair(other_user -> id, conversation));
    }
}
void User::add_conversation(std::shared_ptr<GroupChat> conversation) {
    group_chats.push_back(conversation);
}

void simulation() {
    // create 4 users
    std::shared_ptr<User> user1 = std::make_shared<User>(1, "one", "one o");
    std::shared_ptr<User> user2 = std::make_shared<User>(2, "two", "two t");
    std::shared_ptr<User> user3 = std::make_shared<User>(3, "three", "three t");
    std::shared_ptr<User> user4 = std::make_shared<User>(4, "four", "four f");
    // private chat between user1 and user 2 and between user 2 and user 4
    std::shared_ptr<PrivateChat> private_chat12 = std::make_shared<PrivateChat>(user1, user2);
    user1 -> add_conversation(private_chat12);
    user2 -> add_conversation(private_chat12);
    private_chat12 -> add_message(std::make_shared<Message>("hello"));
    sleepcp(1000);
    private_chat12 -> add_message(std::make_shared<Message>("hello, how are you?"));
    std::cout << private_chat12 << '\n';
    // group chat between all users and between everyone except one
    std::shared_ptr<GroupChat> group_chat_all = std::make_shared<GroupChat>();
    group_chat_all -> add_participant(user1);
    group_chat_all -> add_participant(user2);
    group_chat_all -> add_participant(user3);
    group_chat_all -> add_participant(user4);
    user1 -> add_conversation(group_chat_all);
    user2 -> add_conversation(group_chat_all);
    user3 -> add_conversation(group_chat_all);
    user4 -> add_conversation(group_chat_all);
    group_chat_all -> add_message(std::make_shared<Message>("hello everyone in group chat"));
    sleepcp(2000);
    group_chat_all -> add_message(std::make_shared<Message>("how many participants are here?"));
    std::cout << group_chat_all << '\n';
}

/**
 * Explain how you would design a chat server. In particular, provide details about the various
 * backend components, classes, and methods. What would be the hardest problems to solve?
 */
int main() {
    std::cout << "===========\nChat Server\n===========\n";
    sql::Statement *stmt;
    sql::Connection *con = DBConnection::get_instance();
    if(con->isValid()) {
        std::cout << "Connection is valid\n";
    } else {
        std::cout << "Connection is invalid\n";
    }
    // create table
    stmt = con -> createStatement();
    stmt -> execute("USE ctci"); // ctci is db for ctci problems
    stmt->execute("DROP TABLE IF EXISTS ChatServer");
    stmt->execute("CREATE TABLE ChatServer(message varchar(1000), group_id INT)");

    simulation();
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

/** TODO with db
 * create table with columns: message, group id
*/