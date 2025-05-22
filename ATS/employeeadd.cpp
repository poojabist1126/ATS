#include "employeeadd_utils.hpp"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <random>
#include <string>


string generateEmployeeId() {
    string dateTime = getCurrentDateTime();

    string datePart = dateTime.substr(0, 10);
    string timePart = dateTime.substr(11, 8);

    datePart.erase(remove(datePart.begin(), datePart.end(), '-'), datePart.end());
    timePart.erase(remove(timePart.begin(), timePart.end(), ':'), timePart.end());

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 9);
    int random_number = dis(gen);

    ostringstream employeeID;
    employeeID << datePart << '_' << timePart << '_' << random_number;

    return employeeID.str();
}

Employee askEmployeeDetails() {
    Employee emp;

    emp.id = generateEmployeeId();

    cout << "Name: ";
    getline(cin, emp.name);

    cout << "Position: ";
    getline(cin, emp.position);

    cout << "Gender (m/f): ";
    getline(cin, emp.gender);

    cout << "Date of Birth (YYYY-MM-DD): ";
    getline(cin, emp.DOB);

    emp.joinedDate = getCurrentDateTime();

    cin.ignore();
    return emp;
}