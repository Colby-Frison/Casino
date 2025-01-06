#include "menu.h"
#include "guessingGame.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;


class Player {
    private:
        string user; // username
        int chips; // number of chips available
        bool userSelected; // is there a user selected, doesnt make since for first user selection, but when switching between users its nice
        string playing; // stores what game is being played, null if nothing

    public:

        // constructors
        Player(): chips(-1), userSelected(false) {
            cout << "No user selected, create new user? [y/n]:";

            string input;
            cin >> input;

            if(yesCheck(input)){
                cout << "Enter name: ";
                cin >> input;
                user = input;

                ifstream file(filename());

                if (!file.is_open()) {
                    chips = 10;
                }
                else {
                    cout << "User already exists, select " << user << "? [y/n]: ";
                    cin >> input;
                    if(yesCheck(input)){
                        ifstream userFile(filename());

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
                    else {
                        
                    }
                }
            }


        }
        Player(string user): user(user) {
            getChips();
        }
        Player(string user, int chips): user(user), chips(chips), userSelected(true) {}
        Player(string user, int chips, string game): user(user), chips(chips), userSelected(true), playing(game) {}

        // returns user
        string getUser(){
            return user;
        }

        // if chips is -1 it updates chip from user file, else it returns what the current chip value is 
        int getChips(){
            if(chips == -1) {
                ifstream userFile(filename());

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

        string filename(){
            string fileName = "Users/";
            fileName += user;
            fileName += ".txt";

            return fileName;
        }

        void selectUser(){
            userSelected = true;
        }

        void unselectUser(){
            userSelected = false;
        }

        bool getselectStatus(){
            return userSelected;
        }

        // save progress by updating chips in txt profile
        void save(){
            ofstream file(filename());

            file << "Chips: " << chips;
            
            cout << endl << "Progress Saved" << endl;
            cout << "Username: " << user << endl;
            cout << "Chips available: " << chips << endl << endl;
        }

};


    // returns a bool based on user entry, implemented because there are a lot of yes no checks
    bool yesCheck(string input){
        if(input == "y" || input == "Y" || input == "yes" || input == "Yes"){
                return true;
        }
        return false;

    }

    // creates new user based on global user variable
    void makeUser(string name){
        Player player = Player(name, 10);
        
        ofstream file(player.filename());
        
        file << "Chips: 10";

        
        cout << endl << "New user created" << endl;
        cout << "Username: " << name << endl;
        player.printChips();
    }

    // user global user variable to select user profile
    // if profile doesnt exist create new profile
    void pickUser(Player player){
        string input;

        // open file and check if exists
        ifstream file(player.filename());

        if (file.is_open()) {
            file.close();

            // display available chips
            cout << endl << "Chips: " << player.getChips() << endl;
            player.selectUser();
        }
        else {
            // printing the error message
            cout << "User does not exist" << endl;

            cout << "Create new User? [y/n]:";
            cin >> input;

            if(yesCheck(input)){
                makeUser(player.getUser());
            }
            else{

                cout << "Enter different user: ";
                cin >> input;
                cout << endl;

                Player p = Player(input);
                pickUser(p);
            }

        }
        file.close();
    }

    /*
    void start(Player player){
        if(player.getselectStatus()) {// if user us selected enter game loop
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
            string input;

            cout << "Enter Name: ";
            cin >> input;
            cout << endl;

            Player p = Player(input);

            pickUser(player);
            start(player);
        }
        
    }
    */

int main() {

    Player player;

    player.save(); // once gameloop is exited save game before exiting program

    return 0;
}