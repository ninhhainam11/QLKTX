#ifndef PHONG_H
#define PHONG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LoaiPhong {
    int maLoaiPhong;
    int soSinhVien;
    int dienTich;
    int donGia;
    struct LoaiPhong* next; 
} LoaiPhong;

typedef struct Phong {
    char maPhong[10];
    int soPhong;
    char toaNha[50];
    int loaiPhong;
    int soSinhVienHienTai;
    struct Phong* next;
} Phong;

extern Phong* danhSachPhong;
extern LoaiPhong* danhSachLoaiPhong;

void menuPhong();
void themPhong();
void suaPhong();
void xoaPhong();
void hienThiDanhSachPhong();
void giaiPhongBoNho();
Phong* timPhong(const char* maPhong);
void luuDanhSachPhong();
void taiDanhSachPhong();
int kiemTraPhongTonTai(Phong* danhSachPhong, const char* maPhong);
void menuphong();
LoaiPhong* timLoaiPhong(int maLoaiPhong);
void themLoaiPhong();
void suaLoaiPhong();
void xoaLoaiPhong();
void hienThiDanhSachLoaiPhong();
void luuDanhSachLoaiPhong();
void taiDanhSachLoaiPhong();

#endif 

