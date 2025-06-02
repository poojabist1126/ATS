#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <random>
#include <regex>
#include <map>

#include "modcsv.hpp"
#include "commonfunc.hpp"
#include "customer.hpp"

using namespace std;

int main() {
    vector<string> command;
    map<string, string> user = { {"username", ""}, {"type", ""} };

    cout << "Welcome to Aotearoa Treasures’ inventory management system\n" << endl;

    cout << "Please login to use this software. If you don't have account, please create one." << endl;
    cout << "Type 'login' to login." << endl;
    cout << "Type 'signup' to create account.\n" << endl;

    cout << "If you want to see list of commands, please type 'help'.\n" << endl;

    do {
        cout << ">>> ";
        command = getCommand();

        if (command[0] == "signup") {
            cout << "Please enter the details.\n" << endl;

            Customer c;

            vector<string> details = c.appendDetails();

            user["username"] = details[1];
            user["type"] = "c";

            cout << "Congratulations, " + details[0] + " you have successfully created account as " + user["username"] + "." << endl;
        }
        else if (command[0] == "login") {
            Customer c;
            string username, password;
            vector<string> details;

            cout << "Username: ";
            getline(cin, username);

            if (c.isUserExist(username)) {
                cout << "Password: ";
                getline(cin, password);

                details = c.getDetails(username);
                if (details[3] == trim(password)) {
                    user["username"] = trim(username);
                    user["type"] = "c";

                    cout << "Welcome " << details[0] << ", login successful." << endl;
                }
                else {
                    cout << "Login failed. Password doesn't matched." << endl;
                }
            }
            else {
                cout << "User doesn't exists, please enter valid username. If you don't have account please signup.\nTo signup, please type 'signup'. Thank You" << endl;
            }
        }


        if (command[0] == "update" && command[1] == "pinfo") {
            if (user["type"] == "c") {
                cout << "Fill the information, you want to update. Leave Blank to leave it as it was.\nYou can't change username.\n" << endl;

                Customer c;

                if (c.updateUserDetails(user["username"])) {
                    cout << user["username"] << " you details are updated successfully." << endl;
                }
                else {
                    cout << "Update failed." << endl;
                }
            }
            else {
                cout << "Please login first." << endl;
            }
        }


    } while (command[0] != "exit");

    
    //if (command[0] == "login") {
    //    if (command.size() > 1)
    //        userStatus = userLogin(command);
    //    else
    //        cout << "Please enter a valid command. To check valid commands, type 'help'." << endl;
    //}
    //else if (command[0] == "signup") {
    //    userStatus = userSignup();
    //}
    //else if (command[0] == "update") {
    //    if(command.size() > 1)
    //        updateDetails(command);
    //    else
    //        cout << "Please enter a valid command. To check valid commands, type 'help'." << endl;
    //}
    //else if (command[0] == "add") {
    //    if (command.size() > 1)
    //        addDetails(command);
    //    else
    //        cout << "Please enter a valid command. To check valid commands, type 'help'." << endl;
    //}
    //else if (command[0] == "delete") {
    //    if (command.size() > 1)
    //        deleteDetails(command);
    //    else
    //        cout << "Please enter a valid command. To check valid commands, type 'help'." << endl;
    //}
    //else if (command[0] == "show") {
    //    if (command.size() > 1 && (command[1] == "product" || command[1] == "employee"))
    //        displayTable(readCsvFile(command[1] + "_details.csv"));
    //    else
    //        cout << "Please enter a valid command. To check valid commands, type 'help'." << endl;
    //}
    //else if (command[0] == "help") {
    //    ifstream inputFile("help.txt");
    //    string line;

    //    if (inputFile.is_open()) {
    //        while (getline(inputFile, line)) {
    //            cout << line << endl;
    //        }
    //        inputFile.close();
    //    }
    //    else {
    //        cerr << "Unable to open file" << endl;
    //    }

    //}

    return 0;
}