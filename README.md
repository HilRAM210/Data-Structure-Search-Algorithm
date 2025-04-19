# Data-Structure-Search-Algorithm

**Nama:** Hilal Ramdani

**NIM:** 3337240071

**Mata Kuliah:** Struktur Data

**Kelas:** B

**Dosen Pengampu:** Cakra Adipura Wicaksana, S.T., M.T.

## Deskripsi Singkat Program

Program ini adalah aplikasi berbasis konsol (CLI) untuk mengelola dan mencari data paper ilmiah dengan implementasi *Linear Search* dan *Binary Search* dalam C++.

## Fitur Utama

1. *Memuat Data dari File*
   - Mendukung format CSV/TXT dengan pemisah karakter '|'
   - Struktur data: Sumber, Topik, Judul, Penulis, dan Tahun

2. *Menampilkan Semua Data*
   - Menampilkan data dalam bentuk tabel yang rapi
   - Menampilkan total jumlah paper yang ada

3. *Pencarian Data*
   - Mendukung dua metode pencarian:
     - *Linear Search*: Metode pencarian sekuensial dari awal hingga akhir data
     - *Binary Search*: Metode pencarian yang lebih efisien dengan data yang sudah terurut

4. *Kriteria Pencarian*
   - Pencarian berdasarkan judul
   - Pencarian berdasarkan tahun
   - Pencarian berdasarkan penulis

5. *Performa*
   - Menampilkan waktu eksekusi untuk tiap operasi pencarian
   - Menggunakan indeks untuk mempercepat pencarian binary search

## Struktur Program

Program menggunakan struktur Paper untuk menyimpan data setiap paper ilmiah dan berbagai algoritma pencarian untuk memfasilitasi pencarian data yang efisien. Program ini juga mengimplementasikan metode pengindeksan yang memungkinkan pencarian binary search yang lebih cepat.

## Cara Penggunaan

1. Pilih opsi "Muat Data" dan masukkan nama file data (CSV/TXT)
2. Gunakan menu "Tampilkan Semua Data" untuk melihat seluruh data
3. Gunakan menu "Pencarian" untuk mencari paper berdasarkan kriteria tertentu
   - Pilih metode pencarian (Linear atau Binary)
   - Pilih kriteria pencarian (Judul, Tahun, atau Penulis)
   - Masukkan kata kunci pencarian

Program ini dibuat dengan C++ dan memanfaatkan fitur seperti STL vectors, algoritma sorting, serta pengukuran waktu eksekusi menggunakan library chrono untuk analisis performa.
