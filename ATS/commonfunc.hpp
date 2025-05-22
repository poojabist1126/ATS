#ifndef COMMONFUNC_HPP
#define COMMONFUNC_HPP

#include <string>
#include <vector>

std::string getCurrentDateTime();
std::vector<std::string> getCommand();
std::string trim(const std::string& s);
void displayTable(const std::vector<std::vector<std::string>>& data);

#endif
