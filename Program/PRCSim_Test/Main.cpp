#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Config.h"

std::vector<std::vector<std::string>> readCSV(const std::string& filename) {
    std::vector<std::vector<std::string>> data;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Can't Open File: " << filename << std::endl;
        return data;
    }

    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream lineStream(line);
        std::string cell;

        while (std::getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }
        data.push_back(row);
    }

    file.close();
    return data;
}

int main() {
    std::string filename = "resampled_data.csv";

    std::vector<std::vector<std::string>> csvData = readCSV(filename);

    if (csvData.empty()) { return 1; }

    std::cout << csvData.size() << " " << csvData[0].size() << "\n";
    
    ParachuteSystem prc;

    std::cout << "Filling Slope Data..." << std::endl;
    int fillCount = PRC_BUFFER_SIZE*2;
    for (int i = 0; i < fillCount; i++) {
        prc.fillSpace(std::stof(csvData[1][0]), std::stof(csvData[1][1]));
    }

    std::cout << "Start!" << std::endl;

    std::string output_filename = "data.csv";
    std::ofstream outputFile(output_filename);

    if (!outputFile.is_open()) {
        std::cerr << "無法開啟檔案: " << output_filename << std::endl;
        return 1;
    }

    for (const auto& row : csvData) {
        float array_f[3];
        bool array_b[5];
        array_f[0] = std::stof(row[1]);
        prc.decideDeployment(std::stof(row[0]), array_f, array_b);

        outputFile << row[0];
        outputFile << ",";
        for (const float f : array_f) {
            outputFile << f;
            outputFile << ",";
        }
        for (const float b : array_b) {
            outputFile << b;
            outputFile << ",";
        }
        outputFile << 0;
        outputFile << "\n";
    }

    outputFile.close();

    return 0;
}