#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string user;
int chips = -1;
bool userSelected = false;


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

        if(input == "y" || input == "Y" || input == "yes" || input == "Yes"){
            makeUser();
        }
        else if(input == "n" || input == "N" || input == "no" || input == "No"){

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

int main() {

    cout << "Enter Name: ";
    cin >> user;
    cout << endl;

    pickUser();
    if(userSelected) // if user us selected enter game loop
        gameLoop();

    save(); // once gameloop is exited save game before exiting program

    return 0;
}