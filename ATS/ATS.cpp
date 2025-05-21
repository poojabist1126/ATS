#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "productadd_utils.hpp"
#include "employeeadd_utils.hpp"

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

int main() {
    vector<string> command;
    command = getCommand();
    

    return 0;
}