#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <random>
#include <regex>
#include <map>

#include "productadd_utils.hpp"
#include "employeeadd_utils.hpp"
#include "modcsv.hpp"
#include "userauthentication.hpp"
#include "commonfunc.hpp"
#include "adu.hpp"

using namespace std;

string generateRandomNumByTime() {
    string dateTime = getCurrentDateTime();

    string datePart = dateTime.substr(0, 10);
    string timePart = dateTime.substr(11, 8);

    datePart.erase(remove(datePart.begin(), datePart.end(), '-'), datePart.end());
    timePart.erase(remove(timePart.begin(), timePart.end(), ':'), timePart.end());

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 9);
    int random_number = dis(gen);

    ostringstream randn;
    randn << datePart << timePart << random_number;

    return randn.str();
}

bool isValidEmail(const std::string& email) {
    if (email.empty()) 
        return false;

    const regex pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return regex_match(email, pattern);
}

bool isValidPassword(const std::string& password) {
    if (password.length() < 6 || password.empty()) {
        return false;
    }

    bool hasUpper = false;
    bool hasDigit = false;

    for (char ch : password) {
        if (isupper(ch)) hasUpper = true;
        if (isdigit(ch)) hasDigit = true;
    }

    return hasUpper && hasDigit;
}

class Customer {
private:
    string name;
    string username;
    string email;
    string password;
    string joinedDate;
    string res;
public:
    vector<string> getDetails() {
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

        while (username.empty() && res != "q") {
            cout << "Username (must be unique): ";
            getline(cin, username);

            if (username.empty()) {
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

        return { name, username, email, password, getCurrentDateTime()};
    }

    bool appendDetails() {
        vector<string> details = getDetails();

        writeCsvFile("customer_details.csv", { details }, true);
        return true;
        
    }
};

int main() {
    vector<string> command;
    vector<string> userStatus = { "n", "" };

    command = getCommand();

    if (command[0] == "signup") {
        cout << "Please enter the details.\n" << endl;

        Customer c;

        c.appendDetails();
    }


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