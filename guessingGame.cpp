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

int main() {
    // get user name and set user
    cout << "Enter Name: ";
    cin >> user;
    cout << endl;

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
    }

    file.close();

    cout << "Chips: " << getChips() << endl;

    return 0;
}