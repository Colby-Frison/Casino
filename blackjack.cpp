#include "menu.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// card class, may stay here, but I may have move it over to another thing if I end up doing poker as well
class Card {
    private:
        string rank; // the number value
        string suit; // the symbol thing
        int val; // card val
        string ranks[13] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
    public:

        // constructors
        Card(): val(-1), suit("") {}
        Card(int rank, string suit): val(rank), suit(suit) {}

        // setters
        void setVal(int r) { rank = r; }
        void setSuit(string s) { suit = s; }

        // getters
        string getRank() { return ranks[val -1]; }
        string getSuit() { return suit; }
        int getVal() { return val; }

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

        // ranks string
        // string ranks[13] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};

        // rank int so its easier to get val
        int vals[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

        // denotes the top of the array so I can properly iterate the array as a queue
        int top;

    public:

        // constructor
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
                    deck[dIndex].setVal(vals[j]);

                    // and second deck
                    deck[dIndex + 52].setSuit(suits[i]);
                    deck[dIndex + 52].setVal(vals[j]);
                }
            }

            shuffleDeck();
        }

        void shuffleDeck() {

            srand(time(0)); 

            int randomNum = rand(); 
            int num = 1 + (rand() % 10);
            // makes a random number 1 - 10, change later, but this is just here for refrence

            // Going to use Fishet-Yates shuffle; look it up pretty simple
            // I chould just use the algorithm, but I don't wanna

            
        }

        int size() {
            return sizeof(deck);
        }

        Card draw() {
            top++;

            if ( top <= 104)
                return deck[top - 1];
            else {
                top = 1;
                shuffleDeck();
                return deck[top - 1];
            }
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
    private: 
        int val; // number value of hand
        int numCards; // number of cards in hand

        int bet = -1; // starts a -1 if not -1 assign bet
        // done this way so bet can be handled ber hand in case of splits

        bool doubled = false; // mark true if player doubled so it knows if player can hit again

        vector<Card> hand; // a vector containg a vectors of cards aka hands
        // I did this this way 

    public: 

        // constructor
        Hand(): val(-1), numCards(0) {}
        Hand(int val, int numCards, bool split, vector<Card> hand): val(val), numCards(numCards), hand(hand) {}

        //add card to hand
        void addCard(Card card, int index){
            hand.push_back(card);

            val += card.getVal();
            numCards++;
        }

        int getBet() {
            return bet;
        }

        void setBet(int b) {
            bet = b;
        }
};

Deck deck;

// This will be a method call to hand if the player wants to hit split or double
// Don't know if this is the way to go, but it seems right since it needs kind of be done recursively in the case of splits
void turn(Hand hand) {

}

// player is allowed to split when the have a pair of cards with the same rank (suit is irrelevant)
// when a split occurs the player places a bet of equal value on the pslit hand
// The idea is the returned vector can be either added to or made equal to the players hand, but if a splt occurs more than once a problem would occur
vector<Hand> split(Hand hand) {
     vector<Hand> newHand;

     return newHand;
}

// doubles players bet
// only able to double when player has 2 cards, only allowed to draw one more time
void doubleD(Hand hand) {
    hand.setBet(hand.getBet() * 2);
}

void bjLoop(Player player) {
    vector<Hand> playerHand;
    vector<Hand> houseHand;

    system("clear");
    
    int inputI;
    string inputS;


    // same logic from guessing game
    if(player.getChips() > 1){
        cout << "Place a bet 1 - " << player.getChips() << ": ";
        cin >> inputI;
        playerHand[0].setBet(inputI); // since this is the first thing done we done have to worrry about a split
    }
    else if(player.getChips() == 1){
        string input;
        cout << "You only have 1 chip left, would you like to bet it? [y/n]";
        cin >> input;
        if(yesCheck(input)){
            playerHand[0].setBet(1);
        }
        else {
            cout << "You have decided not to place the bet." << endl;
            cout << "Choose one of the following options:" << endl;

            cout << "1. Place the bet" << endl;
            cout << "2. Exit game" << endl;
            cout << "3. Pick new User" << endl;
            if(input == "1") {
                cout << "Placing bet" << endl;

                playerHand[0].setBet(1);

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

    if(playerHand[0].getBet() != -1){

        // Dealing
        // one card delt to each player, THEN to the dealer (all face up)
        // then another is dealt to each player again face up, then the dealer gets a card face down
        


        // Turn
        // player then gets the choice to hit/ stand/ double/ split
        // they can then continue to take turns on each hand until they decide to stand or they bust 

        // Dealers turn
        // Then dealer reveals card and hits until their hand is 17 or above (17 is arbitrary, its jus tthe house rules)

        // Winnings
        // Player bust = no win
        // House bust = player win
        // player & house tie = player win


    }

}

int main() {
    Deck deck;

    deck.printDeck();
    deck.printDeck();


    return 0;
}