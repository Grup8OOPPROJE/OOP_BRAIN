#include <iostream>
#include <cassert>
#include "../include/Matrix.h"

int main() {
    std::cout << "--- MATRIX BIRIM TESTLERI BASLIYOR ---" << std::endl;

    // Test 1: Matris Boyutlari Dogru Mu?
    Matrix m1(2, 3);
    assert(m1.getRows() == 2 && m1.getCols() == 3);
    std::cout << "[BASARILI] Matris boyutlandirma." << std::endl;

    // Test 2: Deger Atama ve Okuma Dogru Mu?
    m1.setValue(0, 1, 5.5);
    assert(m1.getValue(0, 1) == 5.5);
    std::cout << "[BASARILI] Deger atama ve okuma." << std::endl;

    // Test 3: Toplama Islemi Hatasi Yakalaniyor Mu?
    Matrix m2(3, 3);
    try {
        Matrix m3 = m1 + m2;
        std::cerr << "[HATALI] Boyut uyusmazligi yakalanamadi!" << std::endl;
    } catch (const DimensionMismatchException& e) {
        std::cout << "[BASARILI] Beklenen hata yakalandi: " << e.what() << std::endl;
    }

    std::cout << "--- TUM TESTLER BASARIYLA GECTI ---" << std::endl;
    return 0;
}
