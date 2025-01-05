#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hoadon.h"
#include "phong.h"


HoaDon *danhSachHoaDon = NULL;
char maHoaDon[20];

HoaDon* timHoaDon(const char *maPhong) {
    struct HoaDon *p = danhSachHoaDon;
    while (p != NULL) {
        if (strcmp(p->maPhong, maPhong) == 0) {
            return p;  
        }
        p = p->next;
    }
    return NULL;  
}


void taoMaHoaDon(char *maHoaDon) {
    int soLuongHoaDon = 0;
    HoaDon* hd = danhSachHoaDon;

    while (hd != NULL) {
        soLuongHoaDon++;
        hd = hd->next;
    }

    sprintf(maHoaDon, "HD%04d", soLuongHoaDon + 1); 
}

void themHoaDon() {
    struct HoaDon *p = (struct HoaDon*)malloc(sizeof(struct HoaDon));
    if (p == NULL) {
        printf("Loi cap phat bo nho.\n");
        return;
    }

    printf("Nhap ma phong: ");
    scanf("%s", p->maPhong);

    if (timPhong(p->maPhong) == NULL) {
        printf("Phòng %s không ton tai. Không the them hóa don.\n", p->maPhong);
        free(p); 
        return;
    }
    
    if (timHoaDon(p->maPhong)) {
        printf("Ma phong da ton tai, vui long nhap ma phong khac.\n");
        free(p); 
        return;
    }

    int soDien, soNuoc, soNgay;
    printf("Nhap so dien: ");
    if (scanf("%d", &soDien) != 1 || soDien < 0) {
        printf("So dien khong hop le.\n");
        free(p); 
        return;
    }

    printf("Nhap so nuoc: ");
    if (scanf("%d", &soNuoc) != 1 || soNuoc < 0) {
        printf("So nuoc khong hop le.\n");
        free(p);
        return;
    }

    printf("Nhap so ngay o: ");
    if (scanf("%d", &soNgay) != 1 || soNgay < 0) {
        printf("So ngay o khong hop le.\n");
        free(p); 
        return;
    }
	
    taoMaHoaDon(p->maHoaDon);
    
    p->tienDien = giaDien * soDien;
    p->tienNuoc = giaNuoc * soNuoc;
    
    int giaPhong = 0;
    Phong* phong = timPhong(p->maPhong);
    LoaiPhong* lp = timLoaiPhong(phong->loaiPhong);	
    
    p->tienPhong = lp->donGia * phong->soSinhVienHienTai * soNgay;
    

    p->tongTien = p->tienPhong + p->tienDien + p->tienNuoc;
    p->daThanhToan = 0;

    p->next = danhSachHoaDon;
    danhSachHoaDon = p;

    printf("Hoa don da duoc them thanh cong.\n");

    luuHoaDonVaoFile();
}



void suaHoaDon() {
    char maPhong[50];
    printf("Nhap ma phong can sua: ");
    scanf("%s", maPhong);

    struct HoaDon* p = timHoaDon(maPhong);  

    if (p != NULL) {
        int soDien, soNuoc, soNgay;

        printf("Nhap so dien: ");
        if (scanf("%d", &soDien) != 1 || soDien < 0) {
            printf("So dien khong hop le.\n");
            return;
        }

        printf("Nhap so nuoc: ");
        if (scanf("%d", &soNuoc) != 1 || soNuoc < 0) {
            printf("So nuoc khong hop le.\n");
            return;
        }

        printf("Nhap so ngay o: ");
        if (scanf("%d", &soNgay) != 1 || soNgay < 0) {
            printf("So ngay o khong hop le.\n");
            return;
        }

        p->tienDien = giaDien * soDien;
        p->tienNuoc = giaNuoc * soNuoc;
        
        int giaPhong = 0;
    	Phong* phong = timPhong(p->maPhong);
    	LoaiPhong* lp = timLoaiPhong(phong->loaiPhong);	
    
    	p->tienPhong = lp->donGia * phong->soSinhVienHienTai * soNgay;

        p->tongTien = p->tienDien + p->tienNuoc + p->tienPhong;

        printf("Sua hoa don thanh cong.\n");

        luuHoaDonVaoFile();
    } else {
        printf("Khong tim thay hoa don cho ma phong %s.\n", maPhong);
    }
}




