#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "phong.h"
#include "sinhvien.h"

SinhVien* danhSachSinhVien = NULL;

SinhVien* taoSinhVien(char* maSinhVien, char* hoTen, char* ngaySinh, char* lop, char* maPhong, char* gioiTinh) {
    SinhVien* sv = (SinhVien*)malloc(sizeof(SinhVien));
    strcpy(sv->maSinhVien, maSinhVien);
    strcpy(sv->hoTen, hoTen);
    strcpy(sv->ngaySinh, ngaySinh);
    strcpy(sv->lop, lop);
    strcpy(sv->gioiTinh, gioiTinh);
    strcpy(sv->maPhong, maPhong);
    sv->next = NULL;
    return sv;
}

int kiemTraNgaySinh(const char* ngaySinh) {
    int ngay, thang, nam;
    if (sscanf(ngaySinh, "%d/%d/%d", &ngay, &thang, &nam) == 3) {
        if (nam >= 1900 && nam <= 2024 && thang >= 1 && thang <= 12 && ngay >= 1 && ngay <= 31) {
            return 1;
        }
    }
    return 0;
}

SinhVien* timSinhVien(const char* maSinhVien) {
    SinhVien* p = danhSachSinhVien;
    while (p != NULL) {
        if (strcmp(p->maSinhVien, maSinhVien) == 0) {
            return p; 
        }
        p = p->next;
    }
    return NULL; 
}

void themSinhVien() {
    char maSinhVien[15], hoTen[50], ngaySinh[15], lop[50], maPhong[10], gioiTinh[10];
    Phong* phong = NULL;
    LoaiPhong* lp = NULL;

    fflush(stdin);

    do {
        printf("Nhap ma sinh vien: ");
        fgets(maSinhVien, sizeof(maSinhVien), stdin);
        maSinhVien[strcspn(maSinhVien, "\n")] = 0;
        if (strlen(maSinhVien) == 0) {
            printf("Ma sinh vien khong duoc de trong!\n");
        } else if (timSinhVien(maSinhVien)) {
            printf("Ma sinh vien da ton tai!\n");
        }
    } while (strlen(maSinhVien) == 0 || timSinhVien(maSinhVien));

    do {
        printf("Nhap ho ten: ");
        fgets(hoTen, sizeof(hoTen), stdin);
        hoTen[strcspn(hoTen, "\n")] = 0;
        if (strlen(hoTen) == 0) {
            printf("Ho ten khong duoc de trong!\n");
        }
    } while (strlen(hoTen) == 0);

    do {
        printf("Nhap ngay sinh (dd/mm/yyyy): ");
        fgets(ngaySinh, sizeof(ngaySinh), stdin);
        ngaySinh[strcspn(ngaySinh, "\n")] = 0;
        if (strlen(ngaySinh) == 0 || !kiemTraNgaySinh(ngaySinh)) {
            printf("Ngay sinh khong hop le! Vui long nhap lai.\n");
        }
    } while (strlen(ngaySinh) == 0 || !kiemTraNgaySinh(ngaySinh));

    do {
        printf("Nhap lop: ");
        fgets(lop, sizeof(lop), stdin);
        lop[strcspn(lop, "\n")] = 0;
        if (strlen(lop) == 0) {
            printf("Lop khong duoc de trong!\n");
        }
    } while (strlen(lop) == 0);

    do {
        printf("Nhap gioi tinh (Nam/Nu): ");
        fgets(gioiTinh, sizeof(gioiTinh), stdin);
        gioiTinh[strcspn(gioiTinh, "\n")] = 0;
        if (strcmp(gioiTinh, "Nam") != 0 && strcmp(gioiTinh, "Nu") != 0) {
            printf("Gioi tinh chi duoc nhap 'Nam' hoac 'Nu'!\n");
        }
    } while (strcmp(gioiTinh, "Nam") != 0 && strcmp(gioiTinh, "Nu") != 0);

    do {
        printf("Nhap ma phong: ");
        fgets(maPhong, sizeof(maPhong), stdin);
        maPhong[strcspn(maPhong, "\n")] = 0;

        phong = timPhong(maPhong);
        if (!phong) {
            printf("Ma phong khong ton tai!\n");
        } else {
            lp = timLoaiPhong(phong->loaiPhong);
            if (!lp) {
                printf("Loai phong khong ton tai!\n");
            } else if (phong->soSinhVienHienTai >= lp->soSinhVien) {
                printf("Phong da day sinh vien!\n");
            }
        }
    } while (strlen(maPhong) == 0 || !phong || !lp || phong->soSinhVienHienTai >= lp->soSinhVien);

    SinhVien* sv = taoSinhVien(maSinhVien, hoTen, ngaySinh, lop, maPhong, gioiTinh);
    sv->next = danhSachSinhVien;
    danhSachSinhVien = sv;

    phong->soSinhVienHienTai++;
    luuDanhSachPhong();
    luuDanhSachSinhVien();

    printf("Them sinh vien thanh cong!\n");
}



