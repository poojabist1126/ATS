#ifndef MODCSV_H
#define MODCSV_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


void writeCsvFile(const std::string& filename, const std::vector<std::vector<std::string>>& data, bool append = false);

std::vector<std::vector<std::string>> readCsvFile(const std::string& filename);

#endif