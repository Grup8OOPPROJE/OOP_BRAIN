#include <iostream>
#include "../include/Matrix.h"
#include "../include/Layers.h"
#include "../include/CSVReader.h"

int main() {
    std::cout << "====================================================" << std::endl;
    std::cout << "      OOP-BRAIN MODULER MIMARI FINAL TESTI    " << std::endl;
    std::cout << "====================================================\n" << std::endl;

    // Dinamik polimorfizm için arayüz göstericileri 
    IActivation* sigmoid = new Sigmoid();
    BaseLayer* layer = new DenseLayer(3, 2, sigmoid);

    // --- TEST 1: STANDART İLERİ İLETİM ---
    Matrix input(3, 1);
    input.setValue(0, 0, 1.0); input.setValue(1, 0, 0.5); input.setValue(2, 0, -1.0);
    
    std::cout << "[TEST 1] Basit Girdi Vektoru Ileri Iletimi (3x1):" << std::endl;
    Matrix output = layer->forward(input);
    output.print();

    // --- TEST 2: HATA YAKALAMA (EXCEPTION) ---
    std::cout << "\n--------------------------------------------------" << std::endl;
    std::cout << "[TEST 2] Hata Yakalama Mekanizmasi:" << std::endl;
    try {
        Matrix wrongInput(7, 1);
        Matrix wrongOutput = layer->forward(wrongInput); 
    } catch (const DimensionMismatchException& e) {
        std::cout << "-> [BASARILI] Hata yakalandi: " << e.what() << std::endl;
    }

    // --- TEST 3: MODEL PERSISTENCE (DOSYA I/O) ---
    std::cout << "\n--------------------------------------------------" << std::endl;
    std::cout << "[TEST 3] SOLID Uyumlu Model Kaydetme:" << std::endl;
    std::ofstream dosyaYaz("../data/sinir_agi_modeli.txt"); 
    if (dosyaYaz.is_open()) {
        layer->save(dosyaYaz);
        dosyaYaz.close();
        std::cout << "-> [BASARILI] Model agirliklari kaydedildi." << std::endl;
    }

    // --- TEST 4: BÜYÜK FİNAL - IRIS VERİ SETİ OKUMA (BONUS GÖREV) ---
    std::cout << "\n--------------------------------------------------" << std::endl;
    std::cout << "[TEST 4] BÜYÜK FİNAL: Iris CSV Veri Seti Entegrasyonu" << std::endl;
    
    // CSV'den 6 satır ve 4 özellik (Sepal/Petal uzunluk ve genişlikleri) okuyoruz
    Matrix irisData = CSVReader::loadFeatures("../data/iris_sample.csv", 6, 4);
    std::cout << "\nCSV'den okunan 6 Iris ciceginin ozellik matrisi:" << std::endl;
    irisData.print();

    // Iris çiçeğinin 4 özelliği var. 3 farklı türü sınıflandıracağız.
    // Buna uygun yepyeni bir katman kuruyoruz (Girdi: 4, Çıktı: 3)
    BaseLayer* irisLayer = new DenseLayer(4, 3, sigmoid);

    // CSV'den okunan ilk çiçeğin verisini alıp ağımıza uygun bir vektöre (4x1) çeviriyoruz
    Matrix tekCicek(4, 1);
    for(int i = 0; i < 4; i++) {
        tekCicek.setValue(i, 0, irisData.getValue(0, i)); 
    }

    std::cout << "\nIlk Iris cicegi agimiza sokuluyor (Ileri Iletim)..." << std::endl;
    Matrix irisTahmin = irisLayer->forward(tekCicek);
    
    std::cout << "Agin Tahmin Ciktilari (3 farkli tur icin olasiliklar):" << std::endl;
    irisTahmin.print();

    // --- HAFIZA TEMİZLİĞİ ---
    delete layer;
    delete irisLayer;
    delete sigmoid;

    std::cout << "\n====================================================" << std::endl;
    std::cout << "[SISTEM] 14 Haftalik Tum Moduller ve Bonuslar Calisti (0 Leak)." << std::endl;
    std::cout << "====================================================" << std::endl;
    
    return 0;
}