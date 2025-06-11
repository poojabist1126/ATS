#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <string>
#include <vector>

class Employee {
private:
    std::string employeeId;
    std::string name;
    std::string position;
    std::string email;
    std::string contactNum;
    std::string gender;
    std::string address;
    std::string joinedDate;
    std::string res;
    std::string filePath = "employee_details.csv";
    std::string rosterPath = "employee_roster.csv";
public:
    std::vector<std::string> askDetails();
    std::vector<std::string> appendDetails();
    bool isUserExist(std::string username);
    std::vector<std::string> getDetails(std::string username);
    bool updateUserDetails(std::string username);
    std::vector<std::vector<std::string>> getUsers();
    std::vector<std::vector<std::string>> getEmployeesByPosition(std::string position);
    void updateRoster(std::string employeeId);
    std::vector<std::vector<std::string>> getRosters();
    void clear();
};

#endif