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
    LoaiPhong loaiPhong;
    struct Phong* next;
} Phong;

// External references
extern Phong* danhSachPhong;
extern LoaiPhong* danhSachLoaiPhong;

// Room functions
void themPhong();
void suaPhong();
void xoaPhong();
void hienThiDanhSachPhong();
void giaiPhongBoNho();
Phong* timPhong(const char* maPhong);
void luuDanhSachPhong();
void taiDanhSachPhong();
void menuphong();

// Room type functions
void themLoaiPhong();
void suaLoaiPhong();
void xoaLoaiPhong();
void hienThiDanhSachLoaiPhong();
void giaiPhongBoNhoLoaiPhong();
void luuDanhSachLoaiPhong();
void taiDanhSachLoaiPhong();

#endif // PHONG_H

