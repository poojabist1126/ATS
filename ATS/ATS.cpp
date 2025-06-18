#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <random>
#include <regex>
#include <map>

#include "modcsv.hpp"
#include "commonfunc.hpp"
#include "customer.hpp"
#include "employee.hpp"
#include "admin_.hpp"
#include "product.hpp"

using namespace std;

void userAuthentication(map<string, string>& user, vector<string> command) {
    // user authentication function 

    if (command[0] == "signup" && command.size() == 1) {
        if (user["username"] == "") {
            cout << "Please enter the details.\n" << endl;

            Customer c;

            vector<string> details = c.appendDetails(); // appends details to customer details csv file

            user["username"] = details[1];
            user["type"] = "c"; // sets user's type to customer

            cout << "Congratulations, " + details[0] + " you have successfully created account as " + user["username"] + "." << endl;
        }
        else {
            cout << "You have to logout first." << endl;
        }
    }
    else if (command[0] == "login") {
        if (user["username"] == "") {
            if (command.size() == 1) {
                Customer c;
                string username, password;
                vector<string> details;

                cout << "Username: ";
                getline(cin, username);

                if (c.isUserExist(username)) {
                    // excutes only if the username exists in the csv file
                    cout << "Password: ";
                    getline(cin, password);

                    details = c.getDetails(username); // gets the details from customer csv file

                    if (details[3] == trim(password)) {
                        user["username"] = trim(username);
                        user["type"] = "c"; // sets user's type to customer

                        cout << "Welcome " << details[0] << ", login successful." << endl;
                    }
                    else {
                        cout << "Login failed. Password doesn't matched." << endl;
                    }
                }
                else {
                    cout << "User doesn't exists, please enter valid username. If you don't have account please signup.\nTo signup, please type 'signup'. Thank You" << endl;
                }
            }
            else if (command[1] == "admin" && command.size() == 2) {
                Admin a;
                string username, password;
                vector<string> details;

                cout << "Username: ";
                getline(cin, username);

                if (a.isUserExist(username)) {
                    // excutes only if the username exists in the csv file
                    cout << "Password: ";
                    getline(cin, password);

                    details = a.getDetails(username); // gets the details from admin csv file
                    if (details[1] == trim(password)) {
                        user["username"] = trim(username);
                        user["type"] = "a";

                        cout << "Welcome " << details[0] << ", login successful." << endl;
                    }
                    else {
                        cout << "Login failed. Password doesn't matched." << endl;
                    }
                }
                else {
                    cout << "User doesn't exists, please enter valid username. If you don't have account please signup.\nTo signup, please type 'signup'. Thank You" << endl;
                }
            }
        }
        else {
            cout << "You have to logout first." << endl;
        }

    }
}

bool checkUser(map<string, string> user, string commandOf = "") {
    if (user["username"] == "" && user["type"] == "") {
        // executes if no user has been registered
        cout << "You are not logged in." << endl;
        cout << "To log in, type: 'login'." << endl;
        cout << "To create an account, type: 'signup'." << endl;
        cout << "To view available commands, type: 'help'." << endl;
        return false;
    }
    else if (user["username"] != "" && user["type"] == "c" && commandOf == "a") {
        // executes if user want to executes command of admin but is logined as a customer
        cout << "Must be loggedIn as admin." << endl;
        return false;
    }
    return true;
}

