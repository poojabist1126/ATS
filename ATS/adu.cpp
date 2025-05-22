#include "adu.hpp"
#include "commonfunc.hpp"
#include "employeeadd_utils.hpp"
#include "productadd_utils.hpp"
#include "modcsv.hpp"
#include <iostream>
using namespace std;

void updateDetails(vector<string> command) {
    if (command[1] == "product") {
        string id;
        cout << "Enter id of product: ";
        getline(cin, id);

        cout << "Leave blank to not update." << endl;

        Product p;
        p = askProductDetails();

        updateDetails("product_details.csv", 0, trim(id), { "", p.productName, p.productDesc, "", p.price, p.quantity });
    }
    else if (command[1] == "employee") {
        string id;
        cout << "Enter id of employee: ";
        getline(cin, id);

        cout << "Leave blank to not update." << endl;

        Employee e;
        e = askEmployeeDetails();

        updateDetails("employee_details.csv", 0, trim(id), { "", e.name, e.position, e.gender, "", e.DOB });
    }
    else {
        cout << "Please enter a valid command. To check valid commands, type 'help'." << endl;
    }
}

void addDetails(vector<string> command) {
    if (command[1] == "product") {
        Product p;

        p = askProductDetails();

        if (p.productName == "" || p.price == "" || p.quantity == "") {
            cout << "Required fields cannot be empty. Product add failed. Try again." << endl;
        }
        else {
            writeCsvFile("product_details.csv", { {p.productId, p.productName, p.productDesc, p.date, p.price, p.quantity} }, true);
            cout << "Product add successful. The product id is " << p.productId << "." << endl;
        }
    }
    else if (command[1] == "employee") {
        Employee e;

        e = askEmployeeDetails();

        if (e.name == "" || e.position == "" || e.email == "" || e.contactNum == "" || e.gender == "" || e.DOB == "") {
            cout << "Required fields cannot be empty. Product add failed. Try again." << endl;
        }
        else {
            writeCsvFile("employee_details.csv", { {e.id, e.name, e.position, e.email, e.contactNum, e.gender, e.DOB, e.joinedDate} }, true);
            cout << "Employee add successful. The employee id is " << e.id << "." << endl;
        }
    }
}