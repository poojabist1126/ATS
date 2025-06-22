#ifndef ADMIN_HPP
#define ADMIN_HPP

#include <string>
#include <vector>

class Admin {
private:
    std::string username;
    std::string employeeId;
    std::string password;
    std::string res;
    std::string filePath = "admin_details.csv";
public:
    std::vector<std::string> askDetails();
    std::vector<std::string> appendDetails();
    bool isUserEmployee(std::string employeeId);
    bool isUserEmployeeIdExist(std::string employeeId);
    bool isUserExist(std::string username);
    std::vector<std::string> getDetails(std::string username);
    void clear();
};

#endif