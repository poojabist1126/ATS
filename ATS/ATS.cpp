#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <vector>
#include <random>
#include "productadd_utils.hpp"

using namespace std;

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
      
        cout << products[0].productId << endl;
        cout << products[0].productName << endl;
        cout << products[0].productDesc << endl;
        cout << products[0].date << endl;
        cout << products[0].price << endl;
        cout << products[0].quantity << endl;
    }
    else {
        cout << "Keyword not found." << endl;
    }

    return 0;
}