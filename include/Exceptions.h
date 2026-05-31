#pragma once
#include <stdexcept>
#include <string>

// 13. HAFTA: Özel İstisna Sınıfı
class DimensionMismatchException : public std::runtime_error {
public:
    DimensionMismatchException(const std::string& message) 
        : std::runtime_error("[Boyut Uyumsuzlugu Hatasi] " + message) {}
};