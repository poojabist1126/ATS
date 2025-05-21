#ifndef WRITECSV_H
#define WRITECSV_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


void writeCsvFile(const std::string& filename, const std::vector<std::vector<std::string>>& data, bool append = false);

#endif