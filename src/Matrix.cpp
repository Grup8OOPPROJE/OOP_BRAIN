#include "../include/Matrix.h"
#include <iostream>
#include <iomanip>
#include <string>

// 1-2. Hafta: Yapıcı (Constructor) ile Dinamik Bellek Ayırımı 
Matrix::Matrix(int r, int c) : rows(r), cols(c) {
    data = new double*[rows]; 
    for (int i = 0; i < rows; ++i) {
        data[i] = new double[cols];
        // Bellekteki çöp değerlerin temizlenmesi
        for (int j = 0; j < cols; ++j) {
            data[i][j] = 0.0;
        }
    }
}

// 3. Hafta: Matris bellek sızıntılarının önlenmesi için yıkıcı (destructor)
Matrix::~Matrix() {
    if (data != NULL) {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i]; // Her satırın dizisini siler 
        }
        delete[] data; // Ana işaretçi dizisini siler
    }
}

// 4-5. Hafta: Matrix kopyalama yapıcılarının derin kopyalama ile yazılması
Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
    data = new double*[rows];
    for (int i = 0; i < rows; ++i) {
        data[i] = new double[cols];
        for (int j = 0; j < cols; ++j) {
            data[i][j] = other.data[i][j]; 
        }
    }
}

// Getter ve Setter Metotları 
int Matrix::getRows() const { return rows; }
int Matrix::getCols() const { return cols; }

void Matrix::setValue(int r, int c, double val) {
    if (r >= 0 && r < rows && c >= 0 && c < cols) {
        data[r][c] = val;
    }
}

double Matrix::getValue(int r, int c) const {
    if (r >= 0 && r < rows && c >= 0 && c < cols) {
        return data[r][c];
    }
    return 0.0;
}

// 6. Hafta: Matris çarpımı fonksiyonlarında referans kullanımı 
Matrix Matrix::multiply(const Matrix& other) const {
    if (this->cols != other.getRows()) {
        throw DimensionMismatchException(
            "Carpim kurali ihlali! Matris A Sutun (" + std::to_string(this->cols) + 
            ") ile Matris B Satir (" + std::to_string(other.getRows()) + ") esit olmalidir!" 
        );
    }

    Matrix result(this->rows, other.getCols());
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < other.getCols(); ++j) {
            double sum = 0.0;
            for (int k = 0; k < this->cols; ++k) {
                sum += this->data[i][k] * other.getValue(k, j);
            }
            result.setValue(i, j, sum);
        }
    }
    return result;
}

// 9. Hafta: Matrix sınıfı için + operatörünün aşırı yüklenmesi 
Matrix Matrix::operator+(const Matrix& other) const {
    // Mantıksal operatör kontrolü temizlendi ve düzeltildi
    if (this->rows != other.getRows() || this->cols != other.getCols()) {
        throw DimensionMismatchException("Matris toplama islemi icin boyutlar ayni olmalidir!");
    }
    Matrix result(this->rows, this->cols);
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->cols; ++j) {
            result.setValue(i, j, this->data[i][j] + other.getValue(i, j));
        }
    }
    return result;
}

// 14. Hafta: SOLID uyarınca matrisin kendi verisini dosyaya yazması
void Matrix::saveToFile(std::ofstream& file) const {
    file << rows << " " << cols << "\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file << data[i][j] << " ";
        }
        file << "\n";
    }
}

void Matrix::loadFromFile(std::ifstream& file) {
    int r, c;
    if (file >> r >> c) {
        for (int i = 0; i < rows; ++i) delete[] data[i];
        delete[] data;

        rows = r; cols = c;
        data = new double*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new double[cols];
            for (int j = 0; j < cols; ++j) {
                file >> data[i][j];
            }
        }
    }
}

void Matrix::print() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << std::setw(10) << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}