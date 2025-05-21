#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "productadd_utils.hpp"
#include "employeeadd_utils.hpp"
#include "readcsv.hpp"
#include "writecsv.hpp"

using namespace std;

vector<string> getCommand() {
    string command;
    getline(cin, command);

    istringstream iss(command);
    string word;
    vector<string> words;

    while (iss >> word) {
        words.push_back(word);
    }

    return words;
}

bool checkUser(string username, string password, string filePath) {
    vector<vector<string>> adminInfo = readCsvFile(filePath);
    int i = 0;

    for (i = 0; i < adminInfo.size(); i++) {
        if (username == adminInfo[i][0]) {
            if (password == adminInfo[i][1]) {
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

vector<string> userStatusFunc(vector<string> command) {
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
        }
    }
    else if (command[1] == "admin") {
        cout << "Username: ";
        getline(cin, username);

        cout << "Password: ";
        getline(cin, password);

        if (checkUser(username, password, "admin_credentials.csv")) {
            res = { "a", username };
        }
    }

    return res;
}

int main() {
    vector<string> command;
    vector<string> userStatus;

    command = getCommand();

    if (command[0] == "login") {
        userStatus = userStatusFunc(command);
    }


    return 0;
}