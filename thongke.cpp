#include <stdio.h>
#include "phong.h"
#include "sinhvien.h"
#include "hoadon.h"

void thongKeSinhVien() {
    int tongSinhVien = 0, soNam = 0, soNu = 0;

    SinhVien* sv = danhSachSinhVien;
    while (sv != NULL) {
        tongSinhVien++;
        if (sv->gioiTinh == "Nam") {
            soNam++;
        } else if (sv->gioiTinh == "Nu") {
            soNu++;
        }
        sv = sv->next;
    }

    printf("\n--- Thong ke sinh vien ---\n");
    printf("Tong so sinh vien: %d\n", tongSinhVien);
    printf("So sinh vien nam: %d\n", soNam);
    printf("So sinh vien nu: %d\n", soNu);
}

void thongKePhong() {
    int tongPhong = 0, phongTrong = 0, phongDay = 0;
    int loaiDienTichLon15 = 0, loaiDonGiaLon250k = 0;

    Phong* phong = danhSachPhong;
    while (phong != NULL) {
        tongPhong++;
        if (phong->soSinhVienHienTai < timLoaiPhong(phong->loaiPhong)->soSinhVien) {
            phongTrong++;
        } else {
            phongDay++;
        }

        LoaiPhong* loai = danhSachLoaiPhong;
        while (loai != NULL) {
            if (loai->maLoaiPhong == phong->loaiPhong) {
                if (loai->dienTich > 15) loaiDienTichLon15++;
                if (loai->donGia > 250000) loaiDonGiaLon250k++;
                break;
            }
            loai = loai->next;
        }

        phong = phong->next;
    }

    printf("\n--- Thong ke phong ---\n");
    printf("Tong so phong: %d\n", tongPhong);
    printf("So phong trong: %d\n", phongTrong);
    printf("So phong day: %d\n", phongDay);
    printf("So loai phong co dien tich > 15m2: %d\n", loaiDienTichLon15);
    printf("So loai phong co don gia > 250000 VND: %d\n", loaiDonGiaLon250k);
}

void thongKeHoaDon() {
    int soHoaDon = 0, daThanhToan = 0, chuaThanhToan = 0;
    int tongTienDien = 0, tongTienNuoc = 0, tongTienPhong = 0, tongDoanhThu = 0;

    HoaDon* hd = danhSachHoaDon;
    while (hd != NULL) {
        soHoaDon++;
        if (hd->daThanhToan) {
            daThanhToan++;
        } else {
            chuaThanhToan++;
        }

        tongTienDien += hd->tienDien;
        tongTienNuoc += hd->tienNuoc;
        tongTienPhong += hd->tienPhong;
        tongDoanhThu += hd->tongTien;

        hd = hd->next;
    }

    printf("\n--- Thong ke hoa don ---\n");
    printf("Tong so hoa don: %d\n", soHoaDon);
    printf("Tong so hoa don da thanh toan: %d\n", daThanhToan);
    printf("Tong so hoa don chua thanh toan: %d\n", chuaThanhToan);
    printf("Tong tien dien: %d VND\n", tongTienDien);
    printf("Tong tien nuoc: %d VND\n", tongTienNuoc);
    printf("Tong tien phong: %d VND\n", tongTienPhong);
    printf("Tong doanh thu: %d VND\n", tongDoanhThu);
}

void menuThongKe() {
    int choice;
    system("cls");
    do {
        printf("\n--- Menu Thong Ke ---\n");
        printf("1. Thong ke sinh vien\n");
        printf("2. Thong ke phong\n");
        printf("3. Thong ke hoa don\n");
        printf("0. Thoat\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: thongKeSinhVien(); break;
            case 2: thongKePhong(); break;
            case 3: thongKeHoaDon(); break;
            case 0: printf("Thoat menu thong ke.\n"); break;
            default: printf("Lua chon sai, vui long chon lai.\n"); break;
        }
    } while (choice != 0);
}

