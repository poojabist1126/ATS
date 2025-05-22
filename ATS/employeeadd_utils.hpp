#ifndef EMPLOYEEADD_UTILS_HPP
#define EMPLOYEEADD_UTILS_HPP

#include <string>

using namespace std;

string getCurrentDateTime();

string generateEmployeeId();

struct Employee {
    string id;
    string name;
    string position;
    string email;
    string contactNum;
    string gender;
    string joinedDate;
    string DOB;

    Employee(string id = "", string name = "", string position = "", string email = "", string contactNum = "", string gender = "", string joinedDate = "", string DOB = "")
        : id(id), name(name), position(position), email(email), contactNum(contactNum), gender(gender), joinedDate(joinedDate), DOB(DOB) {
    }
};

Employee askEmployeeDetails();


#endif
