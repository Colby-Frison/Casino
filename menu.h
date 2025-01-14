#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

bool yesCheck(string input);

class Player {
    private:
        string user; // username
        int chips; // number of chips available
        bool userSelected; // is there a user selected, doesnt make since for first user selection, but when switching between users its nice
        string playing; // stores what game is being played, null if nothing

    public:

        // constructors
        Player(): chips(-1), userSelected(false) {
            system("clear");
            cout << "No user selected, select user? [y/n]:";

            string input;
            cin >> input;

            if(yesCheck(input)){
                cout << "Enter name: ";
                cin >> input;
                user = input;

                ifstream file(filename());

                if (!file.is_open()) {
                    system("clear");
                    cout << "==Profile created==" << endl;
                    cout << "Username: " << user << endl;
                    cout << "Chips available: 50" << endl << endl;
                    chips = 50;
                }
                else {
                    string in;
                    cout << user << " profile already exists, select? [y/n]: ";
                    cin >> in;
                    if(yesCheck(in)){
                        getChips();
                        system("clear");

                        cout << "==Profile selected==" << endl;
                        cout << "Username: " << user << endl;
                        cout << "Chips available: " << chips << endl << endl;
                    }
                    else {
                        Player();
                    }
                }
            }
            else {
                return;
            }
        }

        Player(string user): chips(-1), user(user), userSelected(true) {
            getChips(); // gets user's saved chips value
            system("clear");

            cout << "==Profile selected==" << endl;
            cout << "Username: " << user << endl;
            cout << "Chips available: " << chips << endl;
            // doesn't need save as if it already has a file which its pulling chips from, and no changes were made so no save needed
        }
        Player(string user, int chips): user(user), chips(chips), userSelected(true) {
            system("clear");

            cout << "==Profile selected==" << endl;
            cout << "Username: " << user << endl;
            cout << "Chips available: " << chips << endl;
            save(false); // needs save to create and write to the new user's file
        }
        Player(string user, int chips, string game): user(user), chips(chips), userSelected(true), playing(game) {}

        // Getters:
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

        int gChips() const {
            return chips;
        }

        // Setters: 
        void selectUser(){
            userSelected = true;
        }
        void unselectUser(){
            userSelected = false;
        }
        bool getselectStatus(){
            return userSelected;
        }
        void addChips(int x){
            chips += x;
        }
        void takeChips(int x){
            chips -= x;
        }

        // save progress by updating chips in txt profile
        void save(bool display){
            ofstream file(filename());
            file << "Chips: " << chips;

            system("clear");

            if(true){
                cout << endl << "Progress Saved" << endl;
                cout << "Username: " << user << endl;
                cout << "Chips available: " << chips << endl << endl;
            }
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

        // For loading chips from file
        void loadChips() {
            if(chips == -1) {
                ifstream userFile(filename());
                string line;
                getline(userFile, line);
                string chipStr = "";
                for(char c : line) {
                    if(isdigit(c)) {
                        chipStr += c;
                    }
                }
                chips = stoi(chipStr);
                userFile.close();
            }
        }

};

// Header files seem to be working just have to reimplement functions in porper files and add proper functions to the correct headers
// also need to rewrite some of the functions to work with the Player class