#include "commonfunc.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <random>
#include <algorithm>

using namespace std;

string getCurrentDateTime() {
    auto now = chrono::system_clock::now();

    time_t now_c = chrono::system_clock::to_time_t(now);

    ostringstream oss;

    struct tm buf;
    localtime_s(&buf, &now_c);
    oss << put_time(&buf, "%Y-%m-%d %H:%M:%S");

    return oss.str();
}

vector<string> getCommand() {
    string command;
    getline(cin, command);

    if (command.empty())
        return { "" };

    istringstream iss(command);
    string word;
    vector<string> words;

    while (iss >> word) {
        words.push_back(word);
    }

    return words;
}

string trim(const string& s) {
    if (s.empty())
        return "";

    auto start = find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !isspace(ch);
        });

    auto end = find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !isspace(ch);
        }).base();

    return (start < end) ? string(start, end) : "";
}

void displayTable(const vector<vector<string>>& data) {
    if (data.empty()) {
        cout << "Empty table." << endl;
        return;
    }

    size_t numCols = 0;
    for (const auto& row : data) {
        numCols = max(numCols, row.size());
    }

    vector<size_t> colWidths(numCols, 0);
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            colWidths[i] = max(colWidths[i], row[i].length());
        }
    }

    for (size_t r = 0; r < data.size(); ++r) {
        for (size_t c = 0; c < numCols; ++c) {
            string cell = (c < data[r].size()) ? data[r][c] : "";
            cout << left << setw(colWidths[c] + 2) << cell;
        }
        cout << endl;

        if (r == 0) {
            for (size_t c = 0; c < numCols; ++c) {
                cout << string(colWidths[c] + 2, '*');
            }
            cout << endl;
        }
        else {
            for (size_t c = 0; c < numCols; ++c) {
                cout << string(colWidths[c] + 2, '-');
            }
            cout << endl;
        }
    }
}

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

bool isValidEmail(const string& email) {
    if (email.empty())
        return false;

    const regex pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return regex_match(email, pattern);
}

bool isValidNZMobileNumber(const string& number) {
    regex localFormat("^02[0-9]{7,8}$");
    regex internationalFormat("^\\+642[0-9]{7,8}$");

    return regex_match(number, localFormat) || regex_match(number, internationalFormat);
}

bool isValidPassword(const string& password) {
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

bool isValidGender(const string& gender) {
    return ("m" == gender || "f" == gender) && !gender.empty();
}

bool isNumber(const string& str) {
    if (str.empty() || std::all_of(str.begin(), str.end(), ::isspace)) {
        return false;
    }

    istringstream iss(str);
    double d;
    char c;
    return (iss >> d) && !(iss >> c);
}

bool isWholeNumber(const string& str) {
    if (str.empty()) return false;

    if (str[0] == '-') return false;

    size_t start = (str[0] == '+') ? 1 : 0;

    if (start == str.length()) return false;

    return all_of(str.begin() + start, str.end(), ::isdigit);
}

void printTable(const vector<vector<string>>& table, int sortByColumn, bool ascending) {
    if (table.empty()) return;

    size_t numCols = 0;
    for (const auto& row : table)
        numCols = max(numCols, row.size());

    vector<vector<string>> sortedTable = table;

    if (sortByColumn >= 0 && sortByColumn < numCols) {
        sort(sortedTable.begin() + 1, sortedTable.end(), [&](const vector<string>& a, const vector<string>& b) {
            string valA = (sortByColumn < a.size()) ? a[sortByColumn] : "";
            string valB = (sortByColumn < b.size()) ? b[sortByColumn] : "";
            return ascending ? (valA < valB) : (valA > valB);
            });
    }

    vector<size_t> colWidths(numCols, 0);
    for (const auto& row : sortedTable)
        for (size_t i = 0; i < row.size(); ++i)
            colWidths[i] = max(colWidths[i], row[i].length());

    auto printBorder = [&]() {
        cout << "+";
        for (auto width : colWidths)
            cout << string(width + 2, '-') << "+";
        cout << '\n';
        };

    auto printRow = [&](const vector<string>& row) {
        cout << "|";
        for (size_t i = 0; i < numCols; ++i) {
            string cell = (i < row.size()) ? row[i] : "";
            cout << " " << left << setw(colWidths[i]) << cell << " |";
        }
        cout << '\n';
        };

    printBorder();
    bool isHeader = true;
    for (const auto& row : sortedTable) {
        printRow(row);
        if (isHeader) {
            printBorder();
            isHeader = false;
        }
    }
    printBorder();
}