#include "guessingGame.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;


class Player {
    public:
        string user; // username
        int chips = -1; // number of chips available
        bool userSelected = false; // is there a user selected, doesnt make since for first user selection, but when switching between users its nice
        string playing; // stores what game is being played


    Player(){}
    // returns a bool based on user entry, implemented because there are a lot of yes no checks
    bool yesCheck(string input){
        if(input == "y" || input == "Y" || input == "yes" || input == "Yes"){
                return true;
        }
        return false;

    }

    //converts name to the proper file name in directory
    string fileConv(string name){
        string fileName = "Users/";
        fileName += user;
        fileName += ".txt";

        return fileName;
    }

    // opens file and updates chips global variable
    int getChips(){
        if(chips == -1) {
            ifstream userFile(fileConv(user));

            string line;
            getline(userFile, line);

            string chipStr = "";

            // loop line and get num
            for(char c : line){
                if(isdigit(c)) {
                    chipStr += c;
                }
            }
            chips = stoi(chipStr);

            userFile.close();
        }

        return chips;
    }

    // prints available chips to console
    void printChips() {
        cout << "Chips available: " << chips << endl;
    }

    // creates new user based on global user variable
    void makeUser(){
        ofstream file(fileConv(user));
        chips = 10;

        file << "Chips: 10";

        
        cout << endl << "New user created" << endl;
        cout << "Username: " << user << endl;
        printChips();
    }

    // user global user variable to select user profile
    // if profile doesnt exist create new profile
    void pickUser(Player player){
        string input;

        // open file and check if exists
        ifstream file(fileConv(user));

        if (file.is_open()) {
            file.close();

            // display available chips
            cout << endl << "Chips: " << getChips() << endl;
            userSelected = true;
        }
        else {
            // printing the error message
            cout << "User does not exist" << endl;

            cout << "Create new User? [y/n]:";
            cin >> input;

            if(yesCheck(input)){
                makeUser();
            }
            else{

                cout << "Enter different user: ";
                cin >> user;
                cout << endl;
                pickUser(player);
            }

        }
        file.close();
    }

    // save progress by updating chips in txt profile
    void save(){
        ofstream file(fileConv(user));

        file << "Chips: " << chips;
        
        cout << endl << "Progress Saved" << endl;
        cout << "Username: " << user << endl;
        cout << "Chips available: " << chips << endl << endl;
    }

    void start(Player player){
        if(userSelected) {// if user us selected enter game loop
            string input;

            cout << "Start game? [y/n] ";
            cin >> input;
            cout << endl;

            if(yesCheck(input)){
                rules();
                gameLoop(player);
            }
            else {
                option(true, player);
            } 

        }
        else {
            cout << "Enter Name: ";
            cin >> user;
            cout << endl;

            pickUser(player);
            start(player);
        }
    }

};

int main() {

    Player player;

    player.save(); // once gameloop is exited save game before exiting program

    return 0;
}