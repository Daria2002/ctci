#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>
#include <memory>
#include <algorithm>
#include <mysql-cppconn-8/jdbc/mysql_driver.h>
#include <mysql-cppconn-8/jdbc/cppconn/statement.h>
#include <mysql-cppconn-8/jdbc/cppconn/prepared_statement.h>
#include <mysql-cppconn-8/jdbc/cppconn/resultset.h>

class Entry;
class File;
class Directory;

// singleton for sql connection
class DBCOnnection {
    public:
        static sql::Connection* get_instance() {
            static sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
            static sql::Connection* con = driver -> connect("tcp://127.0.0.1:3306", "daria", "5555");
            return con;
        }
};

class Entry : std::enable_shared_from_this<Entry> {
    public:
        Entry(std::string n, std::shared_ptr<Directory> p) : name(n), parent(p) {
            created = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            last_accessed = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            last_updated = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        }
        std::string get_full_path();
        bool delete_entry();
        std::time_t created;
        std::time_t last_accessed;
        std::time_t last_updated;
        std::string name;
        std::shared_ptr<Directory> parent;
        int size;
        virtual int num_of_files() = 0;
};

class File : public Entry {
    public:
        File(std::string n, std::shared_ptr<Directory> p, int s) : Entry(n, p) {
            size = s;
        }
        std::string get_content() {
            sql::PreparedStatement *pstmt = DBCOnnection::get_instance() -> prepareStatement("SELECT * FROM FileSystem WHERE file_path = ?");
            pstmt -> setString(1, get_full_path());
            pstmt -> execute();
            sql::ResultSet* res = pstmt -> getResultSet();
            while (res != nullptr && res -> next())
            {
                return res -> getString("file_content");
            }
            return "";
        }
        void set_content(std::string c) {
            sql::PreparedStatement *pstmt = DBCOnnection::get_instance() -> prepareStatement("INSERT INTO FileSystem(file_path, file_content) VALUES (?, ?)");
            pstmt -> setString(1, get_full_path());
            pstmt -> setString(2, c);
            pstmt -> execute();
        }
        int num_of_files() {
            return 0;
        }
};

class Directory : public Entry {
    public:
        Directory(std::string n, std::shared_ptr<Directory> p) : Entry(n, p) {}
        int num_of_files();
        void delete_entry(std::shared_ptr<Entry> entry) {
            std::remove(contents.begin(), contents.end(), entry);
        }
        std::size_t get_size() {
            std::size_t s;
            for(auto content : contents) {
                s += content -> size;
            }
            return s;
        }
        std::vector<std::shared_ptr<Entry>> contents;
};

bool Entry::delete_entry() {
    if(parent == nullptr) return false;
    parent -> delete_entry(shared_from_this());
    return true;
}

std::string Entry::get_full_path() {
    if(parent == nullptr) return name;
    std::string path = ""; 
    path.append(parent -> get_full_path());
    path.append("//");
    path.append(name);
    return path;
}

int Directory::num_of_files() {
    int count = 0;
    for(auto e : contents) {
        if(typeid(e) == typeid(std::shared_ptr<Directory>)) {
            count++;
            count += e -> num_of_files();
        } else {
            count++;
        }
    }
    return count;
}

bool set_database() {
    sql::Statement* stmt;
    sql::Connection *con = DBCOnnection::get_instance();
    if(con -> isValid()) {
        std::cout << "Connection is valid.\n";
    } else {
        std::cout << "Connection is not valid.\n";
        return false;
    }
    stmt = con -> createStatement();
    stmt -> execute("USE ctci");
    stmt -> execute("DROP TABLE IF EXISTS FileSystem");
    stmt -> execute("CREATE TABLE FileSystem(file_path varchar(1000), file_content varchar(1000))");
    return true;
}

void simulation() {
    std::shared_ptr<Directory> root = std::make_shared<Directory>("root", nullptr);
    std::shared_ptr<File> one = std::make_shared<File>("one", root, 5);
    one -> set_content("This is the file number one, so it's name is one.");
    std::shared_ptr<File> two = std::make_shared<File>("two", root, 3);
    two -> set_content("This is the file number two, so it's name is two.");
    std::shared_ptr<File> three = std::make_shared<File>("three", root, 4);
    three -> set_content("This is the file number three, so it's name is three.");
    std::cout << "File one content:\n" << one -> get_content() << '\n';
    std::cout << "File two content:\n" << two -> get_content() << '\n';
    std::cout << "File three content:\n" << three -> get_content() << '\n';
}

/**
 * Explain the data structures and algorithms that you would use to design an in-memory
 * file system. Illustrate with an example in code where possible.
 */
int main() {
    std::cout << "===========\n"
                 "File system\n"
                 "===========\n";
    if(!set_database()) {
        std::cout << "Program finished due to the failed database connection.\n";
    }
    simulation();
}