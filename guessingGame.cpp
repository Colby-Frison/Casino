#include "menu.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
string user;
int chips = -1;
int roundNum = 0;
bool userSelected = false;
*/


// default for gameloop function so it can be called in the option function
void guessLoop(Player player);

// displays rules
void rules(){
    cout << endl;
    cout << "You are currently playing the Guessing game. The rules are as follows: " << endl;
    cout << "In order to play you will first place a bet, then guess a number 1 - 10." << endl;
    cout << "If the number you guess is within 1 of the number you dont lose any chips." << endl;
    cout << "If you guess the number exactly you recieve the amount you bet." << endl;
    cout << "If you are outside farther from 1 from the target number you lose your bet." << endl << endl;
}

// prints options and handles the options, recieves bool to determine if the thrid option "play game" should be displayed
// semi-flexible function, used in most cases, but have to do it manually when placing a bet and balance is only 1
void option(bool third, Player player){
    string input;

    cout << endl << "Options:" << endl;
    cout << "1. Pick different user" << endl;
    cout << "2. Exit game" << endl;
    if(third){
        cout << "3. Start game" << endl;

        cout << "Choose number [1/2/3]:";
    }
    else {
        cout << "Choose number [1/2]:";
    }
    cin >> input;
    cout << endl;

    if(input == "1") {
        cout << "Picking new user: " << endl;
        player.unselectUser();

        cout << "Enter user: ";
        cin >> input;
        cout << endl;
        player = Player(input);

    }
    else if(input == "2") {
        // exit game;
        player.save(true);
        return;
    }
    else if(third && input == "3") {
        cout << "Starting game: " << endl;

        rules();
        guessLoop(player);
    }
    else {
        cout << "Please choose valid option";
        option(third, player);
    }
}

void guessLoop(Player player){
    system("clear");
    int bet = -1;
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
                // I'm now reaizing this has no way of looping so create a method
                // that is able to takes in parameters and is able to proporly have the options menu 
                // pop up and handle errors effectively

                // Along with that see if there is a way to make it clear on each text entry/prompt
                // Also see if theres a way to make the file directory not be there.
                // That obviously isnt nessesary, but it would definatley make it more visually appealing
            }
        }
    }
    else {
        cout << "You do not have enough chips to place a bet, please choose one of the following options: " << endl;

        option(false, player);
    }

    if (bet != -1){
        srand(time(0)); 

        int randomNum = rand(); 
        int num = 1 + (rand() % 10);

        cout << "Enter a number 1 - 10 :" ;

        string guess;
        cin >> guess;

        cout << endl << endl << "The number was: " << to_string(num) << endl << endl;

        if (stoi(guess) == num){
            cout << "You guessed the number" << endl;
            cout << "You have recieved " << bet * 2 << " chips" << endl;
            int win = bet * 2;
            player.addChips(win);

            cout << endl << "Current balance is now: " <<  player.getChips() << endl;

        }
        else if(stoi(guess) == num + 1 || stoi(guess) == num - 1 ) {
            cout << "You have guessed one away from the number so you don't lose any chips" << endl;


            cout << endl << "Current balance is now: " <<  player.getChips() << endl;

        }
        else {
            cout << "You have guessed incorectly, so you have lost " << bet << " chips" << endl << endl;

            player.takeChips(bet);
            if(player.getChips() == 1){
                cout << "You only have one chip left spend it carefully" << endl;
            }
            else if(player.getChips() == 0) {
                if(num % 2 == 0) {
                    cout << "You have no more chips, maybe its time to call it" << endl;
                }
                else {
                    cout << "You have no more chips please exit or choose a new profile" << endl;
                }
            }
            else {
                cout << "You now have " << player.getChips() << " chips left, spend them carefully" << endl << endl;
            }
        }

        if(player.getChips() >= 1){
            cout << "Play again? [y/n] ";

            string input;
            cin >> input;
            if(yesCheck(input)){ 
                guessLoop(player);
            }
            else{
                option(true, player);
            }
        }
        else {
            cout << "Please choose one of the following options:" << endl;
            option(false, player);
        }
    }
}