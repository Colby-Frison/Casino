#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    FILE* file;
    string name;
    string fileName = "Users/";

    cout << "Enter Name: ";
    cin >> name;
    cout << endl;

    fileName += name;
    fileName += ".txt";

    file = fopen(fileName.c_str(), "r");

    if (file!=NULL)
    {
        // printing the success message
        cout << "File exists" << endl;
    }
    else
    {
        // printing the error message
        cout << "File does not exists" << endl;
    }

    return 0;
}