#include "../include/Layers.h"
#include <cmath>
#include <iostream>

// ==========================================
// 12. HAFTA: AKTİVASYON FONKSİYONLARI
// ==========================================

// Sigmoid Fonksiyonu: f(x) = 1 / (1 + e^-x)
Matrix Sigmoid::compute(const Matrix& x) const {
    Matrix result(x.getRows(), x.getCols());
    for (int i = 0; i < x.getRows(); ++i) {
        for (int j = 0; j < x.getCols(); ++j) {
            double val = 1.0 / (1.0 + std::exp(-x.getValue(i, j))); 
            result.setValue(i, j, val);
        }
    }
    return result;
}

// ReLU Fonksiyonu: f(x) = max(0, x)
Matrix ReLU::compute(const Matrix& x) const {
    Matrix result(x.getRows(), x.getCols());
    for (int i = 0; i < x.getRows(); ++i) {
        for (int j = 0; j < x.getCols(); ++j) {
            double val = x.getValue(i, j);
            result.setValue(i, j, val > 0.0 ? val : 0.0);
        }
    }
    return result;
}

// ==========================================
// 7-11. HAFTALAR: DENSE LAYER (TAM BAĞLANTILI KATMAN)
// ==========================================

// Yapıcı (Constructor): Ağırlık ve sapma matrislerini oluşturur
DenseLayer::DenseLayer(int input_size, int output_size, IActivation* act) 
    : weights(output_size, input_size), bias(output_size, 1), activation(act) {
    
    // Ağın ağırlıklarını (W) ve sapmalarını (b) başlangıç değerleriyle dolduruyoruz
    for (int i = 0; i < weights.getRows(); ++i) {
        for (int j = 0; j < weights.getCols(); ++j) {
            weights.setValue(i, j, 0.5); 
        }
        bias.setValue(i, 0, 0.2);        
    }
}

// İleri İletim (Forward Pass) Matematiği: A = Aktivasyon(W * X + b)
Matrix DenseLayer::forward(const Matrix& input) {
    Matrix Z = weights.multiply(input) + bias; 
    return activation->compute(Z); // Polimorfik çağrı
}

// 14. Hafta: SOLID - Model Dosyası Kaydetme
void DenseLayer::save(std::ofstream& file) const {
    weights.saveToFile(file);
    bias.saveToFile(file);
}

// 14. Hafta: SOLID - Model Dosyası Yükleme
void DenseLayer::load(std::ifstream& file) {
    weights.loadFromFile(file);
    bias.loadFromFile(file);
}