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

    command = getCommand();

    if (command[0] == "login") {
        userStatus = userLogin(command);
    }
    else if (command[0] == "signup") {
        userStatus = userSignup(command);
    }

    return 0;
}