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
        bool two_cards_available() {
            return dealt_index + 1 < cards.size();
        }
        bool one_card_available() {
            return dealt_index < cards.size();
        }
        T deal_card() {
            T t = cards[dealt_index];
            dealt_index++;
            return t;
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
    public:
        bool available = true;
        int face_value; // 11-Jack, 12-Queen, 13-King, 1-Ace, 2-10
        Suit suit;
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
        void print() {
            std::vector<std::string> face_values;
            face_values.push_back("A");
            face_values.push_back("1");
            face_values.push_back("2");
            face_values.push_back("3");
            face_values.push_back("4");
            face_values.push_back("5");
            face_values.push_back("6");
            face_values.push_back("7");
            face_values.push_back("8");
            face_values.push_back("9");
            face_values.push_back("10");
            face_values.push_back("J");
            face_values.push_back("Q");
            face_values.push_back("K");
            std::cout << face_values[face_value - 1];
            switch (suit)
            {
            case Suit::Club:
                std::cout << "c";
                break;
            case Suit::Heart:
                std::cout << "h";
                break;
            case Suit::Diamond:
                std::cout << "d";
                break;
            case Suit::Spade:
                std::cout << "s";
                break;
            default:
                break;
            }
            std::cout << ' ';
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
        void print() {
            for(T c : cards) {
                c.print();
            }
        }
};

class BlackJackCard : public Card {
    public:
        BlackJackCard(int val, Suit s) : Card::Card(val, s) {}
        int value() {
            if(is_ace()) return 1;
            else if(is_free_card()) return 10;
            return face_value;
        }
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
            return (max == std::numeric_limits<int>::min() ? min : max);
        }
        bool busted() {
            return score() > 21;
        }
        bool is_21() {
            return score() == 21;
        }
        bool is_black_jack() {
            if(cards.size() != 2) return false;
            BlackJackCard first = cards[0];
            BlackJackCard second = cards[1];
            return (first.is_ace() && second.is_free_card() || (second.is_ace() && first.is_free_card()));
        }
    private:
        void add_card_to_score_list(BlackJackCard card, std::vector<int>& scores) {
            if(scores.size() == 0) {
                scores.push_back(0);
            }
            int len = scores.size();
            for(int i = 0; i < len; i++) {
                int score = scores[i];
                scores[i] = score + card.min_val();
                if(card.min_val() != card.max_val()) {
                    scores.push_back(score + card.max_val());
                }
            }
        }
        std::vector<int> possible_scores() {
            // returns possible scores that this hand can achive
            std::vector<int> scores;
            if(cards.size() == 0) {
                scores.push_back(0);
                return scores;
            }
            for(BlackJackCard card : cards) {
                add_card_to_score_list(card, scores);
            }
            return scores;
        }
};

class BlackJackAutomator {
    public:
        Deck<BlackJackCard> deck;
        std::vector<BlackJackHand> hands;
        const int HIT_UNTIL = 16; 
        BlackJackAutomator(int n) : num_of_hands(n) {
            for(int i = 0; i < num_of_hands; i++) {
                hands.push_back(BlackJackHand());
            }
        }
        bool deal_initial() {
            for(BlackJackHand hand : hands) {
                if(!deck.two_cards_available()) {
                    return false;
                }
                BlackJackCard card1 = deck.deal_card();
                BlackJackCard card2 = deck.deal_card();
                hand.add_card(card1);
                hand.add_card(card2);
            }
            return true;
        }
        std::vector<int> get_black_jacks() {
            std::vector<int> winners;
            for(int i = 0; i < hands.size(); i++) {
                if(hands[i].is_black_jack()) {
                    winners.push_back(i);
                }
            }
            return winners;
        }
        bool play_hand(int i) {
            BlackJackHand hand = hands[i];
            return play_hand(hand);
        }
        bool play_hand(BlackJackHand& hand) {
            while (hand.score() < HIT_UNTIL)
            {
                if(!deck.one_card_available()) {
                    return false;
                }
                BlackJackCard card = deck.deal_card();
                hand.add_card(card);
            }
            return true;
        }
        bool play_all_hands() {
            for(BlackJackHand& hand : hands) {
                if(!play_hand(hand)) return false;
            }
            return true;
        }
        std::vector<int> get_winners() {
            std::vector<int> winners;
            int winning_score = 0;
            for(int i = 0; i < hands.size(); i++) {
                BlackJackHand hand = hands[i];
                if(!hand.busted()) {
                    if(hand.score() > winning_score) {
                        winning_score = hand.score();
                        winners.clear();
                        winners.push_back(i);
                    } else if(hand.score() == winning_score) {
                        winners.push_back(i);
                    }
                }
            }
            return winners;
        }
        void ini_deck() {
            std::vector<BlackJackCard> cards;
            for(int i = 1; i <= 13; i++) {
                for(int j = 0; j <= 3; j++) {
                    Suit suit = Suit(j);
                    BlackJackCard card(i, suit);
                    cards.push_back(card);
                }
            }
            deck.set_deck_of_cards(cards);
            deck.shuffle();
        }
        void print_hands_and_score() {
            for(int i = 0; i < hands.size(); i++) {
                std::cout << "Hand " << i << " (" << hands[i].score() << "): ";
                hands[i].print();
                std::cout << '\n';
            }
        }
    private:
        int num_of_hands;
};

/**
 * Design the data structures for a generic deck of cards. Explain how you would
 * subclass the data structures to implement blackjack.
 */
int main() {
    std::cout << "=================================================================================\n"
                 "This program is used for designing data structures for implementing deck of cards\n"
                 "=================================================================================\n";
    int num_of_hands = 5;
    BlackJackAutomator automator(num_of_hands);
    automator.ini_deck();
    bool success = automator.deal_initial();
    if(!success) {
        std::cout << "Error. Out of cards\n";
    } else {
        std::cout << "-- Initial --\n";
        automator.print_hands_and_score();
        std::vector<int> black_jacks = automator.get_black_jacks();
        if(black_jacks.size() > 0) {
            std::cout << "Blackjack at ";
            for(int i : black_jacks) {
                std::cout << i << ", ";
            }
            std::cout << '\n';
        } else {
            success = automator.play_all_hands();
            if(!success) {
                std::cout << "Error. Out of cards\n";
            } else {
                std::cout << "\n-- Completed Game --\n";
                automator.print_hands_and_score();
                std::vector<int> winners = automator.get_winners();
                if(winners.size() > 0) {
                    std::cout << "Winners: ";
                    for(int i : winners) {
                        std::cout << i << ", ";
                    }
                    std::cout << '\n';
                } else {
                    std::cout << "Draw. All players have busted\n";
                }
            }
        }
    }
}
