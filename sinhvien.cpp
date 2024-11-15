#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sinhvien.h"


// Function Implementations
void initlist(struct list *l) {
    l->Head = NULL;
}

struct node *createnode(struct SinhVien data) {
    struct node *nd = (struct node *)malloc(sizeof(struct node));
    if (nd == NULL) {
        printf("Loi cap phat bo nho \n");
        return NULL;
    }
    nd->data = data;
    nd->next = NULL;
    return nd;
}

void docDanhSachSinhVien(struct list *l) {
    FILE *file = fopen("sinhvien.txt", "r");
    if (file == NULL) {
        printf("Khong the mo tep tin de doc!\n");
        return;
    }

    struct SinhVien sv;
    while (fscanf(file, "%s %s %s %s %s",
                  sv.maSinhVien, sv.hoTen, sv.ngSinh, sv.lop, sv.maPhong) == 5) {
        struct node *nd = createnode(sv);
        if (nd == NULL) {
            fclose(file);
            return;
        }

        nd->next = l->Head;
        l->Head = nd;
    }

    fclose(file);
}

void ghiDanhSachSinhVien(struct list *l) {
    FILE *file = fopen("sinhvien.txt", "w");
    if (file == NULL) {
        printf("Khong the mo tep tin de ghi!\n");
        return;
    }

    struct node *current = l->Head;
    while (current != NULL) {
        fprintf(file, "%s %s %s %s %s\n",
                current->data.maSinhVien,
                current->data.hoTen,
                current->data.ngSinh,
                current->data.lop,
                current->data.maPhong);
        current = current->next;
    }

    fclose(file);
}

void themSinhVien(struct list *l) {
    struct SinhVien sv;

    printf("\nNhap ma sinh vien: ");
    fgets(sv.maSinhVien, sizeof(sv.maSinhVien), stdin);
    sv.maSinhVien[strcspn(sv.maSinhVien, "\n")] = '\0';

    printf("\nNhap ho ten sinh vien: ");
    fgets(sv.hoTen, sizeof(sv.hoTen), stdin);
    sv.hoTen[strcspn(sv.hoTen, "\n")] = '\0';

    printf("\nNhap ngay sinh cua sinh vien: ");
    fgets(sv.ngSinh, sizeof(sv.ngSinh), stdin);
    sv.ngSinh[strcspn(sv.ngSinh, "\n")] = '\0';

    printf("\nNhap lop cua sinh vien: ");
    fgets(sv.lop, sizeof(sv.lop), stdin);
    sv.lop[strcspn(sv.lop, "\n")] = '\0';

    printf("\nNhap ma phong cua sinh vien: ");
    fgets(sv.maPhong, sizeof(sv.maPhong), stdin);
    sv.maPhong[strcspn(sv.maPhong, "\n")] = '\0';

    struct node *nd = createnode(sv);
    if (nd == NULL) return;

    nd->next = l->Head;
    l->Head = nd;

    ghiDanhSachSinhVien(l);
    printf("Sinh vien da duoc them vao danh sach.\n");
}

void hienthiDanhSachSinhVien(struct list *l) {
    struct node *current = l->Head;
    if (current == NULL) {
        printf("Danh sach sinh vien trong!\n");
        return;
    }

    printf("\n--- Danh sach sinh vien ---\n");
    while (current != NULL) {
        printf("\nMa sinh vien: %s\n", current->data.maSinhVien);
        printf("Ho ten: %s\n", current->data.hoTen);
        printf("Ngay sinh: %s\n", current->data.ngSinh);
        printf("Lop: %s\n", current->data.lop);
        printf("Ma phong: %s\n", current->data.maPhong);
        printf("----------------------------------\n");
        current = current->next;
    }
}

