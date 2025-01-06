#pragma once

#include <string>

class Player {
    public: 
        std::string user; // username
        int chips = -1; // number of chips available
        bool userSelected = false; // is there a user selected, doesnt make since for first user selection, but when switching between users its nice
        std::string playing; // stores what game is being played

    bool yesCheck(std::string input);

    void pickUser();

    void save();


};


// Header files seem to be working just have to reimplement functions in porper files and add proper functions to the correct headers
// also need to rewrite some of the functions to work with the Player class