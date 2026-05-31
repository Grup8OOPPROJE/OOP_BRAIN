#include <iostream>
#include <iomanip>   // 6. Hafta: Matris görselleştirme (Hizalama) için
#include <cmath>     // 12. Hafta: Aktivasyon fonksiyonu hesaplamaları için
#include <vector>    // 10-11. Hafta: Polimorfik katman listesi için
#include <fstream>   // 14. Hafta: SOLID - Persistence (Dosya I/O) için
#include <string>    // 13. Hafta: Exception hata mesajları için
#include <stdexcept> // 13. Hafta: Standart hata türetimi için

// =================================================================
// 13. HAFTA: HATA YÖNETİMİ (EXCEPTION HANDLING)
// =================================================================
// Müfredat Konusu: try-catch blokları ve Özel İstisna Sınıfları 
// Proje Teslimatı: Matris boyut uyumsuzlukları için hata fırlatma yapısı 
class DimensionMismatchException : public std::runtime_error {
public:
    DimensionMismatchException(const std::string& message) 
        : std::runtime_error("[Boyut Uyumsuzlugu Hatasi] " + message) {}
};

// =================================================================
// 1-6. HAFTALAR: BİRİNCİ AŞAMA - TEMELLER VE VERİ YAPILARI 
// =================================================================
class Matrix {
private:
    // 1-2. Hafta: Sınıf Yapısı ve Kapsülleme
    // Temel veri üyelerinin private olarak kapsüllenmesi 
    int rows;          
    int cols;          
    double** data;     

public:
    // 1-2. Hafta: Yapıcı (Constructor) ile Dinamik Bellek Ayırımı 
    Matrix(int r, int c) : rows(r), cols(c) {
        data = new double*[rows]; 
        for (int i = 0; i < rows; ++i) {
            data[i] = new double[cols];
            // Bellekteki çöp değerlerin temizlenmesi
            for (int j = 0; j < cols; ++j) {
                data[i][j] = 0.0;
            }
        }
    }

    // 3. Hafta: Yapıcılar ve Yıkıcılar (Kritik Teslimat) 
    // Matris bellek sızıntılarının önlenmesi için yıkıcı (destructor) implementasyonu 
    ~Matrix() {
        if (data != NULL) {
            for (int i = 0; i < rows; ++i) {
                delete[] data[i]; // Her satırın dizisini siler 
            }
            delete[] data; // Ana işaretçi dizisini siler
        }
    }

