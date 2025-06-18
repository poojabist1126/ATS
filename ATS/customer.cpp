#include "customer.hpp"
#include "commonfunc.hpp"
#include "modcsv.hpp"
#include <iostream>

using namespace std;

vector<string> Customer::askDetails() {
    // the while loop loops until a certain function is not met
    // if typed q whole function gets terminated

    while (name.empty() && res != "q") {
        cout << "Name: ";
        getline(cin, name);

        if (name.empty()) {
            cout << "Name cannot be empty. Press enter to type again or type 'q' to quit creating account." << endl;
            getline(cin, res);
        }

        if (res == "q")
            return { };
    }

    while (!isValidEmail(email) && res != "q") {
        cout << "Email: ";
        getline(cin, email);

        if (!isValidEmail(email)) {
            cout << "Email is not valid. Press enter to type again or type 'q' to quit creating account." << endl;
            getline(cin, res);
        }

        if (res == "q")
            return { };
    }

    cout << "Thanks for the details.\n" << endl;

    while (res != "q" && isUserExist(username)) {
        cout << "Username (must be unique): ";
        getline(cin, username);

        if (isUserExist(username)) {
            cout << "Username not valid. Press enter to type again or type 'q' to quit creating account." << endl;
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

    return { name, username, email, password, getCurrentDateTime() };
}

vector<string> Customer::appendDetails() {
    vector<string> details = askDetails();

    writeCsvFile(filePath, { details }, true); // appends details to customer_details.csv file

    return details;
}

bool Customer::isUserExist(string username) {
    if (username.empty() || username == "")
        // checks if the username is empty or not
        return true;

    vector<vector<string>> details = readCsvFile(filePath); // read customer.csv file
    int i = 0;

    for (i = 0; i < details.size(); i++) {
        if (username == details[i][1]) {
            // checks for the specific user, if found returns true
            return true;
            break;
        }
    }

    return false;
}

vector<string> Customer::getDetails(string username) {
    if (isUserExist(username)) {
        vector<vector<string>> details = readCsvFile(filePath); // reads customer.csv file
        int i = 0;

        for (i = 0; i < details.size(); i++) {
            if (trim(username) == details[i][1]) {
                // if the username is matched returns customer details
                return {trim(details[i][0]), trim(details[i][1]), trim(details[i][2]), trim(details[i][3]), trim(details[i][4]) };
                break;
            }
        }
    }

    return {}; // returns empty 
}

bool Customer::updateUserDetails(string username) {
    // the while loop loops until a certain function is not met
    // if typed q whole function gets terminated
    // if left blanks the specific one is skipped

    cout << "Name: ";
    getline(cin, name);

    while (!isValidEmail(email) && res != "q" ) {
        cout << "Email: ";
        getline(cin, email);

        if (email.empty())
            break; 

        if (!isValidEmail(email)) {
            cout << "Email is not valid. Press enter to type again or type 'q' to quit updating details." << endl;
            getline(cin, res);
        }

        if (res == "q")
            return false;
    }
    
    while (!isValidPassword(password) && res != "q") {
        cout << "Password (must be atleast 6 characters, must contain atleast one uppercase letter and one number): ";
        getline(cin, password);

        if (password.empty())
            break;

        if (!isValidPassword(password)) {
            cout << "Password is not valid. Press enter to type again or type 'q' to quit updating details." << endl;
            getline(cin, res);
        }

        if (res == "q")
            return { };
    }

    updateDetails(filePath, 1, trim(username), { trim(name), trim(username), trim(email), trim(password), "" }); // if parameter is empty the value doesnot change
    return true;
}

void Customer::deleteUser(string username) {
    if (getDetails(username).empty())
        cout << "Customer not found." << endl;
    else
        deleteDetails(filePath, 1, username); // removes the user details from the csv file
}

void Customer::clear() {
    // clears every variables
    name.clear();
    username.clear();
    email.clear();
    password.clear();
    joinedDate.clear();
    res.clear();
}
