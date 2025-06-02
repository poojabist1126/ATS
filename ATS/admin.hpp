#ifndef ADMIN_HPP
#define ADMIN_HPP

#include <string>
#include <vector>

class Admin {
private:
    std::string username;
    std::string password;
    std::string res;
    std::string filePath = "admin_details.csv";
public:
    std::vector<std::string> askDetails();
    std::vector<std::string> appendDetails();
    bool isUserExist(std::string username);
    std::vector<std::string> getDetails(std::string username);
};

#endif