void xoaHoaDon() {
    char maPhong[50];
    printf("Nhap ma phong can xoa: ");
    scanf("%s", maPhong);

    struct HoaDon* p = danhSachHoaDon;
    struct HoaDon* previous = NULL;

    while (p != NULL && strcmp(p->maPhong, maPhong) != 0) {
        previous = p;
        p = p->next;
    }

    if (p == NULL) {
        printf("Khong tim thay ma phong.\n");
        return;
    }

    if (previous == NULL) {
        danhSachHoaDon = p->next;
    } else {
        previous->next = p->next;
    }

    free(p);
    printf("Xoa hoa don thanh cong.\n");
    luuHoaDonVaoFile();
}


void hienThiHoaDon() {
    struct HoaDon* p = danhSachHoaDon;

    if (p == NULL) {
        printf("Danh sach hoa don trong.\n");
        return;
    }

    printf("\n%-15s | %-10s | %-10s | %-10s | %-10s | %-10s | %-20s\n", 
           "Ma Hoa Don", "Ma Phong", "Tien Dien", "Tien Nuoc", "Tien Phong", "Tong Tien", "Trang Thai Thanh Toan");
    printf("---------------------------------------------------------------------------------------------\n");

    while (p != NULL) {
        printf("%-15s | %-10s | %-10d | %-10d | %-10d | %-10d | %-20s\n", 
               p->maHoaDon, 
               p->maPhong, 
               p->tienDien, 
               p->tienNuoc, 
               p->tienPhong, 
               p->tongTien, 
               p->daThanhToan ? "Da thanh toan" : "Chua thanh toan");
        p = p->next;
    }

    printf("---------------------------------------------------------------------------------------------\n");
}


void thanhToanHoaDon() {
    char maPhong[50];
    printf("Nhap ma phong muon thanh toan: ");
    scanf("%s", maPhong);

    struct HoaDon *p = danhSachHoaDon;
    int found = 0;

    while (p != NULL) {
        if (strcmp(p->maPhong, maPhong) == 0) {
            if (p->daThanhToan == 0) {
                p->daThanhToan = 1; 
                printf("Hoa don cho ma phong %s da duoc thanh toan.\n", maPhong);
            } else {
                printf("Hoa don cho ma phong %s da duoc thanh toan truoc do.\n", maPhong);
            }
            found = 1;
            break;
        }
        p = p->next;
    }
	luuHoaDonVaoFile();
	
    if (!found) {
        printf("Khong tim thay hoa don cho ma phong %s.\n", maPhong);
    }
}

void hienThiHoaDonTheoMaPhong() {
    char maPhong[50];
    printf("Nhap ma phong: ");
    scanf("%s", maPhong);

    struct HoaDon* p = danhSachHoaDon;

    if (p == NULL) {
        printf("Danh sach hoa don trong.\n");
        return;
    }

    printf("\n%-15s | %-10s | %-10s | %-10s | %-10s | %-10s | %-20s\n", 
           "Ma Hoa Don", "Ma Phong", "Tien Dien", "Tien Nuoc", "Tien Phong", "Tong Tien", "Trang Thai Thanh Toan");
    printf("---------------------------------------------------------------------------------------------\n");

    while (p != NULL) {
        if (strcmp(p->maPhong, maPhong) == 0) {
            printf("%-15s | %-10s | %-10d | %-10d | %-10d | %-10d | %-20s\n", 
                   p->maHoaDon, 
                   p->maPhong, 
                   p->tienDien, 
                   p->tienNuoc, 
                   p->tienPhong, 
                   p->tongTien, 
                   p->daThanhToan ? "Da thanh toan" : "Chua thanh toan");
            printf("---------------------------------------------------------------------------------------------\n");
            return;
        }
        p = p->next;
    }

    printf("Khong tim thay hoa don cho ma phong %s.\n", maPhong);
}

