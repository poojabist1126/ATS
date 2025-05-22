#ifndef MODCSV_H
#define MODCSV_H
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

void writeCsvFile(const std::string& filename, const std::vector<std::vector<std::string>>& data, bool append = false);

std::vector<std::vector<std::string>> readCsvFile(const std::string& filename);

void updateDetails(
    const std::string& filename,
    size_t matchColumnIndex,
    const std::string& matchValue,
    const std::vector<std::string>& newRow
);

void deleteDetails(
    const std::string& filename,
    size_t matchColumnIndex,
    const std::string& matchValue
);

#endif
