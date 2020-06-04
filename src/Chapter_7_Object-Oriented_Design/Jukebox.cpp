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
        User(std::string name, std::string pass) : user_name(name), password(pass) {}
        bool check_password(const std::string& pass) {
            return pass == password;
        }
        std::string name() {
            return user_name;
        }
    private:
        std::string password;
        std::string user_name;
};

class Playlist;
class CD;
class Song;
class SetOfSongs;

class Jukebox {
    public:
        bool logged = false;
        User current_user;
        void login() {
            std::string name;
            std::cout << "** Login **\n";
            std::cout << "Enter name:\n";
            std::cin >> name;
            User user; 
            bool user_exists = get_user(name, user);
            if(user_exists) {
                std::cout << "Enter a password\n";
                std::string pass;
                std::cin >> pass;
                if(user.check_password(pass)) {
                    current_user = user;
                    std::cout << "Password correct. You are logged in.\n";
                    logged = true;
                } else {
                    std::cout << "Password is not correct.\n";
                }
                return;
            }
            std::cout << "User with username " << name << " doesn't exist\n";
        }
        void logout() {
            logged = false;
        }
        void sign_up() {
            std::string name;
            std::string pass;
            std::cout << "** Sign up ** \n";
            std::cout << "Enter name:\n";
            std::cin >> name;
            std::cout << "Enter password:\n";
            std::cin >> pass;
            User u(name, pass);
            users.push_back(u);
        }
        void add_cd(std::shared_ptr<CD> cd) {
            cds.push_back(cd);
        }
        void add_playlist(std::shared_ptr<Playlist> playlist) {
            playlists.push_back(playlist);
        }
        bool get_user(std::string name, User& user) {
            for(User& u : users) {
                if(u.name() == name) {
                    user = u;
                    return true;
                }
            }
            return false;
        }
        void play(std::shared_ptr<SetOfSongs>&&);
    private:
        std::vector<User> users;
        std::shared_ptr<CD> current_cd;
        std::vector<std::shared_ptr<CD>> cds;
        std::vector<std::shared_ptr<Playlist>> playlists;
};

class SetOfSongs {
    public:
        std::vector<std::shared_ptr<Song>> songs;
        std::string name;
        SetOfSongs(std::vector<std::shared_ptr<Song>> s, std::string n) : songs(s), name(n) {}
};

void Jukebox::play(std::shared_ptr<SetOfSongs>&& set) {
    std::cout << "Set " << set -> name << " is playing\n";
}

class Artist;

class CD : public SetOfSongs {
    public:
        CD(std::vector<std::shared_ptr<Song>> s, std::string n) : SetOfSongs(s, n) {}
        std::shared_ptr<Artist> artist;
};

class Song {
    public:
        Song(std::string n, std::shared_ptr<Artist> a) : name(n), artist(a) {}
        std::string name;
        std::shared_ptr<Artist> artist;
};

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

class Playlist : public SetOfSongs {
    public:
        Playlist(std::vector<std::shared_ptr<Song>> s, std::string n) : SetOfSongs(s, n) {}
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

    Jukebox jukebox;
    jukebox.sign_up();
    jukebox.login();
    jukebox.add_playlist(std::make_shared<Playlist>(p));
    std::shared_ptr<Playlist> playlist_ptr = std::make_shared<Playlist>(p);
    jukebox.play(playlist_ptr);
    jukebox.logout();
}
