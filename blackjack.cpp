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
        string getRank() const { return ranks[val -1]; }
        string getSuit() const { return suit; }
        int getVal() const { return val; }

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
            
            // Fisher-Yates shuffle algorithm
            for (int i = 103; i > 0; i--) {
                // Generate random index between 0 and i (inclusive)
                int j = rand() % (i + 1);
                
                // Swap elements at i and j
                Card temp = deck[i];
                deck[i] = deck[j]; 
                deck[j] = temp;
            }
            
            // Reset top of deck
            top = 0;
        }

        int size() {
            return sizeof(deck);
        }

        Card draw() {
            if (top >= 104) {
                shuffleDeck();
                top = 0;
            }
            return deck[top++];
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

        vector<Card>& getCards() {
            return hand;
        }
        
        void displayHand() {
            for (const Card& card : hand) {
                cout << card.getRank() << card.getSuit() << " ";
            }
            cout << endl;
        }
        
        int getValue() {
            return val;
        }
        
        int getNumCards() {
            return numCards;
        }
        
        bool isDoubled() {
            return doubled;
        }
        
        bool canSplit() {
            return numCards == 2 && hand[0].getRank() == hand[1].getRank();
        }
};

Deck deck;


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
    vector<Hand> houseHand; // now that I'm thinking about it, house doesnt need a hand vecto as a split will never ocur so I can just go with a single hand

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
        cout << "1. Exit game" << endl;
        cout << "2. Pick new user" << endl;
        
        string input;
        cin >> input;
        
        if(input == "1") {
            player.save(true);
            return;
        }
        else if(input == "2") {
            cout << "Picking new user: " << endl;
            player.unselectUser();
            
            cout << "Enter user: ";
            cin >> input;
            cout << endl;
            Player(input);
        }
        else {
            cout << "Please choose a valid option" << endl;
            //make loopable
        }
    }

    if(playerHand[0].getBet() != -1) {
        // Dealing initial cards
        for (auto& hand : playerHand) {
            hand.addCard(deck.draw(), 0); // Not the intended way as it may cause a problem if a split occurs
        }
        houseHand[0].addCard(deck.draw(), 0);  // Dealer's first card (face up)
        
        for (auto& hand : playerHand) {
            hand.addCard(deck.draw(), 0);
        }
        houseHand[0].addCard(deck.draw(), 0);  // Dealer's second card (face down)

        // Display initial hands
        cout << "Dealer's hand: " << houseHand[0].getCards()[0].getRank() << " [Hidden]" << endl;
        cout << "Your hand: ";
        playerHand[0].displayHand();
        
        // Player's turn for each hand
        for (auto& hand : playerHand) {
            bool playing = true;
            while (playing && hand.getValue() < 21) {
                cout << "\nChoose action (1: Hit, 2: Stand, 3: Double, 4: Split): ";
                cin >> inputI;
                
                switch(inputI) {
                    case 1: // Hit
                        hand.addCard(deck.draw(), 0);
                        hand.displayHand();
                        break;
                    case 2: // Stand
                        playing = false; // not sure about this
                        break;
                    case 3: // Double
                        if (hand.getNumCards() == 2 && !hand.isDoubled()) {
                            doubleD(hand);
                            hand.addCard(deck.draw(), 0);
                            hand.displayHand(); // make sure this wors after splits
                            playing = false;
                        } else {
                            cout << "Cannot double at this time!" << endl;
                        }
                        break;
                    case 4: // Split
                        if (hand.canSplit()) {
                            playerHand = split(hand);
                        } else {
                            cout << "Cannot split these cards!" << endl;
                        }
                        break;
                    default:
                        cout << "Invalid option!" << endl;
                }
            }
            
            if (hand.getValue() > 21) {
                cout << "Bust!" << endl;
            }
        }

        // Dealer's turn
        cout << "\nDealer's turn:" << endl;
        houseHand[0].displayHand(); // Show both cards
        
        while (houseHand[0].getValue() < 17) {
            houseHand[0].addCard(deck.draw(), 0);
            houseHand[0].displayHand();
        }

        // Determine winners and pay out
        for (auto& hand : playerHand) {
            if (hand.getValue() <= 21) {
                if (houseHand[0].getValue() > 21 || hand.getValue() > houseHand[0].getValue()) {
                    player.addChips(hand.getBet() * 2);  // Win pays 2:1
                    cout << "Hand won! +" << hand.getBet() * 2 << " chips" << endl;
                } else if (hand.getValue() == houseHand[0].getValue()) {
                    player.addChips(hand.getBet());  // Push returns bet
                    cout << "Push! Bet returned" << endl;
                } else {
                    cout << "Hand lost!" << endl;
                }
            }
        }
    }

}
