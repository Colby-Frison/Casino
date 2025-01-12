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

void bjLoop(Player player) {

}

int main() {
    Deck deck;

    deck.printDeck();
    deck.printDeck();


    return 0;
}