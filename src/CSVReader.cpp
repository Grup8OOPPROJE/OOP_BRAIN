#include "../include/CSVReader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Matrix CSVReader::loadFeatures(const std::string& filename, int num_rows, int num_cols) {
    Matrix data(num_rows, num_cols);
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "[HATA] Veri seti dosyasi acilamadi: " << filename << std::endl;
        return data;
    }

    std::string line;
    int row = 0;
    
    // Satır satır okuma işlemi
    while (std::getline(file, line) && row < num_rows) {
        std::stringstream ss(line);
        std::string cell;
        int col = 0;
        
        // Virgüllere göre sütunları ayırma
        while (std::getline(ss, cell, ',') && col < num_cols) {
            try {
                double val = std::stod(cell); // String'i ondalıklı sayıya (double) çevir
                data.setValue(row, col, val);
            } catch (...) {
                // Eğer hücrede sayı yoksa (örneğin "Iris-setosa" yazısı varsa) atla
            }
            col++;
        }
        row++;
    }
    
    file.close();
    return data;
}