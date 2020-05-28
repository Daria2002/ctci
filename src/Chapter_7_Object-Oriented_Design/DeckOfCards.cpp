#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <limits>

#define NUM_OF_CARDS 52
#define SHUFFLE_MOVES 50

enum class Suit {
    Club = 0, Diamond = 1, Heart = 2, Spade = 3
};

template <typename T>
class Deck {
    public:
        T deal_card() {
            dealt_index++;
            return cards[dealt_index];
        }
        void set_deck_of_cards(std::vector<T> deck_of_cards) {
            cards = deck_of_cards;
        }
        std::vector<T> deal_hand(int number) {
            std::vector<T> c;
            for(int i = 0; i < number; i++) {
                c.push_back(deal_card());
            }
            return c;
        }
        void shuffle() {
            srand(time(NULL));
            for(int i = 0; i < SHUFFLE_MOVES; i++) {
                int index1 = rand() % cards.size();
                int index2 = rand() % cards.size();
                T tmp = cards[index1];
                cards[index1] = cards[index2];
                cards[index2] = tmp;
            }
        }
        int number_of_remaining_cards() {
            return cards.size() - dealt_index;
        }
    private:
        std::vector<T> cards; // all cards (dealt and undealt)
        int dealt_index = 0; // marks first undealt index
};

class Card {
    protected:
        bool available = true;
        int face_value; // 11-Jack, 12-Queen, 13-King, 1-Ace, 2-10
        Suit suit;
    public:
        Card() = default;
        Card(int fv, Suit s) : face_value(fv), suit(s) {}
        virtual int value() = 0;
        Suit get_suit() {
            return suit;
        }
        bool is_available() {
            return available;
        }
        void mark_available() {
            available = true;
        }
        void mark_unavailable() {
            available = false;
        }
};

template <typename T>
class Hand {
    protected:
        std::vector<T> cards;
    public:
        int score() {
            int score = 0;
            for(T card : cards) {
                score += card.value();
            }
            return score;
        }
        void add_card(T card) {
            cards.push_back(card);
        }
};

class BlackJackCard : public Card {
    public:
        int face_value;
        Suit suit;
        BlackJackCard(int val, Suit s) : face_value(val), suit(s) {}
        BlackJackCard() = default;
        int value() {
            if(is_ace()) return 1;
            else if(is_free_card()) return 10;
            return face_value;
        }
    private:
        int min_val() {
            return value();
        }
        int max_val() {
            if(is_ace()) return 11;
            return value();
        }
        bool is_ace() {
            return face_value == 1;
        }
        bool is_free_card() {
            return face_value >= 11 && face_value <= 13;
        }
};

class BlackJackHand : public Hand<BlackJackCard> {
    public:
        int score() {
            std::vector<int> scores = possible_scores();
            int max = std::numeric_limits<int>::min();
            int min = std::numeric_limits<int>::max();
            for(int score : scores) {
                if(score > 21 && score < min) {
                    min = score;
                } else if(score <= 21 && score > max) {
                    max = score;
                }
            }
            return max == std::numeric_limits<int>::min() ? min : max;
        }
        bool busted() {
            return score() > 21;
        }
        bool is_21() {
            return score() == 21;
        }
        bool is_black_jack() {
            
        }
    private:
        std::vector<int> possible_scores() {
            // returns possible scores that this hand can achive
        }
};

/**
 * Design the data structures for a generic deck of cards. Explain how you would
 * subclass the data structures to implement blackjack.
 */
int main() {
    std::cout << "=================================================================================\n"
                 "This program is used for designing data structures for implementing deck of cards\n"
                 "=================================================================================\n";
}
