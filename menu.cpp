#include "menu.h"
#include "guessingGame.h"
#include "blackjack.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

    bool yesCheck(string input){
        if(input == "y" || input == "Y" || input == "yes" || input == "Yes"){
            return true;
        }
        else { return false; }
    }

    void chooseGame(Player& player){
        string input;
        system("clear");
        cout << "Choose game: " << endl;
        cout << "1. Guessing Game" << endl;
        cout << "2. Blackjack" << endl;
        cin >> input;

        if(input == "1"){
            guessLoop(player);
        }
        else if(input == "2"){
            bjLoop(player);
        }
        else {
            chooseGame(player);
        }
    }
    
    void start(){
        system("clear");

        string input;

        Player player = Player();
        chooseGame(player);
    }
    

int main() {

    start();

    return 0;
}