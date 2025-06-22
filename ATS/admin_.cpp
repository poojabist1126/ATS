#include "admin_.hpp"
#include "modcsv.hpp"
#include "commonfunc.hpp"
#include <iostream>

using namespace std;

vector<string> Admin::askDetails() {
    // the while loop loops until a certian function is not met
    // if typed q whole function gets terminated

    while (isUserExist(username) && res != "q") {
        cout << "Name: ";
        getline(cin, username);
        username = trim(username);

        if (isUserExist(username)) {
            cout << "Username cannot be empty or Username already exists. Press enter to type again or type 'q' to quit creating account." << endl;
            getline(cin, res);
        }

        if (res == "q")
            return { };
    }

    while ((!isUserEmployee(employeeId) || isUserEmployeeIdExist(employeeId)) && res != "q") {
        cout << "Employee Id: ";
        getline(cin, employeeId);
        employeeId = trim(employeeId);

        if ((!isUserEmployee(employeeId) || isUserEmployeeIdExist(employeeId))) {
            cout << "Employee Id is not registered as employee or admin with this employee id is already registered. Press enter to type again or type 'q' to quit creating account." << endl;
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

    return { username, employeeId, password };
}

vector<string> Admin::appendDetails() {
    vector<string> details = askDetails();

    writeCsvFile(filePath, { details }, true); // appends details in admin csv file

    return details;
}

bool Admin::isUserEmployee(string employeeId) {
    if (employeeId.empty() || employeeId == "")
        return false;

    vector<vector<string>> details = readCsvFile("employee_details.csv"); // reads admin csv file
    int i = 0;

    for (i = 0; i < details.size(); i++) {
        // details[i][0] means admin username
        if (employeeId == details[i][0]) {
            return true;
            break;
        }
    }

    return false;
}


bool Admin::isUserEmployeeIdExist(string employeeId) {
    if (employeeId.empty() || employeeId == "")
        // checks for the value of the parameter
        return true; // return true in empty parameter because of some function 

    vector<vector<string>> details = readCsvFile(filePath); // reads admin csv file
    int i = 0;

    for (i = 0; i < details.size(); i++) {
        // details[i][0] means admin employeeId
        if (employeeId == details[i][1]) {
            return true;
            break;
        }
    }

    return false;
}

bool Admin::isUserExist(string username) {
    if (username.empty() || username == "")
        // checks for the value of the parameter
        return true; // return true in empty parameter because of some function 

    vector<vector<string>> details = readCsvFile(filePath); // reads admin csv file
    int i = 0;

    for (i = 0; i < details.size(); i++) {
        // details[i][0] means admin username
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
                return { trim(details[i][0]), trim(details[i][1]), trim(details[i][2]) }; // returns username and password if the user exists
                break;
            }
        }
    }

    return {};
}

void Admin::clear() {
    // clears every variables
    username.clear();
    employeeId.clear();
    password.clear();
    res.clear();
}
