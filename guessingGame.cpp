#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string user;
int chips = -1;
int round = 0;
bool userSelected = false;


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

// creates new user based on global user variable
void makeUser(){
    ofstream file(fileConv(user));
    chips = 10;

    file << "Chips: 10";

    
    cout << endl << "New user created" << endl;
    cout << "Username: " << user << endl;
    cout << "Chips available: " << chips << endl;
}

// user global user variable to select user profile
// if profile doesnt exist create new profile
void pickUser(){
    string input;

    // open file and check if exists
    ifstream file(fileConv(user));

    if (file.is_open()) {
        file.close();

        // display available chips
        cout << "Chips: " << getChips() << endl;
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
            pickUser();
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
    cout << "Chips available: " << chips << endl;
}

void gameLoop(){

}

void start(){
    if(userSelected) {// if user us selected enter game loop
        string input;

        cout << "Start game? [y/n]";
        cin >> input;
        cout << endl;

        if(yesCheck(input))
            gameLoop();
        else {
            cout << "Options:" << endl;
            cout << "1. Pick different user" << endl;
            cout << "2. Exit game" << endl;
            cout << "3. Start game" << endl;

            cout << "Choose number [1/2/3]:";
            cin >> input;
            cout << endl;

            if(input == "1") {
                cout << "Picking new user: " << endl;
                userSelected = false;

                cout << "Enter user: ";
                cin >> user;
                cout << endl;
                pickUser();

            }
            else if(input == "2") {
                // exit game;
            }
            else if(input == "3") {
                cout << "Starting game: " << endl;

                gameLoop();
            }
            else {
                cout << "Please choose valid option";
            }
        } 

    }
    else {
        cout << "Enter Name: ";
        cin >> user;
        cout << endl;

        pickUser();
        start();
    }
}

int main() {

    start();


    save(); // once gameloop is exited save game before exiting program

    return 0;
}