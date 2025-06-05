#ifndef COMMONFUNC_HPP
#define COMMONFUNC_HPP

#include <string>
#include <vector>

std::string getCurrentDateTime();
std::vector<std::string> getCommand();
std::string trim(const std::string& s);
void displayTable(const std::vector<std::vector<std::string>>& data);
std::string generateRandomNumByTime();
bool isValidEmail(const std::string& email);
bool isValidNZMobileNumber(const std::string& number);
bool isValidPassword(const std::string& password);
bool isValidGender(const std::string& gender);
bool isNumber(const std::string& str);
bool isWholeNumber(const std::string& str);
void printTable(const std::vector<std::vector<std::string>>& table, int sortByColumn = -1, bool ascending = true);

#endif