void hienThiDanhSachSinhVien() {
    SinhVien* p = danhSachSinhVien;
    if (!p) {
        printf("Danh sach sinh vien rong.\n");
        return;
    }

    printf("\n%-15s | %-50s | %-15s | %-10s | %-10s | %-10s\n", 
           "Ma SV", "Ho Ten", "Ngay Sinh", "Lop","Gioi Tinh", "Ma Phong" );
    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");

    while (p) {
        printf("%-15s | %-50s | %-15s | %-10s | %-10s | %-10s\n", 
        p->maSinhVien, p->hoTen, p->ngaySinh, p->lop, p->gioiTinh, p->maPhong);
        p = p->next;
    }

    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
}


void suaSinhVien() {
    char maSinhVien[15];
    char hoTen[50], ngaySinh[15], lop[50], gioiTinh[10], maPhong[10];
    Phong* phong = NULL;
    LoaiPhong* lp = NULL;

    fflush(stdin);

    do {
        printf("Nhap ma sinh vien can sua: ");
        fgets(maSinhVien, sizeof(maSinhVien), stdin);
        maSinhVien[strcspn(maSinhVien, "\n")] = 0;
        if (strlen(maSinhVien) == 0) {
            printf("Ma sinh vien khong duoc de trong!\n");
        }
    } while (strlen(maSinhVien) == 0);

    SinhVien* sv = timSinhVien(maSinhVien);
    if (!sv) {
        printf("Khong tim thay sinh vien voi ma: %s\n", maSinhVien);
        return;
    }

    printf("Nhap thong tin moi:\n");

    do {
        printf("Nhap ho ten: ");
        fgets(hoTen, sizeof(hoTen), stdin);
        hoTen[strcspn(hoTen, "\n")] = 0;
        if (strlen(hoTen) == 0) {
            printf("Ho ten khong duoc de trong!\n");
        }
    } while (strlen(hoTen) == 0);

    do {
        printf("Nhap ngay sinh (dd/mm/yyyy): ");
        fgets(ngaySinh, sizeof(ngaySinh), stdin);
        ngaySinh[strcspn(ngaySinh, "\n")] = 0;
        if (strlen(ngaySinh) == 0 || !kiemTraNgaySinh(ngaySinh)) {
            printf("Ngay sinh khong hop le! Vui long nhap lai.\n");
        }
    } while (strlen(ngaySinh) == 0 || !kiemTraNgaySinh(ngaySinh));

    do {
        printf("Nhap lop: ");
        fgets(lop, sizeof(lop), stdin);
        lop[strcspn(lop, "\n")] = 0;
        if (strlen(lop) == 0) {
            printf("Lop khong duoc de trong!\n");
        }
    } while (strlen(lop) == 0);

    do {
        printf("Nhap gioi tinh: ");
        fgets(gioiTinh, sizeof(gioiTinh), stdin);
        gioiTinh[strcspn(gioiTinh, "\n")] = 0;
        if (strlen(gioiTinh) == 0) {
            printf("Gioi tinh khong duoc de trong!\n");
        }
    } while (strlen(gioiTinh) == 0);

    do {
        printf("Nhap ma phong: ");
        fgets(maPhong, sizeof(maPhong), stdin);
        maPhong[strcspn(maPhong, "\n")] = 0;

        phong = timPhong(maPhong);
        if (!phong) {
            printf("Ma phong khong ton tai!\n");
        } else {
            lp = timLoaiPhong(phong->loaiPhong);
            if (!lp) {
                printf("Loai phong khong ton tai!\n");
            } else if (phong->soSinhVienHienTai >= lp->soSinhVien) {
                printf("Phong da day sinh vien!\n");
            }
        }
    } while (strlen(maPhong) == 0 || !phong || !lp || phong->soSinhVienHienTai >= lp->soSinhVien);

    strcpy(sv->hoTen, hoTen);
    strcpy(sv->ngaySinh, ngaySinh);
    strcpy(sv->gioiTinh, gioiTinh);
    strcpy(sv->lop, lop);
    

    if (strcmp(sv->maPhong, maPhong) != 0) {
        Phong* phongCu = timPhong(sv->maPhong);
        if (phongCu) {
            phongCu->soSinhVienHienTai--;
        }
        strcpy(sv->maPhong, maPhong);
        phong->soSinhVienHienTai++;
    }

    luuDanhSachSinhVien();
    luuDanhSachPhong();

    printf("Sua thong tin sinh vien thanh cong.\n");
}



