# 🚗 Aplikasi Manajemen Rental Mobil  
Project akhir mata kuliah **Pemrograman Dasar (Progdas)**  
Dibuat menggunakan **C++ dengan konsep OOP** dan sistem penyimpanan berbasis file.

---

## 👥 Anggota Kelompok
Tambahkan nama anggota Anda:

1. Marchel Rianra Glendrikho Simanjuntak – 22/494013/TK/54157
2. Luthfi Hanif – 22/497890/TK/54589
3. Moh. Nazril Ilham - 22/493142/TK/54000

---

## 📌 Deskripsi Proyek
Aplikasi ini merupakan sistem sederhana untuk mengelola proses penyewaan mobil.  
Program menerapkan konsep **Object-Oriented Programming (OOP)** serta memanfaatkan penyimpanan file `.txt` sebagai basis data sederhana.

Aplikasi ini dapat:
- Memuat data awal dari **input.txt**
- Menambah, mengedit, dan menghapus kendaraan
- Menambah dan menampilkan data customer
- Membuat transaksi penyewaan dan pengembalian kendaraan
- Menyimpan data hasil modifikasi ke **output.txt**

---

## ✨ Fitur Utama
| Kode | Deskripsi Fitur |
|------|------------------------------|
| F-01 | Tambah kendaraan |
| F-02 | Edit tarif kendaraan |
| F-03 | Hapus kendaraan |
| F-04 | List semua kendaraan |
| F-05 | List kendaraan tersedia |
| F-06 | Tambah customer |
| F-07 | List customer |
| F-08 | Sewa kendaraan |
| F-09 | Kembalikan kendaraan |
| F-10 | Simpan data ke output.txt |
| F-11 | Muat ulang data dari input.txt |

---

## 🏗 Struktur Folder

```
Project/
│
├─ include/
│ ├─ Vehicle.h
│ ├─ Customer.h
│ ├─ Rental.h
│ ├─ Fleet.h
│ └─ FileManager.h
│
├─ src/
│ ├─ Vehicle.cpp
│ ├─ Customer.cpp
│ ├─ Rental.cpp
│ ├─ Fleet.cpp
│ ├─ FileManager.cpp
│ └─ main.cpp
│
├─ data/
│ ├─ input.txt # Data awal kendaraan
│ ├─ customers.txt # Data awal customer
│ ├─ output.txt # Hasil penyimpanan kendaraan
│ └─ customers_output.txt # Hasil penyimpanan customer
│
└─ README.md

```


---

## 🛠 Cara Kompilasi

### **Windows (MinGW)**
```bash 
g++ -std=gnu++11 src/*.cpp -I include -o rental.exe
```

### **Linux / MacOS**
```bash 
g++ -std=c++17 src/*.cpp -I include -o rental
```



---

## ▶️ Cara Menjalankan Program

```bash
./rental # Linux/MacOS
rental.exe # Windows
```

---

## 📂 Penjelasan File Input & Output

### **1. input.txt** → Dibaca saat program dimulai  
Contoh:

```bash
1,Toyota,Avanza,2018,280000.00,1
2,Toyota,Innova,2020,500000.00,1
```


### **2. output.txt** → Hasil penyimpanan (menu Simpan Data)  
Contoh:

```bash
1,Toyota,Avanza,2018,280000.00,1
2,Toyota,Innova,2020,500000.00,1
3,Toyota,Fortuner,2020,1000000.00,1
```

### **3. customers.txt / customers_output.txt**  
Format:

```bash
1,Marchel,082112345678
```

---

## 🧩 Arsitektur Program (OOP)

Program menerapkan desain modular:

| Class | Fungsi |
|--------|-------------------------------|
| **Vehicle** | Menyimpan data kendaraan |
| **Customer** | Menyimpan data pelanggan |
| **Rental** | Menghubungkan pelanggan & kendaraan |
| **Fleet** | Mengatur kumpulan kendaraan |
| **FileManager** | Load & save file (input/output) |
| **main.cpp** | Antarmuka menu & alur aplikasi |
