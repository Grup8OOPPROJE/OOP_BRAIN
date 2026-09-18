# 🧠 OOP-Brain: C++ Modüler Sinir Ağı Kütüphanesi

[cite_start]Bu proje, C++ dilinin Nesneye Yönelik Programlama (OOP) yetenekleri kullanılarak sıfırdan geliştirilmiş modüler, genişletilebilir ve sağlam bir yapay sinir ağı (ANN) kütüphanesidir[cite: 3]. [cite_start]Ağır matematiksel framework'lere bağımlı kalmadan, yapay zeka sistemlerinin temel taşlarını mimari bir yaklaşımla inşa etmeyi amaçlamaktadır[cite: 4].

Manisa Celal Bayar Üniversitesi (MCBÜ) Yapay Zeka ve Makine Öğrenmesi bölümü öğrencileri tarafından **Grup 8** proje görevi olarak tasarlanmıştır.

## 🚀 Proje Özellikleri

**Arayüz Tabanlı Tasarım (Interface-Based Design):** Polimorfizm kullanılarak yeni katmanların ve aktivasyon fonksiyonlarının (Sigmoid, ReLU) kolayca sisteme entegre edilebilmesi./n

**Dinamik Bellek Yönetimi:** Gelişmiş yapıcı (constructor) ve yıkıcı (destructor) metotlar ile "0 Memory Leak" hedefli güvenli bellek tahsisi.;/n
**Hata Yönetimi (Exception Handling):** Matris boyut uyuşmazlıkları gibi çalışma zamanı hatalarının `try-catch` mekanizmalarıyla güvenli bir şekilde yakalanması./n
**Model Kalıcılığı (Persistence):** SOLID prensiplerine uygun olarak, eğitilmiş veya ilklendirilmiş model ağırlıklarının `.txt` dosyalarına yazılması ve okunması (Dosya I/O)./n

## 📂 Klasör Mimarisi

Endüstri standardı modüler yapı kullanılmıştır:
`include/`: Sınıf tanımlamalarının bulunduğu başlık (`.h`) dosyaları (İskelet).
`src/`: Tüm fonksiyonların ve asıl mantığın bulunduğu kaynak (`.cpp`) dosyaları (Kaslar).
`data/`: Model ağırlıkları ve veri setleri (örn. Iris dataset).
`tests/`: Modüler birim testleri (Unit tests).
`docs/`: UML diyagramları, görev dağılımı (RACI matrisi) ve proje raporu.

## 👥 Ekip Üyeleri (Grup 8)
Proje, 14 haftalık müfredat boyunca profesyonel bir iş bölümü ile geliştirilmiştir[cite: 48, 51]:
**Baş Yazılım Mimarı & Sistem Entegratörü:** Eyüp Karakoç
**Matematik Motoru Geliştiricisi:** Ravza ibil
**Katman Uygulama Uzmanı:** Elif Azra İşbilir
**Veri ve Test Uzmanı:** Ozan Güneş

## 💻 Kurulum ve Çalıştırma (MSYS2 / g++)

Projeyi bilgisayarınızda derlemek ve test etmek için GCC derleyicisi (g++) gereklidir.

**1. Depoyu Klonlayın:**
```bash
git clone [https://github.com/Grup8OOPPROJE/OOP_BRAIN.git](https://github.com/Grup8OOPPROJE/OOP_BRAIN.git)
cd OOP_BRAIN