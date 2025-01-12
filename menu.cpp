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
    
    void start(){
        system("clear");

        string input;

        Player player = Player();
        cout << "Start game? [y/n] ";
        cin >> input;
        cout << endl;

        // need to adjust this file and header file to resolve the following errors, read TODO to see how
        if(yesCheck(input)){
            guessLoop(player);
        }
        else {
            option(true, player);
        } 
    }
    

int main() {

    start();

    return 0;
}