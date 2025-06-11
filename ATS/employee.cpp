#include "employee.hpp"
#include "commonfunc.hpp"
#include "modcsv.hpp"
#include <iostream>
#include <map>

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

void Employee::deleteUser(string employeeId) {
    if (getDetails(employeeId).empty())
        cout << "Employee not found." << endl;
    else
        deleteDetails(filePath, 0, employeeId);
}

vector<vector<string>> Employee::getUsers() {
    return readCsvFile(filePath);
}


vector<vector<string>> Employee::getEmployeesByPosition(string position) {
    vector<vector<string>> filtered, output = readCsvFile(filePath);

    for (const auto& row : output) {
        if (row.size() > 2 && (row[2] == position || filtered.size() == 0)) {
            filtered.push_back(row);
        }
    }

    return filtered;
}

bool Employee::isRosterExist(string employeeId) {
    if (employeeId.empty() || employeeId == "")
        return false;

    vector<vector<string>> details = readCsvFile(rosterPath);
    int i = 0;

    for (i = 0; i < details.size(); i++) {
        if (employeeId == details[i][0]) {
            return true;
            break;
        }
    }

    return false;
}

void Employee::addRoster(string employeeId) {
    if (!getDetails(employeeId).empty()) {
        if (!isRosterExist(employeeId)) {
            vector<string> days = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
            vector<string> shifts;
            string payRate = "0";

            cout << "Pay rate (per hour): ";
            cin >> payRate;
            cin.ignore();

            cout << "\nLeave blank for no shift." << endl;

            for (int i = 0; i < days.size(); i++) {
                string start, end;
                cout << "\n" << days[i] << ":" << endl;
                cout << "Start: ";
                getline(cin, start);

                if (!start.empty()) {
                    cout << "End: ";
                    getline(cin, end);
                    shifts.push_back(trim(start) + "-" + trim(end));
                }
                else {
                    shifts.push_back("-");
                }
            }

            shifts.insert(shifts.begin(), payRate);
            shifts.insert(shifts.begin(), employeeId);
            writeCsvFile(rosterPath, { shifts }, true);
        }
        else {
            cout << "Employee's roster already exists." << endl;
            cout << "Type update roster for updating roster." << endl;
        }
    }
    else {
        cout << "Employee doesn't exists." << endl;
    }
}

vector<vector<string>> Employee::getRosters() {
    return readCsvFile(rosterPath);
}

bool Employee::updateRosters(string employeeId) {
    if (!getDetails(employeeId).empty()) {
        if (isRosterExist(employeeId)) {
            vector<string> days = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
            vector<string> shifts;
            string payRate;

            cout << "Leave blank to make value as it is." << endl;
            cout << "Type d to delete the roster." << endl;

            cout << "Pay rate (per hour): ";
            cin >> payRate;
            cin.ignore();

            cout << "\nLeave blank for leaving roster as it is." << endl;

            for (int i = 0; i < days.size(); i++) {
                string start, end;
                cout << "\n" << days[i] << ":" << endl;
                cout << "Start: ";
                getline(cin, start);
                
                if (trim(start) == "d") {
                    shifts.push_back("-");
                } else if (start.empty()) {
                    shifts.push_back("");
                }
                else {
                    cout << "End: ";
                    getline(cin, end);
                    shifts.push_back(trim(start) + "-" + trim(end));
                }
            }

            shifts.insert(shifts.begin(), payRate);
            shifts.insert(shifts.begin(), employeeId);

            updateDetails(rosterPath, 0, trim(employeeId), { shifts });
            return true;
        }
        else {
            cout << "Employee's roster does not exists." << endl;
            cout << "Type add roster for adding roster." << endl;
        }
    }
    else {
        cout << "Employee doesn't exists." << endl;
        return false;
    }
}

void Employee::deleteRoster(string employeeId) {
    if (getDetails(employeeId).empty())
        cout << "Employee not found." << endl;
    else
        if (isRosterExist(employeeId))
            deleteDetails(rosterPath, 0, employeeId);
        else
            cout << "Roster not found." << endl;
}

void Employee::clear() {
    employeeId.clear();
    name.clear();
    position.clear();
    email.clear();
    contactNum.clear();
    gender.clear();
    address.clear();
    joinedDate.clear();
    res.clear();
}