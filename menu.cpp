#include "menu.h"
#include "guessingGame.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// player class go here If i accidentally broke everything

    // returns a bool based on user entry, implemented because there are a lot of yes no checks
    bool yesCheck(string input){
        if(input == "y" || input == "Y" || input == "yes" || input == "Yes"){
                return true;
        }
        return false;

    }


    
    void start(Player player){
        if(player.getselectStatus()) {// if user us selected enter game loop
            string input;

            cout << "Start game? [y/n] ";
            cin >> input;
            cout << endl;

            // need to adjust this file and header file to resolve the following errors, read TODO to see how
            if(yesCheck(input)){
                gameLoop(player);
            }
            else {
                option(true, player);
            } 

        }
        else {
            string input;

            cout << "Enter Name: ";
            cin >> input;
            cout << endl;

            Player p = Player(input);

            player = Player(p);
            start(player);
        }
        
    }
    

int main() {

    Player player;

    player.save(true); // once gameloop is exited save game before exiting program

    return 0;
}