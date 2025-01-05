#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

string user;
int chips = -1;
int roundNum = 0;
bool userSelected = false;

// default for gameloop function so it can be called in the option function
void gameLoop();

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
void pickUser(){
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
    cout << "Chips available: " << chips << endl << endl;
}

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
void option(bool third){
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
        userSelected = false;

        cout << "Enter user: ";
        cin >> user;
        cout << endl;
        pickUser();

    }
    else if(input == "2") {
        // exit game;
        return;
    }
    else if(third && input == "3") {
        cout << "Starting game: " << endl;

        rules();
        gameLoop();
    }
    else {
        cout << "Please choose valid option";
        option(third);
    }
}

void gameLoop(){
    system("clear");
    int bet = -1;
    if(chips > 1){
        cout << "Place a bet 1 - " << chips << ": ";
        cin >> bet;
    }
    else if(chips == 1){
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
                return;
            }
            else if(input == "3") {
                cout << "Picking new user: " << endl;
                userSelected = false;

                cout << "Enter user: ";
                cin >> user;
                cout << endl;
                pickUser();
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

        option(false);
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
            chips += bet * 2;

            cout << endl << "Current balance is now: " <<  chips << endl;

        }
        else if(stoi(guess) == num + 1 || stoi(guess) == num - 1 ) {
            cout << "You have guessed one away from the number so you don't lose any chips" << endl;


            cout << endl << "Current balance is now: " <<  chips << endl;

        }
        else {
            cout << "You have guessed incorectly, so you have lost " << bet << " chips" << endl << endl;

            chips -= bet;
            if(chips == 1){
                cout << "You only have one chip left spend it carefully" << endl;
            }
            else if(chips == 0) {
                if(num % 2 == 0) {
                    cout << "You have no more chips, maybe its time to call it" << endl;
                }
                else {
                    cout << "You have no more chips please exit or choose a new profile" << endl;
                }
            }
            else {
                cout << "You now have " << chips << " chips left, spend them carefully" << endl << endl;
            }
        }

        if(chips >= 1){
            cout << "Play again? [y/n] ";

            string input;
            cin >> input;
            if(yesCheck(input)){ 
                gameLoop();
            }
            else{
                option(true);
            }
        }
        else {
            cout << "Please choose one of the following options:" << endl;
            option(false);
        }
    }
}

void start(){
    if(userSelected) {// if user us selected enter game loop
        string input;

        cout << "Start game? [y/n] ";
        cin >> input;
        cout << endl;

        if(yesCheck(input)){
            rules();
            gameLoop();
        }
        else {
            option(true);
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