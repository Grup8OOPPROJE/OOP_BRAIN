#pragma once
#include "Matrix.h"
#include <string>

class CSVReader {
public:
    // CSV dosyasını okuyup belirtilen boyutlarda bir Matrix döndüren statik fonksiyon
    static Matrix loadFeatures(const std::string& filename, int num_rows, int num_cols);
};
