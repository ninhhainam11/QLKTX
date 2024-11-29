#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "phong.h"

Phong* danhSachPhong = NULL;
LoaiPhong* danhSachLoaiPhong = NULL;

void themPhong() {
    Phong* newPhong = (Phong*)malloc(sizeof(Phong));
    newPhong->next = NULL;

    printf("Nhap ma phong: ");
    scanf("%s", newPhong->maPhong);
    printf("Nhap so phong: ");
    scanf("%d", &newPhong->soPhong);
    printf("Nhap toa nha: ");
    scanf("%s", newPhong->toaNha);
    printf("Nhap loai phong: ");
    scanf("%d", &newPhong->loaiPhong);

    newPhong->next = danhSachPhong;
    danhSachPhong = newPhong;

    luuDanhSachPhong();
}

void suaPhong() {
    char maPhong[10];
    printf("Nhap ma phong can sua: ");
    scanf("%s", maPhong);

    Phong* p = danhSachPhong;
    while (p != NULL && strcmp(p->maPhong, maPhong) != 0) {
        p = p->next;
    }

    if (p != NULL) {
        printf("Nhap so phong moi: ");
        scanf("%d", &p->soPhong);
        printf("Nhap toa nha moi: ");
        scanf("%s", p->toaNha);
        printf("Nhap loai phong moi: ");
        scanf("%d", &p->loaiPhong);

        luuDanhSachPhong();
    } else {
        printf("Khong tim thay phong.\n");
    }
}

// Ham xoa phong
void xoaPhong() {
    char maPhong[10];
    printf("Nhap ma phong can xoa: ");
    scanf("%s", maPhong);

    Phong *p = danhSachPhong, *prev = NULL;
    while (p != NULL && strcmp(p->maPhong, maPhong) != 0) {
        prev = p;
        p = p->next;
    }

    if (p != NULL) {
        if (prev == NULL) {
            danhSachPhong = p->next;
        } else {
            prev->next = p->next;
        }
        free(p);
        printf("Da xoa phong.\n");

        luuDanhSachPhong();
    } else {
        printf("Khong tim thay phong.\n");
    }
}

// Ham hien thi danh sach phong
void hienThiDanhSachPhong() {
    Phong* p = danhSachPhong;
    printf("Danh sach phong:\n");
    while (p != NULL) {
        printf("Ma phong: %s, So phong: %d, Toa nha: %s, Loai phong: %d\n", p->maPhong, p->soPhong, p->toaNha, p->loaiPhong);
        p = p->next;
    }
}


void giaiPhongBoNho() {
    while (danhSachPhong != NULL) {
        Phong* tempPhong = danhSachPhong;
        danhSachPhong = danhSachPhong->next;
        free(tempPhong);
    }
}

// Ham luu danh sach vao file
void luuDanhSachPhong() {
    FILE* file = fopen("danhsachphong.txt", "w");
    if (file == NULL) {
        printf("Khong the mo file de ghi.\n");
        return;
    }

    Phong* p = danhSachPhong;
    while (p != NULL) {
        fprintf(file, "%s %d %s %d\n", p->maPhong, p->soPhong, p->toaNha,p->loaiPhong);
        p = p->next;
    }

    fclose(file);
}


// Ham tai danh sach phong tu file
void taiDanhSachPhong() {
    FILE* file = fopen("danhsachphong.txt", "r");
    if (file == NULL) {
        printf("Khong the mo file de doc.\n");
        return;
    }

    // Giai phong bo nho cu truoc khi tai du lieu moi
    giaiPhongBoNho();

    while (1) {
        Phong* newPhong = (Phong*)malloc(sizeof(Phong));
        if (fscanf(file, "%s %d %s %d\n", newPhong->maPhong, &newPhong->soPhong, newPhong->toaNha, &newPhong->loaiPhong) != 4) {
            free(newPhong);
            break;
        }
        newPhong->next = danhSachPhong;
        danhSachPhong = newPhong;

    }

    fclose(file);
    printf("Da tai danh sach phong.\n");
}

// Ham tim phong theo ma phong
Phong* timPhong(const char* maPhong) {
    Phong* p = danhSachPhong;
    while (p != NULL) {
        if (strcmp(p->maPhong, maPhong) == 0) {
            return p; // Tra ve con tro den phong neu tim thay
        }
        p = p->next;
    }
    return NULL; // Khong tim thay phong
}


// Add a room type
void themLoaiPhong() {
    LoaiPhong* newLoaiPhong = (LoaiPhong*)malloc(sizeof(LoaiPhong));
    newLoaiPhong->next = NULL;

    printf("Nhap ma loai phong: ");
    scanf("%d", &newLoaiPhong->maLoaiPhong);
    printf("Nhap so sinh vien: ");
    scanf("%d", &newLoaiPhong->soSinhVien);
    printf("Nhap dien tich: ");
    scanf("%d", &newLoaiPhong->dienTich);
    printf("Nhap don gia: ");
    scanf("%d", &newLoaiPhong->donGia);

    newLoaiPhong->next = danhSachLoaiPhong;
    danhSachLoaiPhong = newLoaiPhong;

    luuDanhSachLoaiPhong();
}

