#include "admin_.hpp"
#include "modcsv.hpp"
#include "commonfunc.hpp"
#include <iostream>

using namespace std;

vector<string> Admin::askDetails() {
    while (username.empty() && res != "q") {
        cout << "Name: ";
        getline(cin, username);
        username = trim(username);

        if (username.empty()) {
            cout << "Username cannot be empty. Press enter to type again or type 'q' to quit creating account." << endl;
            getline(cin, res);
        }

        if (res == "q")
            return { };
    }

    while (!isValidPassword(password) && res != "q") {
        cout << "Password (must be atleast 6 characters, must contain atleast one uppercase letter and one number): ";
        getline(cin, password);

        if (!isValidPassword(password)) {
            cout << "Password is not valid. Press enter to type again or type 'q' to quit creating account." << endl;
            getline(cin, res);
        }

        if (res == "q")
            return { };
    }

    return { username, password };
}

vector<string> Admin::appendDetails() {
    vector<string> details = askDetails();

    writeCsvFile(filePath, { details }, true);

    return details;
}


bool Admin::isUserExist(string username) {
    if (username.empty() || username == "")
        return false;

    vector<vector<string>> details = readCsvFile(filePath);
    int i = 0;

    for (i = 0; i < details.size(); i++) {
        if (username == details[i][0]) {
            return true;
            break;
        }
    }

    return false;
}

vector<string> Admin::getDetails(string username) {
    if (isUserExist(username)) {
        vector<vector<string>> details = readCsvFile(filePath);
        int i = 0;

        for (i = 0; i < details.size(); i++) {
            if (trim(username) == details[i][0]) {
                return { trim(details[i][0]), trim(details[i][1]) };
                break;
            }
        }
    }

    return {};
}
