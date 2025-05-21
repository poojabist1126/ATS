#ifndef READCSV_H
#define READCSV_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


std::vector<std::vector<std::string>> readCsvFile(const std::string& filename);

#endif