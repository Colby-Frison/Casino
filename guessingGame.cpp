#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string user;
int chips = -1;

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

void makeUser(string name){
    cout << "make new";
}

void start(){
    string input;

    // open file and check if exists
    ifstream file(fileConv(user));

    if (file.is_open()) {
        file.close();

        // display available chips
        cout << "Chips: " << getChips() << endl;
    }
    else {
        // printing the error message
        cout << "User does not exist" << endl;

        cout << "Create new User? [y/n]:";
        cin >> input;

        if(input == "y" || input == "Y" || input == "yes" || input == "Yes"){
            makeUser(user);
        }
        else if(input == "n" || input == "N" || input == "no" || input == "No"){

            cout << "Enter different user: ";
            cin >> user;
            cout << endl;
            start();
        }

    }
    file.close();
}

int main() {

    cout << "Enter Name: ";
    cin >> user;
    cout << endl;

    start();

    return 0;
}