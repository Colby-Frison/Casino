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
        void setVal(int v) { val = v; }
        void setSuit(string s) { suit = s; }

        // getters
        string getRank() const { return ranks[val -1]; }
        string getSuit() const { return suit; }
        int getVal() const { 
            if (val == 1) return 11;  // Ace (handled as 1 or 11 in Hand class)
            if (val > 10) return 10;  // Face cards
            return val;  // Number cards
        }

        // print function
        void printCard() const { 
            cout << ranks[val - 1] << suit; 
        }
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


        // denotes the top of the array so I can properly iterate the array as a queue
        int top;

    public:

        // constructor
        Deck() {
            top = 0;
            // nested loop to intialize all cards
            // i loops through all possible suits j loops through all possible ranks
            // This goes through all possible cards
            for(int i = 0; i < 4 ; i++) {
                for(int j = 0; j < 13; j++) {
                    // index of the card being indexed
                    int dIndex = i * 13 + j;

                    // initialize first deck
                    deck[dIndex].setSuit(suits[i]);
                    deck[dIndex].setVal(j + 1);

                    // and second deck
                    deck[dIndex + 52].setSuit(suits[i]);
                    deck[dIndex + 52].setVal(j + 1);
                }
            }

            shuffleDeck();
        }

        void shuffleDeck() {
            static bool seeded = false;
            if (!seeded) {
                srand(time(0));
                seeded = true;
            }
            
            // Fisher-Yates shuffle algorithm
            for (int i = size() - 1; i > 0; i--) {
                // Generate random index between 0 and i (inclusive)
                int j = rand() % (i + 1);
                
                // Verify indices are valid
                if (i < size() && j < size()) {
                    // Swap elements at i and j
                    Card temp = deck[i];
                    deck[i] = deck[j]; 
                    deck[j] = temp;
                }
            }
            
            // Reset top of deck
            top = 0;
        }

        int size() {
            return 104;
        }

        Card draw() {
            if (top < 0 || top >= 104) {
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
        
        bool canSplit(const Player& player) const {
            // Check if hand has exactly 2 cards of the same value
            if (hand.size() != 2 || hand[0].getVal() != hand[1].getVal()) {
                return false;
            }
            
            // Check if player has enough chips to match the current bet
            if (player.gChips() < bet) {
                return false;
            }
            
            return true;
        }

        int getBlackjackValue() {
            int total = 0;
            int aces = 0;
            
            for (const Card& card : hand) {
                if (card.getVal() == 1) {  // Ace
                    aces++;
                    total += 11;
                } else if (card.getVal() > 10) {  // Face cards
                    total += 10;
                } else {
                    total += card.getVal();
                }
            }
            
            // Adjust for aces if over 21
            while (total > 21 && aces > 0) {
                total -= 10;  // Convert ace from 11 to 1
                aces--;
            }
            
            return total;
        }

        int getBlackjackValueHose() {
            int total = 0;
            int aces = 0;
            
            for (const Card& card : hand) {
                if (card.getVal() == 1) {  // Ace
                    aces++;
                    total += 11;
                } else if (card.getVal() > 10) {  // Face cards
                    total += 10;
                } else {
                    total += card.getVal();
                }
            }
            
            // Adjust for aces if over 21
            while (total > 21 && aces > 0) {
                total -= 10;  // Convert ace from 11 to 1
                aces--;
            }
            
            return total;
        }
};

Deck deck;
vector<Hand> playerHand;
vector<Hand> houseHand;

void bjLoop(Player player);

// player is allowed to split when the have a pair of cards with the same rank (suit is irrelevant)
// when a split occurs the player places a bet of equal value on the pslit hand
// The idea is the returned vector can be either added to or made equal to the players hand, but if a splt occurs more than once a problem would occur
vector<Hand> split(Hand& hand) {
    vector<Hand> newHands;
    
    // Create two new hands from the split
    Hand hand1;
    Hand hand2;
    
    // Set bets for both hands equal to original
    int originalBet = hand.getBet();
    hand1.setBet(originalBet);
    hand2.setBet(originalBet);
    
    // Distribute the cards
    hand1.addCard(hand.getCards()[0], 0);
    hand2.addCard(hand.getCards()[1], 0);
    
    // Add new card to each hand
    hand1.addCard(deck.draw(), 0);
    hand2.addCard(deck.draw(), 0);
    
    newHands.push_back(hand1);
    newHands.push_back(hand2);
    
    return newHands;
}

// doubles players bet
// only able to double when player has 2 cards, only allowed to draw one more time
void doubleD(Hand hand) {
    hand.setBet(hand.getBet() * 2);
}

int handleOptions(Player& player) {
    while (true) {
        cout << "Choose one of the following options:" << endl;
        cout << "1. Exit game" << endl;
        cout << "2. Pick new user" << endl;

        string input;
        cin >> input;

        if (input == "1") {
            player.save(true);
            return 1;
        }
        else if (input == "2") {
            player.unselectUser();
            player = Player();
            return 2;
        }
        else {
            cout << "Please choose a valid option" << endl;
        }
    }
}

void playAgain(Player player) {
    string input;
    cout << "Play again? [y/n]" << endl;
    cin >> input;
    if(yesCheck(input)) {
        // Clear hands before starting new game
        playerHand.clear();
        houseHand.clear();
        bjLoop(player);
        return;
    }
    else {
        handleOptions(player);
        return;
    }
}

void bjLoop(Player player) {
    // Initialize hands if empty
    if (playerHand.empty()) {
        playerHand.push_back(Hand());
    }
    if (houseHand.empty()) {
        houseHand.push_back(Hand());
    }

    system("clear");
    
    int inputI;
    string inputS;


    // same logic from guessing game
    if(player.getChips() > 1){
        cout << "Place a bet 1 - " << player.getChips() << ": ";
        cin >> inputI;
        system("clear");

        cout << "Bet placed: " << inputI << endl << endl;

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
            handleOptions(player);
            return;
        }
    }
    else {
        cout << "You do not have enough chips to place a bet" << endl;
        handleOptions(player);
        return;
    }

    if(playerHand[0].getBet() != -1) {
        // Dealing initial cardsc
        for (Hand& hand : playerHand) {
            hand.addCard(deck.draw(), 0);
        }
        houseHand[0].addCard(deck.draw(), 0);  // Dealer's first card (face up)

        for (Hand& hand : playerHand) {
            hand.addCard(deck.draw(), 0);
        }
        houseHand[0].addCard(deck.draw(), 0);  // Dealer's second card (face down)

        // Display initial hands
        cout << "Dealer's hand: " << endl; 
        houseHand[0].getCards()[0].printCard();
        cout << " [Hidden]" << endl;
        cout << "Your hand: ";

        playerHand[0].displayHand();
        
        // Player's turn for each hand
        for (auto& hand : playerHand) {
            bool playing = true;
            while (playing && hand.getBlackjackValue() < 21) {
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
                        if (hand.canSplit(player)) {
                            playerHand = split(hand);
                        } else {
                            cout << "Cannot split these cards!" << endl;
                        }
                        break;
                    default:
                        cout << "Invalid option!" << endl;
                }
            }
            
            if (hand.getBlackjackValue() > 21) {
                cout << "Bust!" << endl << endl;
                player.takeChips(hand.getBet());
                cout << "Hand lost!" << endl << endl;;
                playAgain(player);
                return;
            }
            else if (hand.getBlackjackValue() == 21) {
                cout << "Blackjack!" << endl << endl;

                player.addChips(hand.getBet() * 2); 
                cout << "Hand won! +" << hand.getBet() * 2 << " chips" << endl;
                playAgain(player);
                return;
            }

        }

        // Dealer's turn
        cout << "\nDealer's turn:" << endl;
        houseHand[0].displayHand(); // Show both cards
        
        while (houseHand[0].getBlackjackValueHose() < 17) {
            houseHand[0].addCard(deck.draw(), 0);
            houseHand[0].displayHand();
        }

        // Determine winners and pay out
        for (auto& hand : playerHand) {
            if (hand.getBlackjackValue() <= 21) {
                if (houseHand[0].getBlackjackValue() > 21 || hand.getBlackjackValue() > houseHand[0].getBlackjackValue()) {
                    player.addChips(hand.getBet() * 2);  // Win pays 2:1
                    cout << "Hand won! +" << hand.getBet() * 2 << " chips" << endl;
                } else if (hand.getBlackjackValue() == houseHand[0].getBlackjackValueHose()) {
                    player.addChips(hand.getBet());  // Push returns bet
                    cout << "Push! Bet returned" << endl;
                } else {
                    player.takeChips(hand.getBet());
                    cout << "Hand lost!" << endl;
                }
            }
        }

        playAgain(player);
    }

}