void xoaSinhVien() {
    char maSinhVien[15];
    printf("Nhap ma sinh vien can xoa: ");
    scanf("%s", maSinhVien);

    SinhVien *p = danhSachSinhVien, *prev = NULL;
    while (p) {
        if (strcmp(p->maSinhVien, maSinhVien) == 0) {
            if (prev) {
                prev->next = p->next;
            } else {
                danhSachSinhVien = p->next;
            }
            free(p);
            printf("Xoa sinh vien thanh cong.\n");
            return;
        }
        prev = p;
        p = p->next;
    }
    luuDanhSachSinhVien();
    printf("Khong tim thay sinh vien voi ma: %s\n", maSinhVien);
}

void giaiPhongBoNhoSinhVien() {
    SinhVien* p = danhSachSinhVien;
    while (p) {
        SinhVien* temp = p;
        p = p->next;
        free(temp);
    }
    danhSachSinhVien = NULL;
}

void luuDanhSachSinhVien() {
    FILE* file = fopen("sinhvien.txt", "w");
    if (!file) {
        printf("Khong mo duoc file.\n");
        return;
    }

    SinhVien* p = danhSachSinhVien;
    while (p) {
        fprintf(file, "%s\n%s\n%s\n%s\n%s\n%s\n", 
                p->maSinhVien, 
                p->hoTen, 
                p->ngaySinh, 
                p->lop, 
                p->gioiTinh, 
                p->maPhong);
        p = p->next;
    }
    fclose(file);
    printf("Luu danh sach sinh vien thanh cong.\n");
}

void taiDanhSachSinhVien() {
    FILE* file = fopen("sinhvien.txt", "r");
    if (!file) {
        printf("Khong mo duoc file.\n");
        return;
    }

    char maSinhVien[15], hoTen[50], ngaySinh[15], lop[50], gioiTinh[10], maPhong[10];
    while (fscanf(file, "%s\n", maSinhVien) == 1) {
        fgets(hoTen, sizeof(hoTen), file);
        hoTen[strcspn(hoTen, "\n")] = 0; 

        fscanf(file, "%s\n", ngaySinh);
        fscanf(file, "%s\n", lop);
        fscanf(file, "%s\n", gioiTinh);
        fscanf(file, "%s\n", maPhong);

        SinhVien* sv = taoSinhVien(maSinhVien, hoTen, ngaySinh, lop, gioiTinh, maPhong);
        sv->next = danhSachSinhVien;
        danhSachSinhVien = sv;
    }
    fclose(file);
}


void hienThiSinhVienTheoMaSinhVien() {
    char maSinhVien[15];
    printf("Nhap ma sinh vien can tim: ");
    scanf("%s", maSinhVien);

    SinhVien* p = danhSachSinhVien;

    if (!p) {
        printf("Danh sach sinh vien rong.\n");
        return;
    }

    printf("\n%-15s | %-50s | %-15s | %-10s | %-10s | %-10s\n", 
           "Ma SV", "Ho Ten", "Ngay Sinh", "Lop", "Gioi Tinh", "Ma Phong");
    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");

    while (p) {
        if (strcmp(p->maSinhVien, maSinhVien) == 0) {
            printf("%-15s | %-50s | %-15s | %-10s | %-10s | %-10s\n", 
                   p->maSinhVien, 
                   p->hoTen, 
                   p->ngaySinh, 
                   p->lop, 
                   p->gioiTinh, 
                   p->maPhong);
            printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
            return;
        }
        p = p->next;
    }

    printf("Khong tim thay sinh vien co ma: %s\n", maSinhVien);
}



void menuSinhVien() {
    int choice;
    system("cls");
    do {
        printf("\n--- MENU QUAN LY SINH VIEN ---\n");
        printf("1. Them sinh vien\n");
        printf("2. Hien thi danh sach sinh vien\n");
        printf("3. Sua sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Hien thi sinh vien theo ma sinh vien\n");
        printf("0. Thoat\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: themSinhVien(); break;
            case 2: hienThiDanhSachSinhVien(); break;
            case 3: suaSinhVien(); break;
            case 4: xoaSinhVien(); break;
            case 5: hienThiSinhVienTheoMaSinhVien(); break;
            case 0: giaiPhongBoNhoSinhVien();break;
            default: printf("Lua chon sai, vui long chon lai.\n"); break;
        }
    } while (choice != 0);
}

