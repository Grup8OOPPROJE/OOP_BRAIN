#pragma once
#include "Matrix.h"

// 12. Hafta: Soyut Sınıf ve Interface (Arayüz Tasarımı) 
class IActivation {
public:
    virtual ~IActivation() {}
    virtual Matrix compute(const Matrix& x) const = 0; // Pure Virtual Function 
};

// Interface üzerinden türetilen somut Sigmoid sınıfı 
class Sigmoid : public IActivation {
public:
    Matrix compute(const Matrix& x) const override;
};

// Interface üzerinden türetilen somut ReLU sınıfı 
class ReLU : public IActivation {
public:
    Matrix compute(const Matrix& x) const override;
};