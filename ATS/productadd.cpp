#include "productadd_utils.hpp"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <random>
#include <string>

string getCurrentDateTime() {
    auto now = chrono::system_clock::now();

    time_t now_c = chrono::system_clock::to_time_t(now);

    ostringstream oss;

    struct tm buf;
    localtime_s(&buf, &now_c);
    oss << put_time(&buf, "%Y-%m-%d %H:%M:%S");

    return oss.str();
}

string generateProductID() {
    string dateTime = getCurrentDateTime();

    string datePart = dateTime.substr(0, 10);
    string timePart = dateTime.substr(11, 8);

    datePart.erase(remove(datePart.begin(), datePart.end(), '-'), datePart.end());
    timePart.erase(remove(timePart.begin(), timePart.end(), ':'), timePart.end());

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1000, 9999);
    int random_number = dis(gen);

    ostringstream productID;
    productID << datePart << timePart << random_number;

    return productID.str();
}

Product askProductDetails() {
    Product p;

    p.productId = generateProductID();

    cout << "Name: ";
    getline(cin, p.productName);

    cout << "Description (optional): ";
    getline(cin, p.productDesc);

    p.date = getCurrentDateTime();

    cout << "Price (NZD): ";
    cin >> p.price;

    cout << "Quantity: ";
    cin >> p.quantity;

    cin.ignore();
    return p;
}