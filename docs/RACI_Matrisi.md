# OOP-Brain Projesi Görev Dağılımı (RACI Matrisi)

Bu belge, 4 kişilik ekibimizin C++ Sinir Ağı Kütüphanesi geliştirme sürecindeki rol ve sorumluluklarını tanımlar.

## Ekip Üyeleri ve Roller
* **Üye 1 (Baş Yazılım Mimarı & Sistem Entegratörü):** Sınıf hiyerarşisinin tasarımı, UML diyagramları ve tüm modüllerin `main.cpp` altında birleştirilmesi.
* **Üye 2 (Matematik Motoru Geliştiricisi):** `Matrix` sınıfının implementasyonu, bellek yönetimi (destructor/copy constructor) ve operatör aşırı yüklemeleri.
* **Üye 3 (Katman ve Aktivasyon Uzmanı):** `BaseLayer` soyutlaması, `DenseLayer` ileri iletim matematiği ve Polimorfik aktivasyon (Sigmoid, ReLU) arayüzleri.
* **Üye 4 (Veri, Dosya ve Test Sorumlusu):** Model ağırlıklarının dosyaya yazılması/okunması (Persistence), özel hata (Exception) sınıflarının tasarımı ve Valgrind/Birim test süreçleri.