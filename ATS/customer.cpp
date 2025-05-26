#include "customer.hpp"
#include "commonfunc.hpp"
#include "modcsv.hpp"
#include <iostream>


using namespace std;

vector<string> Customer::getDetails() {
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

    return { name, username, email, password, getCurrentDateTime() };
}

void Customer::appendDetails() {
    vector<string> details = getDetails();

    writeCsvFile("customer_details.csv", { details }, true);
}