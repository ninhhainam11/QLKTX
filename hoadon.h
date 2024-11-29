#ifndef HOADON_H
#define HOADON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct HoaDon {
	char maHoaDon[20];
    char maPhong[50];
    int tienPhong;
    int tienDien;
    int tienNuoc;
    int tongTien;
    int daThanhToan;
    struct HoaDon *next; 
};

// Function declarations
void themHoaDon(struct HoaDon **danhSachHoaDon);
void suaHoaDon(struct HoaDon *danhSachHoaDon);
void xoaHoaDon(struct HoaDon **danhSachHoaDon);
void hienThiHoaDon(struct HoaDon *danhSachHoaDon);
void hienThiHoaDonTheoMaPhong(struct HoaDon *danhSachHoaDon, const char *maPhong);
void luuHoaDonVaoFile();
int kiemTraMaPhongTonTai(struct HoaDon *danhSachHoaDon, const char *maPhong);
void hienThiHoaDonChuaThanhToan();
void hienThiMenu();

#endif

