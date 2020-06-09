#include <iostream>
#include <unordered_map>
#include <memory>

class User;
class Book;
class OnlineBookReaderSystem;
class UserManager;
class Library;
class Display;

class OnlineBookReaderSystem {
    public:
        std::shared_ptr<Library> get_library() const {
            return library;
        }
        std::shared_ptr<Display> get_display() const {
            return display;
        }
        std::shared_ptr<UserManager> get_user_manager() const {
            return user_manager;
        }
        std::shared_ptr<Book> get_active_book() const {
            return active_book;
        }
        std::shared_ptr<User> get_active_user() const {
            return active_user;
        }
        bool is_book_finished();
        void set_active_book(std::shared_ptr<Book>);
        void set_active_user(std::shared_ptr<User>);
    private:
        std::shared_ptr<Library> library;
        std::shared_ptr<UserManager> user_manager;
        std::shared_ptr<Display> display = std::make_shared<Display>();
        std::shared_ptr<Book> active_book;
        std::shared_ptr<User> active_user;
};

class User {
    public:
        User() = default;
        User(int i, int type) : id(i), account_type(type) {}
        int get_id() {
            return id;
        }
        void renew_membership(int type) { // renew membership - user can change account type
            account_type = type;
        }
        void set_id(int i) {
            id = i;
        }
        int get_account_type() {
            return account_type;
        }
        void set_account_type(int type) {
            account_type = type;
        }
    private:
        int id;
        int account_type;
};

class Book {
    public:
        Book() = default;
        Book(int id, int pages) : book_id(id), num_of_pages(pages) {}
        int get_id() {
            return book_id;
        }
        void set_id(int i) {
            book_id = i;
        }
        int number_of_pages() {
            return num_of_pages;
        }
    private:
        int book_id;
        int num_of_pages;
};

class Library {
    public:
        bool add_book(int id, int num_of_pages) {
            if(books.find(id) != books.end()) { // books constains given id
                return false; 
            }
            books[id] = Book(id, num_of_pages);
            return true;
        }
        bool remove_book(Book b) {
            return books.erase(b.get_id()); // erase returns 1 if element with given key exists, otherwise 0
        }
        bool remove_book(int id) {
            return books.erase(id);
        }
        Book get_book(int id) {
            return books[id];
        }
    private:
        std::unordered_map<int, Book> books;

};

class Display {
    public:
        void display_user(std::shared_ptr<User> user) {
            active_user = user;
            refresh_username();
        }
        void display_book(std::shared_ptr<Book> book) {
            page_number = 0;
            active_book = book;
            refresh_title();
            refresh_page();
        }
        void turn_page_backward() {
            std::cout << "Turn page backward: ";
            if(page_number <= 0) {
                page_number = -1;
                std::cout << "Book is closed\n";
                return;
            }
            page_number--;
            refresh_page();
        }
        void turn_page_forward() {
            std::cout << "Turn page forward: ";
            if(active_book -> number_of_pages() <= page_number) {
                std::cout << "Book is finished\n";
                return;
            }
            page_number++;
            refresh_page();
        }
        bool book_read() {
            return page_number >= (active_book -> number_of_pages());
        }
    private:
        int page_number = 0;
        std::shared_ptr<Book> active_book;
        std::shared_ptr<User> active_user;
        void refresh_username() {
            std::cout << "active user id = " << active_user -> get_id() << '\n';
        }
        void refresh_title() {
            std::cout << "active book id = " << active_book -> get_id() << '\n';
        }
        void refresh_page() {
            std::cout << "current page = " << page_number << '\n';
        }
};

class UserManager {
    public:
        bool add_user(int id, int account_type) {
            if(users.find(id) != users.end()) { // books constains given id
                return false; 
            }
            users[id] = User(id, account_type);
            return true;
        }
        bool remove_user(User user) {
            return remove_user(user.get_id());
        }
        bool remove_user(int id) {
            return users.erase(id);
        }
    private:
        std::unordered_map<int, User> users;
};

void OnlineBookReaderSystem::set_active_book(std::shared_ptr<Book> book) {
    active_book = book;
    display -> display_book(book);
}

void OnlineBookReaderSystem::set_active_user(std::shared_ptr<User> user) {
    active_user = user;
    display -> display_user(user);
}

bool OnlineBookReaderSystem::is_book_finished() {
    return display -> book_read(); 
}

void simulate_online_reader_system() {
    OnlineBookReaderSystem online_book_reader;
    online_book_reader.set_active_user(std::make_shared<User>(123, 1));
    online_book_reader.set_active_book(std::make_shared<Book>(456, 10));
    online_book_reader.get_display() -> turn_page_backward();
    while (!online_book_reader.is_book_finished())
    {
        online_book_reader.get_display() -> turn_page_forward();
    }   
    online_book_reader.get_display() -> turn_page_forward();
}

/**
 * Design the data structures for an online book reader system.
 * ASSUMPTIONS:
 * -user membership creation and extension
 * -reading a book
 * -only one active user at a time
 * -only one active book by this user
 */
int main() {
    std::cout << "==================\n"
                 "Online Book Reader\n"
                 "==================\n";
    simulate_online_reader_system();
}