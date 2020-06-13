#include <iostream>
#include <unordered_map>
#include <memory>

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