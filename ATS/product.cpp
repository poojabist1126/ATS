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
        cout << "Quantity: ";
        getline(cin, quantity);
        quantity = trim(quantity);

        if (!isWholeNumber(quantity)) {
            cout << "Quantity is not valid. Press enter to type again or type 'q' to quit." << endl;
            getline(cin, res);
        }

        if (res == "q")
            return { };
    }

    while (!(storeLocation == "1" || storeLocation == "2" || storeLocation == "3") && res != "q") {
        cout << "Store Location (1 for Wellington, 2 for Christchurch, 3 for Auckland): ";
        getline(cin, storeLocation);
        storeLocation = trim(storeLocation);

        if (!(storeLocation == "1" || storeLocation == "2" || storeLocation == "3")) {
            cout << "Store Location is not valid. Press enter to type again or type 'q' to quit." << endl;
            getline(cin, res);
        }

        if (res == "q")
            return { };
    }

    productId = "P" + generateRandomNumByTime();

    cout << "Details added successfully." << endl;

    if (storeLocation == "1") {
        storeLocation = "Wellington";
    }
    else if (storeLocation == "2") {
        storeLocation = "Christchurch";
    }
    else if (storeLocation == "3") {
        storeLocation = "Auckland";
    }

    return { productId, name, category, price, quantity, storeLocation };
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
                return { details[i][0], details[i][1], details[i][2], details[i][3], details[i][4], details[i][5] };
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

    while (!(storeLocation == "1" || storeLocation == "2" || storeLocation == "3") && res != "q") {
        cout << "Store Location (1 for Wellington, 2 for Christchurch, 3 for Auckland): ";
        getline(cin, storeLocation);

        if (storeLocation.empty())
            break;

        if (!(storeLocation == "1" || storeLocation == "2" || storeLocation == "3")) {
            cout << "Store Location is not valid. Press enter to type again or type 'q' to quit." << endl;
            getline(cin, res);
        }

        if (res == "q")
            return { };
    }

    storeLocation = trim(storeLocation);

    if (storeLocation == "1") {
        storeLocation = "Wellington";
    }
    else if (storeLocation == "2") {
        storeLocation = "Christchurch";
    }
    else if (storeLocation == "3") {
        storeLocation = "Auckland";
    }


    updateDetails(filePath, 0, trim(productId), { { "", trim(name), trim(category), trim(price), trim(quantity)} });
    return true;
}

vector<vector<string>> Product::getProductsByCategory(string category) {
    vector<vector<string>> filtered, output = readCsvFile(filePath);

    for (const auto& row : output) {
        if (row.size() > 2 && (row[2] == category || filtered.size() == 0)) {
            filtered.push_back(row);
        }
    }

    return filtered;
}

vector<vector<string>> Product::getProductsByStoreLocation(string storeLocation) {
    vector<vector<string>> filtered, output = readCsvFile(filePath);

    for (const auto& row : output) {
        if (row.size() > 5 && (row[5] == storeLocation || filtered.size() == 0)) {
            filtered.push_back(row);
        }
    }

    return filtered;
}

vector<vector<string>> Product::getProducts() {
    return readCsvFile(filePath);
}

void Product::deleteProduct(string productId) {
    if (getDetails(productId).empty())
        cout << "Product not found." << endl;
    else
        deleteDetails(filePath, 0, productId);
}

void Product::clear() {
    productId.clear();
    name.clear();
    category.clear();
    price.clear();
    quantity.clear();
    storeLocation.clear();
    res.clear();
}