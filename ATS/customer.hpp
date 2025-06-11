#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include <string>
#include <vector>

class Customer {
private:
    std::string name;
    std::string username;
    std::string email;
    std::string password;
    std::string joinedDate;
    std::string res;
    std::string filePath = "customer_details.csv";
public:
    std::vector<std::string> askDetails();
    std::vector<std::string> appendDetails();
    bool isUserExist(std::string username);
    std::vector<std::string> getDetails(std::string username);
    bool updateUserDetails(std:: string username);
    void deleteUser(std::string username);
    void clear();
};

#endif