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
public:
    std::vector<std::string> getDetails();
    void appendDetails();
};

#endif