#include <iostream>
#include "../include/Matrix.h"
#include "../include/Layers.h"

int main() {
    std::cout << "====================================================" << std::endl;
    std::cout << "      OOP-BRAIN MODULER MIMARI FINAL TESTI    " << std::endl;
    std::cout << "====================================================\n" << std::endl;

    // 12. Hafta: Dinamik polimorfizm için arayüz göstericileri 
    IActivation* sigmoid = new Sigmoid();

    // 7-8. Hafta: BaseLayer pointer'ı üzerinden DenseLayer üretimi
    BaseLayer* layer = new DenseLayer(3, 2, sigmoid);

    // Girdi Matrisi Hazırlığı (3x1) 
    Matrix input(3, 1);
    input.setValue(0, 0, 1.0);
    input.setValue(1, 0, 0.5);
    input.setValue(2, 0, -1.0);

    // --- TEST 1: İLERİ İLETİM ---
    std::cout << "[TEST 1] Matematik Motoru ve Katman Akisi:" << std::endl;
    std::cout << "Girdi Vektoru (3x1):" << std::endl;
    input.print();

    Matrix output = layer->forward(input);
    std::cout << "\nKatman Ileri Iletim Sonucu (2x1 Matris):" << std::endl;
    output.print();

    // --- TEST 2: HATA YAKALAMA (EXCEPTION) ---
    std::cout << "\n--------------------------------------------------" << std::endl;
    std::cout << "[TEST 2] Hata Yakalama Mekanizmasi:" << std::endl;
    Matrix wrongInput(7, 1); // Kasıtlı hatalı boyut

    try {
        std::cout << "Uyumsuz matris boyutuyla ileri iletim deneniyor..." << std::endl;
        Matrix wrongOutput = layer->forward(wrongInput); 
    } 
    catch (const DimensionMismatchException& e) {
        std::cout << "-> " << e.what() << std::endl;
        std::cout << "-> Durum: Program cokmedi, try-catch blogu hatayi yakaladi!" << std::endl; 
    }

    // --- TEST 3: MODEL PERSISTENCE (DOSYA I/O) ---
    std::cout << "\n--------------------------------------------------" << std::endl;
    std::cout << "[TEST 3] SOLID Uyumlu Model Kaydetme:" << std::endl;
    
    std::ofstream dosyaYaz("../data/sinir_agi_modeli.txt"); // data klasörüne kaydeder
    if (dosyaYaz.is_open()) {
        layer->save(dosyaYaz);
        dosyaYaz.close();
        std::cout << "-> Katman agirliklari 'data/sinir_agi_modeli.txt' dosyasina kaydedildi." << std::endl;
    }

    // Hafıza Temizliği (0 Leak)
    delete layer;
    delete sigmoid;

    std::cout << "\n====================================================" << std::endl;
    std::cout << "[SISTEM] Tum Moduller Basariyla Birlestirildi ve Calisti." << std::endl;
    std::cout << "====================================================" << std::endl;
    
    return 0;
}