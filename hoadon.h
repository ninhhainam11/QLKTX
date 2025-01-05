#ifndef HOADON_H
#define HOADON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HoaDon{
    char maHoaDon[20];
    char maPhong[50];
    int tienPhong;
    int tienDien;
    int tienNuoc;
    int tongTien;
    int daThanhToan;
} HoaDon;

typedef struct DanhSachHoaDon{
    HoaDon data;
    struct DanhSachHoaDon *next;
} DanhSachHoaDon;

void themHoaDon();
void suaHoaDon();
void xoaHoaDon();
void hienThiHoaDon();
void hienThiHoaDonTheoMaPhong();
void docHoaDonTuFile();
void luuHoaDonVaoFile();
int kiemTraMaPhongTonTai();
void hienThiHoaDonChuaThanhToan();
void menuHoaDon();

#endif

