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

        std::cout << "Successfull." << std::endl;
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

        std::cout << "Successfull." << std::endl;
    }
    else {
        std::cerr << "Error: Unable access the information." << std::endl;
    }
    return data;
}

void updateDetails(
    const std::string& filename,
    size_t matchColumnIndex,
    const std::string& matchValue,
    const std::vector<std::string>& newRow
) {
    auto data = readCsvFile(filename);
    bool found = false;

    for (auto& row : data) {
        if (row.size() > matchColumnIndex && row[matchColumnIndex] == matchValue) {
            if (row.size() < newRow.size()) {
                row.resize(newRow.size());
            }

            for (size_t i = 0; i < newRow.size(); ++i) {
                if (newRow[i] != "")
                    row[i] = newRow[i];
            }

            found = true;
            break;
        }
    }

    if (found) {
        writeCsvFile(filename, data, false);
    }
    else {
        std::cout << "No details found." << std::endl;
    }
}

void deleteDetails(
    const std::string& filename,
    size_t matchColumnIndex,          
    const std::string& matchValue    
) {
    auto data = readCsvFile(filename);
    bool found = false;

    std::vector<std::vector<std::string>> updatedData;

    for (const auto& row : data) {
        if (row.size() > matchColumnIndex && row[matchColumnIndex] == matchValue) {
            found = true; 
            continue;
        }
        updatedData.push_back(row);  
    }

    if (found) {
        writeCsvFile(filename, updatedData, false);  
    }
    else {
        std::cerr << "Error: No row found with value '" << matchValue << "'." << std::endl;
    }
}