// Edit a room type
void suaLoaiPhong() {
    int maLoaiPhong;
    printf("Nhap ma loai phong can sua: ");
    scanf("%d", &maLoaiPhong);

    LoaiPhong* p = danhSachLoaiPhong;
    while (p != NULL && p->maLoaiPhong != maLoaiPhong) {
        p = p->next;
    }

    if (p != NULL) {
        printf("Nhap so sinh vien moi: ");
        scanf("%d", &p->soSinhVien);
        printf("Nhap dien tich moi: ");
        scanf("%d", &p->dienTich);
        printf("Nhap don gia moi: ");
        scanf("%d", &p->donGia);

        luuDanhSachLoaiPhong();
    } else {
        printf("Khong tim thay loai phong.\n");
    }
}

// Delete a room type
void xoaLoaiPhong() {
    int maLoaiPhong;
    printf("Nhap ma loai phong can xoa: ");
    scanf("%d", &maLoaiPhong);

    LoaiPhong *p = danhSachLoaiPhong, *prev = NULL;
    while (p != NULL && p->maLoaiPhong != maLoaiPhong) {
        prev = p;
        p = p->next;
    }

    if (p != NULL) {
        if (prev == NULL) {
            danhSachLoaiPhong = p->next;
        } else {
            prev->next = p->next;
        }
        free(p);
        printf("Da xoa loai phong.\n");

        luuDanhSachLoaiPhong();
    } else {
        printf("Khong tim thay loai phong.\n");
    }
}

// Display room type list
void hienThiDanhSachLoaiPhong() {
    LoaiPhong* p = danhSachLoaiPhong;
    printf("Danh sach loai phong:\n");
    while (p != NULL) {
        printf("Ma loai phong: %d, So sinh vien: %d, Dien tich: %d, Don gia: %d\n",
               p->maLoaiPhong, p->soSinhVien, p->dienTich, p->donGia);
        p = p->next;
    }
}

// Free memory for room types
void giaiPhongBoNhoLoaiPhong() {
    while (danhSachLoaiPhong != NULL) {
        LoaiPhong* temp = danhSachLoaiPhong;
        danhSachLoaiPhong = danhSachLoaiPhong->next;
        free(temp);
    }
}

// Save room types to file
void luuDanhSachLoaiPhong() {
    FILE* file = fopen("danhsachloaiphong.txt", "w");
    if (file == NULL) {
        printf("Khong the mo file de ghi.\n");
        return;
    }

    LoaiPhong* p = danhSachLoaiPhong;
    while (p != NULL) {
        fprintf(file, "%d %d %d %d\n", p->maLoaiPhong, p->soSinhVien, 
                p->dienTich, p->donGia);
        p = p->next;
    }

    fclose(file);
}

// Load room types from file
void taiDanhSachLoaiPhong() {
    FILE* file = fopen("danhsachloaiphong.txt", "r");
    if (file == NULL) {
        printf("Khong the mo file de doc.\n");
        return;
    }

    giaiPhongBoNhoLoaiPhong();

    while (1) {
        LoaiPhong* newLoaiPhong = (LoaiPhong*)malloc(sizeof(LoaiPhong));
        if (fscanf(file, "%d %d %d %d\n", &newLoaiPhong->maLoaiPhong,
                   &newLoaiPhong->soSinhVien, &newLoaiPhong->dienTich,
                   &newLoaiPhong->donGia) != 4) {
            free(newLoaiPhong);
            break;
        }
        newLoaiPhong->next = danhSachLoaiPhong;
        danhSachLoaiPhong = newLoaiPhong;
    }

    fclose(file);
    printf("Da tai danh sach loai phong.\n");
}



// Menu giao dien
void menuphong() {
    int choice;
    system("cls");
	
    do {
        printf("\n===== MENU =====\n");
        printf("1. Them phong\n");
        printf("2. Sua phong\n");
        printf("3. Xoa phong\n");
        printf("4. Hien thi danh sach phong\n");
        printf("5. Them loai phong\n");
        printf("6. Sua loai phong\n");
        printf("7. Xoa loai phong\n");
        printf("0. Thoat\n");
        printf("Chon: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: themPhong(); break;
            case 2: suaPhong(); break;
            case 3: xoaPhong(); break;
            case 4: hienThiDanhSachPhong(); break;
            case 5: themLoaiPhong();break;
            case 6: suaLoaiPhong();break;
            case 7: xoaLoaiPhong();break;
            case 0: giaiPhongBoNho(); break;
            default: printf("Chon sai, vui long chon lai.\n"); break;
        }
    } while (choice != 0);
}

