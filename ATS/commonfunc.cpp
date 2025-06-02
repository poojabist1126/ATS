#include "commonfunc.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <random>

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