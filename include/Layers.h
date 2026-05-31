#pragma once
#include "Matrix.h"
#include "Activations.h"
#include <fstream>

// 7-8. Hafta: Ortak arayüz ve temel davranışları tanımlayan soyut sınıf
class BaseLayer {
public:
    virtual ~BaseLayer() {}
    
    // 10-11. Hafta: Polimorfizm için sanal fonksiyon
    virtual Matrix forward(const Matrix& input) = 0;
    
    // 14. Hafta: Model kaydetme/yükleme soyutlaması 
    virtual void save(std::ofstream& file) const = 0;
    virtual void load(std::ifstream& file) = 0;
};

// BaseLayer temel sınıfından türetilen Tam Bağlantılı Katman
class DenseLayer : public BaseLayer {
private:
    Matrix weights;            // Katmanın ağırlıkları (W) 
    Matrix bias;               // Katmanın sapma değerleri (b) 
    IActivation* activation;   // Polimorfik aktivasyon göstericisi

public:
    // Yapıcı (Constructor)
    DenseLayer(int input_size, int output_size, IActivation* act);

    // Ezilen (Overridden) fonksiyonlar
    Matrix forward(const Matrix& input) override;
    void save(std::ofstream& file) const override;
    void load(std::ifstream& file) override;
};