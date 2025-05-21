#include "writecsv.hpp"

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
        std::cout << "Data added successfully." << std::endl; 
    }
    else {
        std::cerr << "Error: Unable to open file " << filename << "." << std::endl;
    }
}