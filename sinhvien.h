#ifndef SINHVIEN_H
#define SINHVIEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SinhVien {
    char maSinhVien[15];
    char hoTen[50];
	char ngaySinh[15];
    char lop[50];
    char gioiTinh[10];
    char maPhong[10];
    struct SinhVien* next;
} SinhVien;

extern SinhVien* danhSachSinhVien;

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
void menuSinhVien();

#endif

