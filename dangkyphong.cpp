#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "phong.h"
#include "sinhvien.h"


// Function to register a student to a room
void dangKyPhong() {
    char maSV[10], maPhong[10];
    printf("\n--- Dang ky phong cho sinh vien ---\n");
    printf("Nhap ma sinh vien: ");
    scanf("%s", maSV);

    // Check if student exists
    SinhVien* student = danhSachSinhVien;
    while (student != NULL) {
        if (strcmp(student->maSinhVien, maSV) == 0) {
            printf("Nhap ma phong: ");
            scanf("%s", maPhong);

            // Check if room exists
            Phong* room = danhSachPhong;
            while (room != NULL) {
                if (strcmp(room->maPhong, maPhong) == 0) {
                    strcpy(student->maPhong, maPhong);
                    printf("Sinh vien %s da duoc dang ky vao phong %s.\n", student->hoTen, maPhong);
                    return;
                }
                room = room->next;
            }
            printf("Phong %s khong ton tai.\n", maPhong);
            return;
        }
        student = student->next;
    }
    printf("Sinh vien %s khong ton tai.\n", maSV);
}

// Function to transfer a student to another room
void chuyenPhong() {
    char maSV[10], maPhongMoi[10];
    printf("\n--- Chuyen phong cho sinh vien ---\n");
    printf("Nhap ma sinh vien: ");
    scanf("%s", maSV);

    // Find student
    SinhVien* student = danhSachSinhVien;
    while (student != NULL) {
        if (strcmp(student->maSinhVien, maSV) == 0) {
            printf("Nhap ma phong moi: ");
            scanf("%s", maPhongMoi);

            // Check if room exists
            Phong* room = danhSachPhong;
            while (room != NULL) {
                if (strcmp(room->maPhong, maPhongMoi) == 0) {
                    strcpy(student->maPhong, maPhongMoi);
                    printf("Sinh vien %s da duoc chuyen den phong %s.\n", student->hoTen, maPhongMoi);
                    return;
                }
                room = room->next;
            }
            printf("Phong %s khong ton tai.\n", maPhongMoi);
            return;
        }
        student = student->next;
    }
    printf("Sinh vien %s khong ton tai.\n", maSV);
}

// Function to remove a student from a room
void xoaKhoiPhong() {
    char maSV[10];
    printf("\n--- Xoa sinh vien khoi phong ---\n");
    printf("Nhap ma sinh vien: ");
    scanf("%s", maSV);

    // Find student and remove from room
    SinhVien* student = danhSachSinhVien;
    while (student != NULL) {
        if (strcmp(student->maSinhVien, maSV) == 0) {
            // Remove student from room by clearing maPhong
            strcpy(student->maPhong, "");
            printf("Sinh vien %s da duoc xoa khoi phong.\n", student->hoTen);
            return;
        }
        student = student->next;
    }
    printf("Sinh vien %s khong ton tai.\n", maSV);
}
// Menu for room-related operations
void menudangkyphong() {
    int choice;
    taiDanhSachSinhVien();
    taiDanhSachPhong();
    do {
        printf("\n===== MENU DANG KY PHONG =====\n");
        printf("1. Dang ky phong cho sinh vien\n");
        printf("2. Chuyen phong cho sinh vien\n");
        printf("3. Xoa sinh vien khoi phong\n");
        printf("4. Quay lai menu chinh\n");
        printf("Chon: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                dangKyPhong();
                break;
            case 2:
                chuyenPhong();
                break;
            case 3:
                xoaKhoiPhong();
                break;
            case 4:
                printf("Quay lai menu chinh.\n");
                return;
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
        }
    } while (choice != 4);
}



