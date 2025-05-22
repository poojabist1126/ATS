#ifndef PRODUCTADD_UTILS_HPP
#define PRODUCTADD_UTILS_HPP

#include <string>

using namespace std;

string getCurrentDateTime();

string generateProductID();

struct Product {
    string productId;
    string productName;
    string productDesc;
    string date;
    string price;
    string quantity;

    Product(string id = "", string name = "", string desc = "", string d = "", string pr = "", string noOf = "")
        : productId(id), productName(name), productDesc(desc), date(d), price(pr), quantity(noOf) {
    }
};

Product askProductDetails();


#endif
