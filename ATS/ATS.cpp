#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "productadd_utils.hpp"
#include "employeeadd_utils.hpp"
#include "modcsv.hpp"
#include "userauthentication.hpp"
#include "commonfunc.hpp"
#include "adu.hpp"

using namespace std;

int main() {
    vector<string> command;
    vector<string> userStatus = { "n", "" };

    command = getCommand();

    if (command[0] == "login") {
        if (command.size() > 1)
            userStatus = userLogin(command);
        else
            cout << "Please enter a valid command. To check valid commands, type 'help'." << endl;
    }
    else if (command[0] == "signup") {
        userStatus = userSignup();
    }
    else if (command[0] == "update") {
        if(command.size() > 1)
            updateDetails(command);
        else
            cout << "Please enter a valid command. To check valid commands, type 'help'." << endl;
    }
    else if (command[0] == "add") {
        if (command.size() > 1)
            addDetails(command);
        else
            cout << "Please enter a valid command. To check valid commands, type 'help'." << endl;
    }
    else if (command[0] == "delete") {
        if (command.size() > 1)
            deleteDetails(command);
        else
            cout << "Please enter a valid command. To check valid commands, type 'help'." << endl;
    }
    else if (command[0] == "show") {
        if (command.size() > 1 && (command[1] == "product" || command[1] == "employee"))
            displayTable(readCsvFile(command[1] + "_details.csv"));
        else
            cout << "Please enter a valid command. To check valid commands, type 'help'." << endl;
    }
    else if (command[0] == "help") {
        ifstream inputFile("help.txt");
        string line;

        if (inputFile.is_open()) {
            while (getline(inputFile, line)) {
                cout << line << endl;
            }
            inputFile.close();
        }
        else {
            cerr << "Unable to open file" << endl;
        }

    }

    return 0;
}