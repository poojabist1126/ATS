#include "product.hpp"
#include "commonfunc.hpp"
#include "modcsv.hpp"
#include <iostream>

using namespace std;

vector<string> Product::askDetails() {
    while (name.empty() && res != "q") {
        cout << "Name: ";
        getline(cin, name);
        name = trim(name);

        if (name.empty()) {
            cout << "Name cannot be empty. Press enter to type again or type 'q' to quit." << endl;
            getline(cin, res);
        }

        if (res == "q")
            return { };
    }

    while (category.empty() && res != "q") {
        cout << "Category: ";
        getline(cin, category);
        category = trim(category);

        if (category.empty()) {
            cout << "Category cannot be empty. Press enter to type again or type 'q' to quit." << endl;
            getline(cin, res);
        }

        if (res == "q")
            return { };
    }

    while (!isNumber(price) && res != "q") {
        cout << "Price: ";
        getline(cin, price);
        price = trim(price);

        if (!isNumber(price)) {
            cout << "Price is not valid. Press enter to type again or type 'q' to quit." << endl;
            getline(cin, res);
        }

        if (res == "q")
            return { };
    }

    while (!isWholeNumber(quantity) && res != "q") {
        cout << "Price: ";
        getline(cin, quantity);
        quantity = trim(quantity);

        if (!isWholeNumber(quantity)) {
            cout << "Quantity is not valid. Press enter to type again or type 'q' to quit." << endl;
            getline(cin, res);
        }

        if (res == "q")
            return { };
    }

    productId = "P" + generateRandomNumByTime();

    cout << "Thanks for the details.\n" << endl;
    return { productId, name, category, price, quantity };
}

vector<string> Product::appendDetails() {
    vector<string> details = askDetails();

    writeCsvFile(filePath, { details }, true);

    return details;
}

bool Product::isProductExist(string productId) {
    if (productId.empty() || productId == "")
        return false;

    vector<vector<string>> details = readCsvFile(filePath);
    int i = 0;

    for (i = 0; i < details.size(); i++) {
        if (productId == details[i][0]) {
            return true;
            break;
        }
    }

    return false;
}

vector<string> Product::getDetails(string productId) {
    if (isProductExist(productId)) {
        vector<vector<string>> details = readCsvFile(filePath);
        int i = 0;

        for (i = 0; i < details.size(); i++) {
            if (trim(productId) == details[i][0]) {
                return { details[i][0], details[i][1], details[i][2], details[i][3], details[i][4] };
                break;
            }
        }
    }

    return {};
}

bool Product::updateProductDetails(string productId) {
    cout << "Name: ";
    getline(cin, name);

    cout << "Category: ";
    getline(cin, category);

    while (!isNumber(price) && res != "q") {
        cout << "Price: ";
        getline(cin, price);
        price = trim(price);

        if (price.empty())
            break;

        if (!isNumber(price)) {
            cout << "Price is not valid. Press enter to type again or type 'q' to quit." << endl;
            getline(cin, res);
        }

        if (res == "q")
            return { };
    }


    while (!isWholeNumber(quantity) && res != "q") {
        cout << "Price: ";
        getline(cin, quantity);
        quantity = trim(quantity);

        if (quantity.empty())
            break;

        if (!isWholeNumber(quantity)) {
            cout << "Quantity is not valid. Press enter to type again or type 'q' to quit." << endl;
            getline(cin, res);
        }

        if (res == "q")
            return { };
    }


    updateDetails(filePath, 0, trim(productId), { { "", trim(name), trim(category), trim(price), trim(quantity)} });
    return true;
}