int main() {
    vector<string> command;
    map<string, string> user = { {"username", ""}, {"type", ""} };
    Customer c;
    Admin a;
    Product p;
    Employee e;
    string productCSV = "product_details.csv";
    string orderCSV = "order_details.csv";

    // starting messages
    cout << "Welcome to Aotearoa Treasures’s inventory management system\n" << endl;

    cout << "Please login to use this software. If you don't have account, please create one." << endl;
    cout << "Type 'login' to login." << endl;
    cout << "Type 'signup' to create account.\n" << endl;

    cout << "If you want to see list of commands, please type 'help'.\n" << endl;

    do {
        cout << ">>> ";
        command = getCommand();

        userAuthentication(user, command); // user authentication

        if (command[0] == "logout" && checkUser(user, "") && command.size() == 1) {
            // to logout executes only if user is registered
            user["username"] = "";
            user["type"] = "";

            cout << "Logout successful." << endl;
        }


        if (command[0] == "add" && command.size() == 2) {
            if (command[1] == "product" && checkUser(user, "a")) {
                // adds product
                p.appendDetails();
            }
            else if (command[1] == "employee" && checkUser(user, "a")) {
                // adds employee
                e.appendDetails();
            }
            else if (command[1] == "roster" && checkUser(user, "a")) {
                // adds rooster
                string employeeId;
                cout << "Enter employee Id: ";
                getline(cin, employeeId);
                employeeId = trim(employeeId);

                if (employeeId.empty())
                    continue;

                e.addRoster(employeeId);
            }
        }
        else if (command[0] == "update" && command.size() == 2) {
            if (command[1] == "product" && checkUser(user, "a")) {
                // updates product
                string productId;
                cout << "Enter product Id: ";
                getline(cin, productId);
                productId = trim(productId);

                p.updateProductDetails(productId);
            }
            else if (command[1] == "employee" && checkUser(user, "a")) {
                // updates employee
                string employeeId;
                cout << "Enter employee Id: ";
                getline(cin, employeeId);
                employeeId = trim(employeeId);

                e.updateUserDetails(employeeId);
            }
            else if (command[1] == "roster" && checkUser(user, "a")) {
                // updates roster
                string employeeId;
                cout << "Enter employee Id: ";
                getline(cin, employeeId);
                employeeId = trim(employeeId);

                e.updateRosters(employeeId);
            }
        }
        else if (command[0] == "show") {
            if (command[1] == "product") {
                vector<vector<string>> products;
                if (command.size() == 2) {
                    // display all the products
                    products = p.getProducts();
                    printTable(products, -1);
                }
                else if (command.size() == 4) {
                    if (command[2] == "category") {
                        // only display the product of specific category
                        products = p.getProductsByCategory(command[3]);
                        printTable(products);
                    }
                    else if (command[2] == "storeLocation") {
                        // only display the products in specific location
                        products = p.getProductsByStoreLocation(command[3]);
                        printTable(products);
                    }
                    else if (command[2] == "asc") {
                        if (command[3] == "price") {
                            // display products in a ascending sorted way with respect to price
                            products = p.getProducts();
                            printTable(products, 3, true);
                        }
                        else if (command[3] == "quantity") {
                            // display products in a ascending sorted way with respect to quantity
                            products = p.getProducts();
                            printTable(products, 4, true);

                        }
                    }
                    else if (command[2] == "desc") {
                        if (command[3] == "price") {
                            // display products in a descending sorted way with respect to price
                            products = p.getProducts();
                            printTable(products, 3, false);
                        }
                        else if (command[3] == "quantity") {
                            // display products in a descending sorted way with respect to quantity
                            products = p.getProducts();
                            printTable(products, 4, false);

                        }
                    }
                }
            }
            else if (command[1] == "employee" && checkUser(user, "a")) {
                vector<vector<string>> employees;
                if (command.size() == 2) {
                    // display all the employees
                    employees = e.getUsers();
                    printTable(employees);
                }
                else if (command.size() == 4) {
                    if (command[2] == "position") {
                        // only display the employee of specific position 
                        employees = e.getEmployeesByPosition(command[3]);
                        printTable(employees);
                    }
                }
            }
            else if (command[1] == "roster" && checkUser(user, "a")) {
                if (command.size() == 2) {
                    // display all the roster
                    printTable(e.getRosters());
                }
            }
        }
        else if (command[0] == "buy" && checkUser(user, "c")) {
            // buy product
            vector<string> product;

            if (command.size() == 2) {
                string quantity;
                string res;

                while (!isWholeNumber(quantity) && res != "q") {
                    cout << "Quantity: "; // ask's quantity
                    getline(cin, quantity);
                    quantity = trim(quantity);

                    // quantity must be a whole number
                    if (!isWholeNumber(quantity)) {
                        cout << "Quantity is not valid. Press enter to type again or type 'q' to quit." << endl;
                        getline(cin, res);
                    }

                    if (res == "q")
                        break;
                }

                // command[1] must be product id
                product = p.getDetails(command[1]);

                if (product.empty()) {
                    cout << "Product doesn't exists." << endl;
                    continue;
                }

                int itemLeft = stoi(product[4]) - stoi(quantity); // checks available quantity

                if (itemLeft < 0) {
                    cout << "Not enough item. Item left: " << product[4] << "." << endl;
                    continue;
                }

                updateDetails(productCSV, 0, command[1], { product[0], product[1], product[2], product[3], to_string(itemLeft), product[5] }); // updates quantity in products csv file

                writeCsvFile(orderCSV, { {user["username"], product[0], product[1], quantity, product[5], getCurrentDateTime(), "COD", "not complete"} }, true); // add order in order csv file

                cout << "Your order successfully registered." << endl;
                cout << "Order will delivered within T+3 days." << endl;
                cout << "Payment method Cash on Delivery" << endl;
                cout << "Location: " << product[5] << endl;
            }
        }
        else if (command[0] == "delete" && command.size() == 2) {
            if (command[1] == "employee" && checkUser(user, "a")) {
                // deletes employee
                string employeeId;
                cout << "Enter employee Id: "; // asks employee id
                getline(cin, employeeId);
                employeeId = trim(employeeId);

                e.deleteUser(employeeId);
            }
            else if (command[1] == "roster" && checkUser(user, "a")) {
                // delete roster
                string employeeId;
                cout << "Enter employee Id: "; // asks employee id
                getline(cin, employeeId);
                employeeId = trim(employeeId);

                e.deleteRoster(employeeId);
            }
            else if (command[1] == "product" && checkUser(user, "a")) {
                // delete product
                string productId;
                cout << "Enter product Id: "; // asks product id
                getline(cin, productId);
                productId = trim(productId);

                p.deleteProduct(productId);
            }
            else if (command[1] == "customer" && checkUser(user, "a")) {
                // delete customer
                string username;
                cout << "Enter username: "; // asks username
                getline(cin, username);
                username = trim(username);

                c.deleteUser(username);
            }
        }
        else if (command[0] == "help" && command.size() == 1) {
            printTable(readCsvFile("help.csv")); // display commands
        }
        else if (command[0] == "alert" && checkUser(user, "a")) {
            if (command[1] == "quantity" && command.size() == 2) {
                // display products with less than 5 quantity
                vector<vector<string>> filtered, output = p.getProducts();
                cout << "Products with less than 5 quantity:\n" << endl;

                for (const auto& row : output) {
                    if (row.size() > 4 && (row[4] == "0" || row[4] == "1" || row[4] == "2" || row[4] == "3" || row[4] == "4" || filtered.size() == 0)) {
                        filtered.push_back(row);
                    }
                }

                printTable(filtered);
            }
        }

        p.clear();
        e.clear();
        c.clear();
    } while (command[0] != "exit");


    return 0;
}