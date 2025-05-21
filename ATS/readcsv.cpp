#include "readcsv.hpp" 

using namespace std;

vector<vector<string>> readCsvFile(const string& filename) {
    vector<vector<string>> data;
    ifstream inputFile(filename);

    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            vector<string> row;
            stringstream ss(line);
            string field;

            while (getline(ss, field, ',')) {
                row.push_back(field);
            }
            data.push_back(row);
        }
        inputFile.close();
        cout << "Success." << endl;
    }
    else {
        cerr << "Error: Unable to open file." << endl;
    }
    return data;
}