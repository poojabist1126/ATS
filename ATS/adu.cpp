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