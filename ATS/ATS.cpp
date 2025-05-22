#include <iostream>
#include <string>
#include <vector>
#include "productadd_utils.hpp"
#include "employeeadd_utils.hpp"
#include "modcsv.hpp"
#include "userauthentication.hpp"
#include "commonfunc.hpp"

using namespace std;

int main() {
    vector<string> command;
    vector<string> userStatus = { "n", "" };

    //command = getCommand();

    //if (command[0] == "login") {
    //    userStatus = userLogin(command);
    //}
    //else if (command[0] == "signup") {
    //    userStatus = userSignup(command);
    //}

    Product p;

    //p = askProductDetails();

    updateDetails("product_details.csv", 0, "202505230805549925", { "202505230805549925", "whehghwghrehbrgwregre", "rehrehrenbrehreh", "2025-05-23 08:08:57", "1034430", "10" });

    return 0;
}