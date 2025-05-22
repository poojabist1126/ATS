#ifndef USERAUTHENTICATION_HPP
#define USERAUTHENTICATION_HPP

#include <string>
#include <vector>

bool checkUser(std::string username, std::string password, std::string filePath);

std::vector<std::string> userLogin(std::vector<std::string> command);

std::vector<std::string> userSignup();


#endif