struct node *timSinhVien(struct list *l, const char *maSinhVien) {
    struct node *current = l->Head;
    while (current != NULL) {
        if (strcmp(current->data.maSinhVien, maSinhVien) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void suaSinhVien(struct list *l) {
    char maSinhVien[10];
    printf("\nNhap ma sinh vien can sua: ");
    fgets(maSinhVien, sizeof(maSinhVien), stdin);
    maSinhVien[strcspn(maSinhVien, "\n")] = '\0';

    struct node *svNode = timSinhVien(l, maSinhVien);
    if (svNode == NULL) {
        printf("Khong tim thay sinh vien trong danh sach\n");
        return;
    }

    printf("\nNhap lai thong tin sinh vien ma %s:\n", maSinhVien);
    printf("Nhap lai ho ten: ");
    fgets(svNode->data.hoTen, sizeof(svNode->data.hoTen), stdin);
    svNode->data.hoTen[strcspn(svNode->data.hoTen, "\n")] = '\0';

    printf("Nhap lai ngay sinh: ");
    fgets(svNode->data.ngSinh, sizeof(svNode->data.ngSinh), stdin);
    svNode->data.ngSinh[strcspn(svNode->data.ngSinh, "\n")] = '\0';

    printf("Nhap lai lop: ");
    fgets(svNode->data.lop, sizeof(svNode->data.lop), stdin);
    svNode->data.lop[strcspn(svNode->data.lop, "\n")] = '\0';

    printf("Nhap lai ma phong: ");
    fgets(svNode->data.maPhong, sizeof(svNode->data.maPhong), stdin);
    svNode->data.maPhong[strcspn(svNode->data.maPhong, "\n")] = '\0';

    ghiDanhSachSinhVien(l);
    printf("\nThong tin sinh vien da duoc sua.\n");
}

void xoaSinhVien(struct list *l) {
    char maSinhVien[10];
    printf("\nNhap ma sinh vien can xoa: ");
    fgets(maSinhVien, sizeof(maSinhVien), stdin);
    maSinhVien[strcspn(maSinhVien, "\n")] = '\0';

    struct node *current = l->Head;
    struct node *previous = NULL;
    while (current != NULL) {
        if (strcmp(current->data.maSinhVien, maSinhVien) == 0) {
            if (previous == NULL) {
                l->Head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            ghiDanhSachSinhVien(l);
            printf("Sinh vien da duoc xoa khoi danh sach.\n");
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("Sinh vien khong tim thay trong danh sach.\n");
}

void timVaInSinhVien(struct list *l) {
    char maSinhVien[10];
    printf("\nNhap ma sinh vien can tim: ");
    fgets(maSinhVien, sizeof(maSinhVien), stdin);
    maSinhVien[strcspn(maSinhVien, "\n")] = '\0';

    struct node *svNode = timSinhVien(l, maSinhVien);
    if (svNode == NULL) {
        printf("Sinh vien khong tim thay trong danh sach.\n");
    } else {
        printf("\nThong tin sinh vien voi ma %s:\n", maSinhVien);
        printf("Ma Sinh Vien: %s\n", svNode->data.maSinhVien);
        printf("Ho Ten: %s\n", svNode->data.hoTen);
        printf("Ngay Sinh: %s\n", svNode->data.ngSinh);
        printf("Lop: %s\n", svNode->data.lop);
        printf("Ma Phong: %s\n", svNode->data.maPhong);
    }
}

void menusv() {
    struct list l;
    initlist(&l);
    docDanhSachSinhVien(&l);

    int choice;
    do {
        printf("\n--- MENU QUAN LY SINH VIEN ---\n");
        printf("1. Them sinh vien\n");
        printf("2. Hien thi danh sach sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim sinh vien\n");
        printf("6. Thoat\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                themSinhVien(&l);
                break;
            case 2:
                hienthiDanhSachSinhVien(&l);
                break;
            case 3:
                suaSinhVien(&l);
                break;
            case 4:
                xoaSinhVien(&l);
                break;
            case 5:
                timVaInSinhVien(&l);
                break;
            case 6:
                printf("Thoat chuong trinh.\n");
                ghiDanhSachSinhVien(&l);
                break;
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
        }
    } while (choice != 6);
}

