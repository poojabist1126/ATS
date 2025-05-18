#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;

struct Product {
    string productName;
    string productDesc;
    string date;
    int noOfProduct;

    Product() : productName(""), productDesc(""), date(""), noOfProduct(0) {}

    Product(string name, string desc = "", string d = "", int noOf = 0)
        : productName(name), productDesc(desc), date(d), noOfProduct(noOf) {
    }
};

string getCurrentDateTime() {
    auto now = chrono::system_clock::now();

    time_t now_c = chrono::system_clock::to_time_t(now);

    ostringstream oss;

    struct tm buf;
    localtime_s(&buf, &now_c);
    oss << put_time(&buf, "%Y-%m-%d %H:%M:%S");

    return oss.str();
}

Product askProductDetails() {
    Product p;

    cout << "Enter name of Product: ";
    getline(cin, p.productName);

    cout << "Enter description of Product (optional): ";
    getline(cin, p.productDesc);

    p.date = getCurrentDateTime();

    cout << "Enter number of products: ";
    cin >> p.noOfProduct;

    cin.ignore();
    return p;
}

int main() {
    vector<Product> products;

    string command;
    string keyword = "add";
    Product tempProduct;

    cout << "Enter command: ";
    getline(cin, command);

    if (command.rfind(keyword, 0) == 0 && (command.size() == keyword.size() || command[keyword.size()] == ' ')) {
        tempProduct = askProductDetails();
        products.push_back(tempProduct);

        cout << products[0].productName << endl;
        cout << products[0].productDesc << endl;
        cout << products[0].date << endl;
        cout << products[0].noOfProduct << endl;
    }
    else {
        cout << "Keyword not found." << endl;
    }

    return 0;
}
