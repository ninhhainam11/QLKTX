#ifndef SINHVIEN_H
#define SINHVIEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Ngay{
	int ngay;
	int thang;
	int nam;
};

typedef struct SinhVien {
    char maSinhVien[10];
    char hoTen[50];
    char ngSinh[50];
    char lop[50];
    Ngay ngaysinh;
    struct SinhVien* next;
} SinhVien;

// Declaration of danhSachSinhVien (external reference)
extern SinhVien* danhSachSinhVien;

// Function prototypes
SinhVien* taoSinhVien(char* maSinhVien, char* hoTen, char* ngSinh, char* lop, char* maPhong);
void themSinhVien();
void hienThiDanhSachSinhVien();
SinhVien* timSinhVien(const char* maSinhVien);
void suaSinhVien();
void xoaSinhVien();
void giaiPhongBoNhoSinhVien();
void luuDanhSachSinhVien();
void taiDanhSachSinhVien();
void themSinhVienVaoPhong();
void chuyenPhongChoSinhVien();
void menusv();

#endif // SINHVIEN_H

