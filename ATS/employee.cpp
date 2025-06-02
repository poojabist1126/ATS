#include "employee.hpp"
#include "commonfunc.hpp"
#include "modcsv.hpp"
#include <iostream>

using namespace std;

vector<string> Employee::askDetails() {
    while (name.empty() && res != "q") {
        cout << "Name: ";
        getline(cin, name);
        name = trim(name);

        if (name.empty()) {
            cout << "Name cannot be empty. Press enter to type again or type 'q' to quit." << endl;
            getline(cin, res);
        }

        if (res == "q")
            return { };
    }

    while (position.empty() && res != "q") {
        cout << "Position: ";
        getline(cin, position);
        position = trim(position);

        if (position.empty()) {
            cout << "Position cannot be empty. Press enter to type again or type 'q' to quit." << endl;
            getline(cin, res);
        }

        if (res == "q")
            return { };
    }

    while (!isValidEmail(email) && res != "q") {
        cout << "Email: ";
        getline(cin, email);
        email = trim(email);

        if (!isValidEmail(email)) {
            cout << "Email is not valid. Press enter to type again or type 'q' to quit." << endl;
            getline(cin, res);
        }

        if (res == "q")
            return { };
    }

    while (!isValidNZMobileNumber(contactNum) && res != "q") {
        cout << "Contact Number: ";
        getline(cin, contactNum);
        contactNum = trim(contactNum);

        if (!isValidNZMobileNumber(contactNum)) {
            cout << "Contact Number is not valid. Press enter to type again or type 'q' to quit." << endl;
            getline(cin, res);
        }

        if (res == "q")
            return { };
    }

    while (address.empty() && res != "q") {
        cout << "Address: ";
        getline(cin, address);
        address = trim(address);

        if (address.empty()) {
            cout << "Address cannot be empty. Press enter to type again or type 'q' to quit." << endl;
            getline(cin, res);
        }

        if (res == "q")
            return { };
    }

    while (!isValidGender(gender) && res != "q") {
        cout << "Gender (m/f/n): ";
        getline(cin, gender);
        gender = trim(gender);

        if (!isValidGender(gender)) {
            cout << "Gender is not valid. Press enter to type again or type 'q' to quit." << endl;
            getline(cin, res);
        }

        if (res == "q")
            return { };
    }

    employeeId = "E" + generateRandomNumByTime();

    cout << "Thanks for the details.\n" << endl;
    return { employeeId, name, position, email, contactNum, address, gender, getCurrentDateTime() };
}

vector<string> Employee::appendDetails() {
    vector<string> details = askDetails();

    writeCsvFile(filePath, { details }, true);

    return details;
}

bool Employee::isUserExist(string employeeId) {
    if (employeeId.empty() || employeeId == "")
        return false;

    vector<vector<string>> details = readCsvFile(filePath);
    int i = 0;

    for (i = 0; i < details.size(); i++) {
        if (employeeId == details[i][0]) {
            return true;
            break;
        }
    }

    return false;
}
vector<string> Employee::getDetails(string employeeId) {
    if (isUserExist(employeeId)) {
        vector<vector<string>> details = readCsvFile(filePath);
        int i = 0;

        for (i = 0; i < details.size(); i++) {
            if (trim(employeeId) == details[i][0]) {
                return { details[i][0], details[i][1], details[i][2], details[i][3], details[i][4], details[i][5], details[i][6], details[i][7] };
                break;
            }
        }
    }

    return {};
}

bool Employee::updateUserDetails(string employeeId) {
    cout << "Name: ";
    getline(cin, name);

    cout << "Position: ";
    getline(cin, position);

    while (!isValidEmail(email) && res != "q") {
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

    while (!isValidNZMobileNumber(contactNum) && res != "q") {
        cout << "Contact Number: ";
        getline(cin, contactNum);

        if (contactNum.empty())
            break;

        if (!isValidNZMobileNumber(contactNum)) {
            cout << "Contact Number is not valid. Press enter to type again or type 'q' to quit updating details." << endl;
            getline(cin, res);
        }

        if (res == "q")
            return { };
    }

    cout << "Address: ";
    getline(cin, address);

    while (!isValidGender(gender) && res != "q") {
        cout << "Gender (m/f/n): ";
        getline(cin, gender);

        if (gender.empty())
            break;

        if (!isValidGender(gender)) {
            cout << "Gender is not valid. Press enter to type again or type 'q' to quit." << endl;
            getline(cin, res);
        }

        if (res == "q")
            return { };
    }


    updateDetails(filePath, 0, trim(employeeId), { { "", trim(name), trim(position), trim(email), trim(contactNum), trim(address), trim(gender), ""} });
    return true;
}

vector<vector<string>> Employee::getUsers() {
    return readCsvFile(filePath);
}