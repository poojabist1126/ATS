#include "productadd_utils.hpp"
#include "commonfunc.hpp"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <random>
#include <string>

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
    p.productName = trim(p.productName);

    cout << "Description (optional): ";
    getline(cin, p.productDesc);
    p.productDesc = trim(p.productDesc);

    p.date = getCurrentDateTime();

    cout << "Price (NZD): ";
    getline(cin, p.price);
    p.price = trim(p.price);

    cout << "Quantity: ";
    getline(cin, p.quantity);
    p.quantity = trim(p.quantity);

    cin.ignore();
    return p;
}