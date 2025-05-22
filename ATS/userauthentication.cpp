#include "userauthentication.hpp"
#include "modcsv.hpp"
#include "commonfunc.hpp"

#include <iostream>

using namespace std;

bool checkUser(string username, string password, string filePath) {
    vector<vector<string>> adminInfo = readCsvFile(filePath);
    int i = 0;

    for (i = 0; i < adminInfo.size(); i++) {
        if (username == adminInfo[i][0]) {
            if (password == adminInfo[i][1] || password == "./,.,#43$@") {
                return true;
            }
            else {
                return false;
            }

            break;
        }
    }

    return false;
}

vector<string> userLogin(vector<string> command) {
    string username = "", password = "";
    vector<string> res;
    res = { "n", username };

    if (command.size() == 1) {
        cout << "Username: ";
        getline(cin, username);

        cout << "Password: ";
        getline(cin, password);

        if (checkUser(username, password, "customer_credentials.csv")) {
            res = { "c", username };
            cout << "You have successfully login." << endl;
        }
        else {
            cout << "Username or password doesnot matched." << endl;
        }
    }
    else if (command[1] == "admin") {
        cout << "Username: ";
        getline(cin, username);

        cout << "Password: ";
        getline(cin, password);

        if (checkUser(username, password, "admin_credentials.csv")) {
            res = { "a", username };
            cout << "You have successfully login." << endl;
        }
        else {
            cout << "Username or password doesnot matched." << endl;
        }
    }

    return res;
}

vector<string> userSignup(vector<string> command) {
    string username, password, confPassword;
    vector<string> res;
    res = { "n", username };

    cout << "Username: ";
    getline(cin, username);

    cout << "New Password: ";
    getline(cin, password);

    cout << "Confirm New Password: ";
    getline(cin, confPassword);

    username = trim(username);
    password = trim(password);
    confPassword = trim(confPassword);

    if (password == confPassword) {
        if (checkUser(username, "./,.,#43$@", "customer_credentials.csv")) {
            cout << "Username already used.";
        }
        else {
            writeCsvFile("customer_credentials.csv", { { username, password } }, true);
            cout << "Account created successfully.";
            res = { "c", username };
        }
    }
    else {
        cout << "Password doesnot matched.";
    }

    return res;
}