void hienThiHoaDonChuaThanhToan() {
    struct HoaDon* p = danhSachHoaDon;

    if (p == NULL) {
        printf("Danh sach hoa don trong.\n");
        return;
    }

    printf("\n%-15s | %-10s | %-10s | %-10s | %-10s | %-10s | %-20s\n", 
           "Ma Hoa Don", "Ma Phong", "Tien Dien", "Tien Nuoc", "Tien Phong", "Tong Tien", "Trang Thai Thanh Toan");
    printf("---------------------------------------------------------------------------------------------\n");

    int found = 0;
    while (p != NULL) {
        if (!p->daThanhToan) {
            found = 1;
            printf("%-15s | %-10s | %-10d | %-10d | %-10d | %-10d | %-20s\n", 
                   p->maHoaDon, 
                   p->maPhong, 
                   p->tienDien, 
                   p->tienNuoc, 
                   p->tienPhong, 
                   p->tongTien, 
                   "Chua thanh toan");
        }
        p = p->next;
    }

    if (!found) {
        printf("Khong co hoa don chua thanh toan.\n");
    } else {
        printf("---------------------------------------------------------------------------------------------\n");
    }
}


void docHoaDonTuFile() {
    FILE *file = fopen("hoadon.txt", "r");
    if (file == NULL) {
        printf("Khong the mo tep hoadon.txt de doc.\n");
        return;
    }

    while (!feof(file)) {
        struct HoaDon *p = (struct HoaDon *)malloc(sizeof(struct HoaDon));
        if (p == NULL) {
            printf("Khong du bo nho de doc hoa don.\n");
            fclose(file);
            return;
        }

        int daThanhToanInt; 

        if (fscanf(file, "%s %s %d %d %d %d %d", p -> maHoaDon,
                   p->maPhong, &p->tienPhong,
                   &p->tienDien, &p->tienNuoc,
                   &p->tongTien, &daThanhToanInt) == 7) {
            p->daThanhToan = daThanhToanInt; 
            p->next = danhSachHoaDon;
            danhSachHoaDon = p;
        } else {
            free(p);
        }
    }

    fclose(file);
    printf("Doc danh sach hoa don tu tep thanh cong.\n");
}


void luuHoaDonVaoFile() {
    FILE *file = fopen("hoadon.txt", "w");
    if (file == NULL) {
        printf("Loi khi mo tep.\n");
        return;
    }

    struct HoaDon *p = danhSachHoaDon;
    while (p != NULL) {
        fprintf(file, "%s %s %d %d %d %d %d\n", p -> maHoaDon,
                p->maPhong, p->tienPhong,
                p->tienDien, p->tienNuoc,
                p->tongTien, p->daThanhToan);
        p = p->next;
    }

    fclose(file);
    printf("Hoa don da duoc luu vao tep.\n");
}

void menuHoaDon() {
    int choice;
    system("cls");
    do {
        printf("\n===== MENU QUAN LY HOA DON =====\n");
        printf("1. Them hoa don\n");
        printf("2. Sua hoa don\n");
        printf("3. Xoa hoa don\n");
        printf("4. Hien thi tat ca hoa don\n");
        printf("5. Hien thi hoa don theo ma phong\n");
        printf("6. Hien thi hoa don chua thanh toan\n");
        printf("7. Thanh toan hoa don\n");
        printf("0. Thoat\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                themHoaDon();
                break;
            case 2:
                suaHoaDon();
                break;
            case 3:
                xoaHoaDon();
                break;
            case 4:
                hienThiHoaDon();
                break;
            case 5: {
                hienThiHoaDonTheoMaPhong();
                break;
            }
            case 6:
            	hienThiHoaDonChuaThanhToan();
            	break;
            case 7:
            	thanhToanHoaDon();
            	break;
            case 0:
                break;
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
                break;
        }
    } while (choice != 0);
}

