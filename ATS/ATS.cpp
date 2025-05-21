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

int main() {
    vector<vector<string>> myData = {
       {"Bob", "25", "London"},
       {"Charlie", "35", "This is new"}
    };

    writeCsvFile("pw.csv", myData, true);

    vector<vector<string>> readData = readCsvFile("pw.csv");

    cout << "\n--- Read Data (with using namespace std;) ---\n";
    for (const auto& row : readData) {
        for (const auto& field : row) {
            cout << field << "\t";
        }
        cout << "\n";
    }

    return 0;
}