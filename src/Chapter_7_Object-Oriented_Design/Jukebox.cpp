#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <random>

class User {
    public:
        User() = default;
        User(std::string name, int pass) : user_name(name), password(pass) {}
        bool check_password(const int pass) {
            return pass == password;
        }
        std::string name() {
            return user_name;
        }
    private:
        int password;
        std::string user_name;
};

class Playlist;
class CD;
class Song;

class Jukebox {
    public:
        std::vector<User> users;
        bool logged = false;
        User current_user;
        bool login() {
            std::string name;
            std::cout << "Enter name:\n";
            std::cin >> name;
            if(User user; get_user(name, user)) {
                std::cout << "Enter a password\n";
                int pass;
                std::cin >> pass;
                if(user.check_password(pass)) {
                    std::cout << "Password correct. You are logged in.\n";
                } else {
                    std::cout << "Password is not correct.\n";
                }
            } else {
                std::cout << "User with username " << name << "doesn't exist\n";
            }
            logged = true;
        }
        bool logout() {
            logged = false;
        }
        bool sign_up() {
            std::string name;
            int pass;
            std::cout << "Enter name:\n";
            std::cin >> name;
            std::cout << "Enter password:\n";
            std::cin >> pass;
            users.push_back(User(name, pass));
        }
        void play(std::shared_ptr<CD> cd) {

        }
        void play(std::shared_ptr<Playlist> playlist) {

        }
        void add_cd(std::shared_ptr<CD> cd) {
            cds.push_back(cd);
        }
    private:
        bool get_user(std::string name, User& user) {
            for(User& u : users) {
                if(u.name() == name) {
                    user = u;
                    return true;
                }
            }
            return false;
        }
        std::shared_ptr<CD> current_cd;
        std::vector<std::shared_ptr<CD>> cds;
};

class SongSet {
    public:
        std::vector<std::shared_ptr<Song>> songs;
        std::string name;
        SongSet(std::vector<std::shared_ptr<Song>> s, std::string n) : songs(s), name(n) {}
};

class Artist;

class CD : public SongSet {
    public:
        CD(std::vector<std::shared_ptr<Song>> s, std::string n) : SongSet(s, n) {}
        std::shared_ptr<Artist> artist;
};

class Song {
    public:
        Song(std::string n, std::shared_ptr<Artist> a) : name(n), artist(a) {}
        std::string name;
        std::shared_ptr<Artist> artist;
};

inline bool operator==(const Song& lhs, const Song& rhs){ return true; }

class Artist {
    public:
        Artist(std::string n) : name(n) {}
        void add_song(const Song& song) {
            songs.push_back(song);
        }
    private:
        std::string name;
        std::vector<Song> songs;
};

class Display {
    public:
};

class Playlist : public SongSet {
    public:
        Playlist(std::vector<std::shared_ptr<Song>> s, std::string n) : SongSet(s, n) {}
        void add_song(std::shared_ptr<Song> song) {
            songs.push_back(song);
        }
        void delete_song(const std::shared_ptr<Song>& song) {
            std::remove(songs.begin(), songs.end(), song);
        }
        void shuffle() {
            std::shuffle(songs.begin(), songs.end(), std::default_random_engine(time(0)));
        }
};

/**
 * Design a musical jukebox using object-oriented principles.
 * ASSUMPTIONS: The jukebox is a computer simulation. It's free.
 */
int main() {
    std::cout << "================================\n"
                 "Free of charge jukebox simulator\n"
                 "================================\n";
    std::vector<std::shared_ptr<Song>> pl;
    pl.push_back(std::make_shared<Song>("a", std::make_shared<Artist>("aa")));
    pl.push_back(std::make_shared<Song>("b", std::make_shared<Artist>("aa")));
    pl.push_back(std::make_shared<Song>("c", std::make_shared<Artist>("aa")));
    pl.push_back(std::make_shared<Song>("d", std::make_shared<Artist>("aa")));
    pl.push_back(std::make_shared<Song>("e", std::make_shared<Artist>("aa")));
    pl.push_back(std::make_shared<Song>("f", std::make_shared<Artist>("aa")));
    pl.push_back(std::make_shared<Song>("g", std::make_shared<Artist>("aa")));
    std::string str = "mix";
    Playlist p(pl, str);
    p.shuffle();
}
