#pragma once
#include <fstream>
#include "Exceptions.h"

// 1-6. HAFTALAR: Temel Veri Yapısı
class Matrix {
private:
    int rows;          
    int cols;          
    double** data;     

public:
    // 1-3. Hafta: Yapıcı (Constructor) ve Yıkıcı (Destructor)
    Matrix(int r, int c);
    ~Matrix();
    
    // 4-5. Hafta: Derin Kopyalama
    Matrix(const Matrix& other); 

    // Kapsülleme (Getter/Setter)
    int getRows() const;
    int getCols() const;
    void setValue(int r, int c, double val);
    double getValue(int r, int c) const;

    // 6. ve 9. Hafta: Matematik Motoru ve Operatör Aşırı Yükleme
    Matrix multiply(const Matrix& other) const;
    Matrix operator+(const Matrix& other) const;

    // 14. Hafta: SOLID (Kalıcılık ve Ekrana Yazdırma)
    void saveToFile(std::ofstream& file) const;
    void loadFromFile(std::ifstream& file);
    void print() const;
};