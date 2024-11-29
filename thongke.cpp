#include <stdio.h>
#include "phong.h"
#include "sinhvien.h"
#include "hoadon.h"


void thongKePhong() {
    int tongPhong = 0, phongDay = 0, phongTrong = 0;

    Phong* phong = danhSachPhong;
    while (phong != NULL) {
        tongPhong++;
        if (phong->loaiPhong.soSinhVien > 0) {
            phongDay++;
        } else {
            phongTrong++;
        }
        phong = phong->next;
    }

    printf("\n--- Thong ke phong ---\n");
    printf("Tong so phong: %d\n", tongPhong);
}

void thongKeHoaDon() {
    int soHoaDon = 0, daThanhToan = 0, chuaThanhToan = 0;

    HoaDon* hd = danhSachHoaDon;
    while (hd != NULL) {
        soHoaDon++;
        if (hd->daThanhToan) {
            daThanhToan++;
        } else {
            chuaThanhToan++;
        }
        hd = hd->next;
    }

    printf("\n--- Thong ke hoa don ---\n");
    printf("Tong so hoa don: %d\n", soHoaDon);
    printf("Tong so hoa don da thanh toan: %d\n", daThanhToan);
    printf("Tong so hoa don chua thanh toan: %d\n", chuaThanhToan);
}

void thongKeDoanhThu() {
    float tongDoanhThu = 0;

    HoaDon* hd = danhSachHoaDon;
    while (hd != NULL) {
        tongDoanhThu += hd->tongTien;
        hd = hd->next;
    }

    printf("\n--- Thong ke doanh thu ---\n");
    printf("Tong doanh thu: %.2f VND\n", tongDoanhThu);
}

// Menu th?ng kê
void menuthongke() {
    int choice;
    do {
        printf("\n--- Menu Thong Ke ---\n");
        printf("1. Thong ke sinh vien\n");
        printf("2. Thong ke phong\n");
        printf("3. Thong ke hoa don\n");
        printf("4. Thong ke doanh thu\n");
        printf("0. Thoat\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);

        switch (choice) {
//            case 1: thongKeSinhVien; break;
            case 2: thongKePhong(); break;
            case 3: thongKeHoaDon(); break;
            case 4: thongKeDoanhThu(); break;
            case 0: printf("Thoat menu thong ke.\n"); break;
            default: printf("Lua chon sai, vui long chon lai.\n"); break;
        }
    } while (choice != 0);
}

	