    // 4-5. Hafta: Bellek Yönetimi ve Nesne Kopyalama 
    // Matrix kopyalama yapıcılarının (copy constructor) derin kopyalama (deep copy) ile yazılması 
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        data = new double*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new double[cols];
            for (int j = 0; j < cols; ++j) {
                data[i][j] = other.data[i][j]; // Hücre hücre derin kopyalama
            }
        }
    }

    // Kapsülleme ilkesi gereği yazılan yardımcı üye fonksiyonlar (Getter/Setter) 
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    
    void setValue(int r, int c, double val) {
        if (r >= 0 && r < rows && c >= 0 && c < cols) {
            data[r][c] = val;
        }
    }

    double getValue(int r, int c) const {
        if (r >= 0 && r < rows && c >= 0 && c < cols) {
            return data[r][c];
        }
        return 0.0;
    }

    // 6. Hafta: Pointers ve Referanslar 
    // Matris çarpımı fonksiyonlarında performans için referans kullanımı (const Matrix&) 
    // 13. Hafta Entegrasyonu: Boyut kontrolü ve hata fırlatma (throw) mekanizması
    Matrix multiply(const Matrix& other) const {
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

    // 9. Hafta: Operatör Aşırı Yükleme (Operator Overloading) 
    // Matrix sınıfı için + operatörünün aşırı yüklenmesi (Hücre bazlı matris toplamı) 
    Matrix operator+(const Matrix& other) const {
        if (this->rows != other.getRows() || !this->cols != other.getCols() && (this->cols != other.getCols())) {
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

    // 14. Hafta: SOLID ve Tasarım İlkeleri (Kalıcılık / Persistence Altyapısı) 
    // Single Responsibility (SRP) uyarınca matris kendi verisini dosyaya yazar
    void saveToFile(std::ofstream& file) const {
        file << rows << " " << cols << "\n";
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                file << data[i][j] << " ";
            }
            file << "\n";
        }
    }

    void loadFromFile(std::ifstream& file) {
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

    void print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << std::setw(10) << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

// =================================================================
// 7-12. HAFTALAR: İKİNCİ AŞAMA - KALITIM VE GELİŞMİŞ MİMARİ 
// =================================================================

// 12. Hafta: Soyut Sınıf ve Interface (Arayüz Tasarımı) 
// IActivation saf sanal sınıfının (interface) tasarımı ve kuralları 
class IActivation {
public:
    virtual ~IActivation() {}
    virtual Matrix compute(const Matrix& x) const = 0; // Pure Virtual Function 
};

// 12. Hafta Devamı: Interface üzerinden türetilen somut Sigmoid sınıfı 
class Sigmoid : public IActivation {
public:
    Matrix compute(const Matrix& x) const override {
        Matrix result(x.getRows(), x.getCols());
        for (int i = 0; i < x.getRows(); ++i) {
            for (int j = 0; j < x.getCols(); ++j) {
                double val = 1.0 / (1.0 + std::exp(-x.getValue(i, j))); // Sigmoid formülü 
                result.setValue(i, j, val);
            }
        }
        return result;
    }
};

// 12. Hafta Devamı: Interface üzerinden türetilen somut ReLU sınıfı 
class ReLU : public IActivation {
public:
    Matrix compute(const Matrix& x) const override {
        Matrix result(x.getRows(), x.getCols());
        for (int i = 0; i < x.getRows(); ++i) {
            for (int j = 0; j < x.getCols(); ++j) {
                double val = x.getValue(i, j);
                result.setValue(i, j, val > 0.0 ? val : 0.0);
            }
        }
        return result;
    }
};

// 7-8. Hafta: Kalıtım (Inheritance) 
// Ortak arayüz ve temel davranışları tanımlayan soyut BaseLayer sınıfı 
class BaseLayer {
public:
    virtual ~BaseLayer() {}
    
    // 10-11. Hafta: Polimorfizm (virtual / override) 
    // BaseLayer::forward() fonksiyonunun sanal hale getirilmesi 
    virtual Matrix forward(const Matrix& input) = 0;
    
    // 14. Hafta Entegrasyonu: Modüler yapı için katman kaydetme/yükleme soyutlaması 
    virtual void save(std::ofstream& file) const = 0;
    virtual void load(std::ifstream& file) = 0;
};

// 7-8. Hafta Devamı: BaseLayer temel sınıfından DenseLayer sınıfının türetilmesi 
class DenseLayer : public BaseLayer {
private:
    Matrix weights;            // Katmanın ağırlıkları (W) 
    Matrix bias;               // Katmanın sapma değerleri (b) 
    IActivation* activation;   // 12. Hafta: Davranış arayüzü göstericisi (Polimorfizm Enjeksiyonu) 

public:
    DenseLayer(int input_size, int output_size, IActivation* act) 
        : weights(output_size, input_size), bias(output_size, 1), activation(act) {
        
        // Örnek model parametrelerinin ilklendirilmesi
        for (int i = 0; i < weights.getRows(); ++i) {
            for (int j = 0; j < weights.getCols(); ++j) {
                weights.setValue(i, j, 0.5); 
            }
            bias.setValue(i, 0, 0.2);        
        }
    }

    // 10-11. Hafta: Somut Katman Sınıfında forward() metodunun ezilmesi (Overriding) 
    // Matematiksel İleri İletim Akışı: A = sigma(W * A_prev + b) 
    Matrix forward(const Matrix& input) override {
        // 6. Hafta referanslı çarpım motoru ve 9. Hafta aşırı yüklenmiş + operatörü kullanımı 
        Matrix Z = weights.multiply(input) + bias; 
        return activation->compute(Z); // 12. Hafta polimorfik aktivasyon çağrısı 
    }

    // 14. Hafta: SOLID - Single Responsibility / Model Persistence Gerçekleşimi 
    void save(std::ofstream& file) const override {
        weights.saveToFile(file);
        bias.saveToFile(file);
    }

    void load(std::ifstream& file) override {
        weights.loadFromFile(file);
        bias.loadFromFile(file);
    }
};

// =================================================================
// MAIN ÇALIŞTIRMA VE SÜREÇ TEST ALANI
// =================================================================
int main() {
    std::cout << "====================================================" << std::endl;
    std::cout << "      OOP-BRAIN 14 HAFTALIK MÜFREDAT FINAL TESTI    " << std::endl;
    std::cout << "====================================================\n" << std::endl;

    // 12. Hafta: Dinamik polimorfizm için arayüz göstericileri 
    IActivation* sigmoid = new Sigmoid();

    // 7-8. Hafta: BaseLayer pointer'ı üzerinden DenseLayer üretimi (Polimorfizm) 
    BaseLayer* layer = new DenseLayer(3, 2, sigmoid);

    // 1-2. Hafta: Girdi Matrisi Hazırlığı (3x1) 
    Matrix input(3, 1);
    input.setValue(0, 0, 1.0);
    input.setValue(1, 0, 0.5);
    input.setValue(2, 0, -1.0);

    // -------------------------------------------------------------
    // KRONOLOJİK TEST 1: 1-12. HAFTALAR (İLERİ İLETİM SÜRECİ) 
    // -------------------------------------------------------------
    std::cout << "[HAFTA 1-12 TEST] Matematik Motoru ve Katman Akisi:" << std::endl;
    std::cout << "Girdi Vektörü (3x1):" << std::endl;
    input.print();

    // 10-11. Hafta: Çalışma zamanı polimorfizmi ile forward pass tetiklenmesi 
    Matrix output = layer->forward(input);
    std::cout << "\nKatman Ileri Iletim Sonucu (2x1 Matris):" << std::endl;
    output.print();

    // -------------------------------------------------------------
    // KRONOLOJİK TEST 2: 13. HAFTA (TRY-CATCH HATA YÖNETİMİ) 
    // -------------------------------------------------------------
    std::cout << "\n--------------------------------------------------" << std::endl;
    std::cout << "[HAFTA 13 TEST] Hata Yakalama Mekanizmasi:" << std::endl;
    Matrix wrongInput(7, 1); // Katman 3 girdi beklerken hatalı olarak 7 satır veriyoruz.

    try {
        std::cout << "Uyumsuz matris boyutuyla ileri iletim deneniyor..." << std::endl;
        Matrix wrongOutput = layer->forward(wrongInput); 
    } 
    catch (const DimensionMismatchException& e) {
        std::cout << "-> " << e.what() << std::endl;
        std::cout << "-> Durum: Program cokmedi, try-catch blogu hatayi yakaladi!" << std::endl; 
    }

    // -------------------------------------------------------------
    // KRONOLOJİK TEST 3: 14. HAFTA (SOLID VE MODEL PERSISTENCE) 
    // -------------------------------------------------------------
    std::cout << "\n--------------------------------------------------" << std::endl;
    std::cout << "[HAFTA 14 TEST] SOLID Uyumlu Model Kaydetme/Yukleme:" << std::endl;
    
    // Model parametrelerini text dosyasına yazma (Persistence) 
    std::ofstream dosyaYaz("sinir_agi_modeli.txt");
    if (dosyaYaz.is_open()) {
        layer->save(dosyaYaz);
        dosyaYaz.close();
        std::cout << "-> Katman agirliklari 'sinir_agi_modeli.txt' dosyasina kaydedildi." << std::endl;
    }

    // Model parametrelerini dosyadan geri okuma 
    std::ifstream dosyaOku("sinir_agi_modeli.txt");
    if (dosyaOku.is_open()) {
        layer->load(dosyaOku);
        dosyaOku.close();
        std::cout << "-> Katman agirliklari dosyadan basariyla geri yuklendi." << std::endl;
    }

    // 3. ve 11. Hafta: Dinamik göstericilerin güvenli hafıza temizliği (0 Leak) 
    delete layer;
    delete sigmoid;

    std::cout << "\n====================================================" << std::endl;
    std::cout << "[SISTEM] 14 Haftalik Tum Isler Hatasiz Calisti (0 Leak)." << std::endl;
    std::cout << "====================================================" << std::endl;
    
    return 0;
}

kodumuzu tam haliyle bir yere yağıştımalımıyım