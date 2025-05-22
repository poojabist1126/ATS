#include "modcsv.hpp"

void writeCsvFile(const std::string& filename, const std::vector<std::vector<std::string>>& data, bool append) {
    std::ofstream outputFile;

    if (append) {
        outputFile.open(filename, std::ios::out | std::ios::app);
    }
    else {
        outputFile.open(filename, std::ios::out | std::ios::trunc);
    }

    if (outputFile.is_open()) {
        for (const auto& row : data) {
            for (size_t i = 0; i < row.size(); ++i) {
                outputFile << row[i];
                if (i < row.size() - 1) {
                    outputFile << ","; 
                }
            }
            outputFile << "\n"; 
        }
        outputFile.close();
    }
    else {
        std::cerr << "Error: Unable to access data." << std::endl;
    }
}


std::vector<std::vector<std::string>> readCsvFile(const std::string& filename) {
    std::vector<std::vector<std::string>> data;
    std::ifstream inputFile(filename);

    if (inputFile.is_open()) {
        std::string line;
        while (getline(inputFile, line)) {
            std::vector<std::string> row;
            std::stringstream ss(line);
            std::string field;

            while (getline(ss, field, ',')) {
                row.push_back(field);
            }
            data.push_back(row);
        }
        inputFile.close();
    }
    else {
        std::cerr << "Error: Unable access the information." << std::endl;
    }
    return data;
}