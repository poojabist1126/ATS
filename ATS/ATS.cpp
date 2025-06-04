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
#include "employee.hpp"
#include "admin_.hpp"
#include "product.hpp"

using namespace std;

void userAuthentication(map<string, string>& user, vector<string> command) {
    if (command[0] == "signup") {
        if (user["username"] == "") {
            cout << "Please enter the details.\n" << endl;

            Customer c;

            vector<string> details = c.appendDetails();

            user["username"] = details[1];
            user["type"] = "c";

            cout << "Congratulations, " + details[0] + " you have successfully created account as " + user["username"] + "." << endl;
        }
        else {
            cout << "You have to logout first." << endl;
        }
    }
    else if (command[0] == "login") {
        if (user["username"] == "") {
            if (command.size() == 1) {
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
            else if (command[1] == "admin") {
                Admin a;
                string username, password;
                vector<string> details;

                cout << "Username: ";
                getline(cin, username);

                if (a.isUserExist(username)) {
                    cout << "Password: ";
                    getline(cin, password);

                    details = a.getDetails(username);
                    if (details[1] == trim(password)) {
                        user["username"] = trim(username);
                        user["type"] = "a";

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
        }
        else {
            cout << "You have to logout first." << endl;
        }

    }
}

bool checkUser(map<string, string> user, string commandOf = "") {
    if (user["username"] == "" && user["type"] == "") {
        cout << "You are not logged in." << endl;
        cout << "To log in, type: 'login'." << endl;
        cout << "To create an account, type: 'signup'." << endl;
        cout << "To view available commands, type: 'help'." << endl;
        return false;
    }
    else if (user["username"] != "" && user["type"] == "c" && commandOf == "a") {
        cout << "Must be loggedIn as admin." << endl;
        return false;
    }
    return true;
}

int main() {
    vector<string> command;
    map<string, string> user = { {"username", ""}, {"type", ""} };
    Customer c;
    Admin a;

    cout << "Welcome to Aotearoa Treasures’ inventory management system\n" << endl;

    cout << "Please login to use this software. If you don't have account, please create one." << endl;
    cout << "Type 'login' to login." << endl;
    cout << "Type 'signup' to create account.\n" << endl;

    cout << "If you want to see list of commands, please type 'help'.\n" << endl;

    do {
        cout << ">>> ";
        command = getCommand();

        userAuthentication(user, command);
        
        if (command[0] == "logout" && checkUser(user, "")) {
            user["username"] = "";
            user["type"] = "";

            cout << "Logout successful." << endl;
        }

        if (command[0] == "admin" && checkUser(user, "a")) {
            cout << "Successful." << endl;
        }

    } while (command[0] != "exit");


    return 0;
}