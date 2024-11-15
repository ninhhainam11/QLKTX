#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "phong.h"

Phong* danhSachPhong = NULL;

// Ham them phong
void themPhong() {
    Phong* newPhong = (Phong*)malloc(sizeof(Phong));
    newPhong->next = NULL;

    printf("Nhap ma phong: ");
    scanf("%s", newPhong->maPhong);
    printf("Nhap so phong: ");
    scanf("%d", &newPhong->soPhong);
    printf("Nhap toa nha: ");
    scanf("%s", newPhong->toaNha);

    newPhong->next = danhSachPhong;
    danhSachPhong = newPhong;

    // Save the updated list to file
    luuDanhSachPhong();
}

// Ham sua phong
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

        // Save the updated list to file
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
        printf("Da xoa phong.\n");

        // Save the updated list to file
        luuDanhSachPhong();
    } else {
        printf("Khong tim thay phong.\n");
    }
}

// Ham them sinh vien vao phong


// Ham hien thi danh sach phong
void hienThiDanhSachPhong() {
    Phong* p = danhSachPhong;
    printf("Danh sach phong:\n");
    while (p != NULL) {
        printf("Ma phong: %s, So phong: %d, Toa nha: %s\n", p->maPhong, p->soPhong, p->toaNha);
        p = p->next;
    }
}

// Giai phong bo nho cua toan bo danh sach phong va sinh vien
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
        fprintf(file, "%s %d %s\n", p->maPhong, p->soPhong, p->toaNha);
        fprintf(file, "-\n");
        p = p->next;
    }

    fclose(file);
    printf("Da luu danh sach phong.\n");
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
        if (fscanf(file, "%s %d %s\n", newPhong->maPhong, &newPhong->soPhong, newPhong->toaNha) != 3) {
            free(newPhong);
            break;
        }
        newPhong->next = danhSachPhong;
        danhSachPhong = newPhong;

        // Doc ky tu "-" de xac nhan ket thuc mot phong
        char separator[2];
        fscanf(file, "%s", separator); // doc dau "-"

        if (strcmp(separator, "-") != 0) {
            printf("Dinh dang file khong hop le.\n");
            break;
        }
    }

    fclose(file);
    printf("Da tai danh sach phong.\n");
}


// Menu giao dien
void menuphong() {
    int choice;
    system("cls");
    taiDanhSachPhong();
    do {
        printf("\n===== MENU =====\n");
        printf("1. Them phong\n");
        printf("2. Sua phong\n");
        printf("3. Xoa phong\n");
        printf("4. Them sinh vien vao phong\n");
        printf("5. Xoa sinh vien khoi phong\n");
        printf("6. Hien thi sinh vien theo phong\n");
        printf("7. Hien thi danh sach phong\n");
        printf("8. Thoat\n");
        printf("Chon: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: themPhong(); break;
            case 2: suaPhong(); break;
            case 3: xoaPhong(); break;
//            case 4: themSinhVienVaoPhong(); break;
//            case 5: xoaSinhVienKhoiPhong(); break;
//            case 6: hienThiSinhVienTheoPhong(); break;
            case 7: hienThiDanhSachPhong(); break;
            case 8: giaiPhongBoNho(); break;
            default: printf("Chon sai, vui long chon lai.\n"); break;
        }
    } while (choice != 8);
}

