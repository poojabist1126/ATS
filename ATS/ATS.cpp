#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "productadd_utils.hpp"
#include "employeeadd_utils.hpp"

using namespace std;

int main() {
    vector<Product> products;

    string command;

    bool productAddValid = true;

    cout << "Enter command: ";
    getline(cin, command);

    istringstream iss(command);
    string word;
    vector<string> words;

    while (iss >> word) {
        words.push_back(word);
    }

    if (words[0] == "add") {
        if (words[1] == "product") {
            askProductDetails();
        }
        else if (words[1] == "employee") {
            askEmployeeDetails();
        }
    }

    return 0;
}