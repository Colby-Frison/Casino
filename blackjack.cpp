#include "menu.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// card class, may stay here, but I may have move it over to another thing if I end up doing poker as well
class Card {
    private:
        string rank; // the number value
        string suit; // the symbol thing
    public:

        // constructors
        Card(): rank(""), suit("") {}
        Card(string rank, string suit): rank(rank), suit(suit) {}

        // setters
        void setRank(string r) { rank = r; }
        void setSuit(string s) { suit = s; }

        // getters
        string getRank() { return rank; }
        string getSuit() { return suit; }

        // print function
        void printCard() { cout << rank << suit; }
};

class Deck {
    private:
        // initialize array of Cards of size 104 so its 2 decks instead of 1
        // Poker is also played with 2 decks so this just works better
        Card deck[104];

        // Arrays to initialize the cards

        // suits arent important for black jack, but its good to have if I go over to poker
        // H = hearts, D = diamonds, C = clubs, S = spades
        string suits[4] = {"H", "D", "C", "S"};

        //
        string ranks[13] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};

    public:

        Deck() {
            // nested loop to intialize all cards
            // i loops through all possible suits j loops through all possible ranks
            // This goes through all possible cards
            for(int i = 0; i < 4 ; i++) {
                for(int j = 0; j < 13; j++) {
                    // index of the card being indexed
                    int dIndex = i * 13 + j;

                    // initialize first deck
                    deck[dIndex].setSuit(suits[i]);
                    deck[dIndex].setRank(ranks[j]);

                    // and second deck
                    deck[dIndex + 52].setSuit(suits[i]);
                    deck[dIndex + 52].setRank(ranks[j]);
                }
            }
        }

        void shuffleDeck() {

            srand(time(0)); 

            int randomNum = rand(); 
            int num = 1 + (rand() % 10);
            // makes a random number 1 - 10, change later, but this is just here for refrence

            // Going to use Fishet-Yates shuffle; look it up pretty simple
            // I chould just use the algorithm, but I don't wanna

            
        }


        void printDeck() {

            int suitChange = 0;
            for(int i = 0; i < 104; i++){
                deck[i].printCard();
                cout << " ";
                suitChange++;
                if(suitChange < 13){
                    cout << " ";
                }
                else {
                    suitChange = 0;
                    cout << endl;
                }
            }
        }

};

class Hand {
    // this class is going to make it a little easier to handle each hand
    // needs hit() split() doubledown() methods
    // needs sum of cards variable and a vector to store the number of cards in each hand
};

void bjLoop(Player player) {

    system("clear");

    int bet = -1;

    // same logic from guessing game
    if(player.getChips() > 1){
        cout << "Place a bet 1 - " << player.getChips() << ": ";
        cin >> bet;
    }
    else if(player.getChips() == 1){
        string input;
        cout << "You only have 1 chip left, would you like to bet it? [y/n]";
        cin >> input;
        if(yesCheck(input)){
            bet = 1;
        }
        else {
            cout << "You have decided not to place the bet." << endl;
            cout << "Choose one of the following options:" << endl;

            cout << "1. Place the bet" << endl;
            cout << "2. Exit game" << endl;
            cout << "3. Pick new User" << endl;
            if(input == "1") {
                cout << "Placing bet" << endl;

                bet = 1;

            }
            else if(input == "2") {
                // exit game;
                player.save(true);
                return;
            }
            else if(input == "3") {
                cout << "Picking new user: " << endl;
                player.unselectUser();

                cout << "Enter user: ";
                cin >> input;
                cout << endl;
                Player(input);
            }
            else {
                cout << "Please choose valid option";

                // still need to work out a loop here
            }
        }
    }
    else {
        cout << "You do not have enough chips to place a bet, please choose one of the following options: " << endl;

        // Create a option method, most likely it can be the same as guessingGames, but I will probably need to change some stuff

        //option(false, player);
    }

    if(bet != -1){

        //actual game logic

        // shuffle will never actually be called, shuffle will be called after the deck is initialized, which is at the begining 
        // of the game, and if the deck is ever empty.

        // I will have to be very carefull when drawing cards as a deck close to empty can cause issues

    }

}

int main() {
    Deck deck;

    deck.printDeck();
    deck.printDeck();


    return 0;
}