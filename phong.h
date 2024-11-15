#ifndef PHONG_H
#define PHONG_H


typedef struct Phong {
    char maPhong[10];
    int soPhong;
    char toaNha[50];
    struct Phong* next;
} Phong;

extern Phong* danhSachPhong;

// Function prototypes
void themPhong();
void suaPhong();
void xoaPhong();
void hienThiDanhSachPhong();
void giaiPhongBoNho();
void luuDanhSachPhong();
void taiDanhSachPhong();
void menuphong();

#endif // PHONG_H

