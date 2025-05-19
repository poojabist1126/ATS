#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <vector>
#include <random>
#include "productadd_utils.hpp"

using namespace std;

//string getCurrentDateTime() {
//    auto now = chrono::system_clock::now();
//
//    time_t now_c = chrono::system_clock::to_time_t(now);
//
//    ostringstream oss;
//
//    struct tm buf;
//    localtime_s(&buf, &now_c);
//    oss << put_time(&buf, "%Y-%m-%d %H:%M:%S");
//
//    return oss.str();
//}
//
//
//string generateProductID() {
//    string dateTime = getCurrentDateTime();
//
//    string datePart = dateTime.substr(0, 10);
//    string timePart = dateTime.substr(11, 8);
//
//    datePart.erase(remove(datePart.begin(), datePart.end(), '-'), datePart.end());
//    timePart.erase(remove(timePart.begin(), timePart.end(), ':'), timePart.end());
//
//    random_device rd;
//    mt19937 gen(rd());
//    uniform_int_distribution<> dis(1000, 9999);
//    int random_number = dis(gen);
//
//    ostringstream productID;
//    productID << datePart << timePart << random_number;
//
//    return productID.str();
//}
//
//struct Product {
//    string productId;
//    string productName;
//    string productDesc;
//    string date;
//    int price;
//    int quantity;
//
//    Product(string id = "", string name = "", string desc = "", string d = "", int pr = 0, int noOf = 0)
//        : productId(id), productName(name), productDesc(desc), date(d), price(pr), quantity(noOf) {
//    }
//};
//
//
//Product askProductDetails() {
//    Product p;
//
//    p.productId = generateProductID();
//
//    cout << "Name: ";
//    getline(cin, p.productName);
//
//    cout << "Description (optional): ";
//    getline(cin, p.productDesc);
//
//    p.date = getCurrentDateTime();
//
//    cout << "Price (NZD): ";
//    cin >> p.price;
//
//    cout << "Quantity: ";
//    cin >> p.quantity;
//
//    cin.ignore();
//    return p;
//}

int main() {
    vector<Product> products;

    string command;
    string keyword = "add";
    Product tempProduct;
    bool productAddValid = true;

    cout << "Enter command: ";
    getline(cin, command);

    if (command.rfind(keyword, 0) == 0 && (command.size() == keyword.size() || command[keyword.size()] == ' ')) {
        tempProduct = askProductDetails();

        if (tempProduct.productId == "" || tempProduct.date == "" || tempProduct.productName == "") {
            cout << "Error: Product Name cannot be empty." << endl;
            productAddValid = false;
        }

        if (tempProduct.price < 0) {
            cout << "Error: Price cannot be negative." << endl;
            productAddValid = false;
        }

        if (tempProduct.quantity < 0) {
            cout << "Error: Quantity cannot be negative." << endl;
            productAddValid = false;
        }

        if (productAddValid) {
            products.push_back(tempProduct);
            cout << products[0].productId << endl;
            cout << products[0].productName << endl;
            cout << products[0].productDesc << endl;
            cout << products[0].date << endl;
            cout << products[0].price << endl;
            cout << products[0].quantity << endl;
        }
    }
    else {
        cout << "Keyword not found." << endl;
    }

    return 0;
}