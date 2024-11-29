#include <stdio.h>
#include "gia.h"

int giaDien = 3;  
int giaNuoc = 2;  
int giaPhong = 1000; 

void docGiaTuFile() {
    FILE *file = fopen("gia.txt", "r");
    if (file == NULL) {
        printf("Loi mo file. Su dung gia mac dinh.\n");
        return;
    }

 
    if (fscanf(file, "%d", &giaDien) != 1 || fscanf(file, "%d", &giaNuoc) != 1 || fscanf(file, "%d", &giaPhong) != 1) {
        printf("Loi doc du lieu tu file.\n");
    }

    fclose(file);
}


void ghiGiaVaoFile() {
    FILE *file = fopen("gia.txt", "w");
    if (file == NULL) {
        printf("Loi mo file.\n");
        return;
    }
    fprintf(file, "%d\n", giaDien);
    fprintf(file, "%d\n", giaNuoc);
    fprintf(file, "%d\n", giaPhong);
    fclose(file);
    printf("Gia moi da duoc luu");
}


void hienThiGia() {
    printf("Gia dien: %d VND\n", giaDien);
    printf("Gia nuoc: %d VND\n", giaNuoc);
    LoaiPhong* p = danhSachLoaiPhong;
    printf("Danh sach loai phong:\n");
    while (p != NULL) {
        printf("Ma loai phong: %d, Don gia: %d\n",
               p->maLoaiPhong, p->donGia);
        p = p->next;
    }
}


void thayDoiGiaDien() {
    printf("Nhap gia dien moi: ");
    scanf("%d", &giaDien);
    printf("Thay doi gia dien thanh cong. Gia moi: %d VND\n", giaDien);
    ghiGiaVaoFile();  // Save new prices to file
}


void thayDoiGiaNuoc() {
    printf("Nhap gia nuoc moi: ");
    scanf("%d", &giaNuoc);
    printf("Thay doi gia nuoc thanh cong. Gia moi: %d VND\n", giaNuoc);
    ghiGiaVaoFile();
}


void menugia() {
    int choice;
	system("cls");
    do {
        printf("\n===== MENU QUAN LY GIA =====\n");
        printf("1. Thay doi gia dien\n");
        printf("2. Thay doi gia nuoc\n");
        printf("3. Hien thi gia\n");
        printf("0. Quay lai menu chinh\n");
        printf("Chon: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                thayDoiGiaDien();
                break;
            case 2:
                thayDoiGiaNuoc();
                break;
            case 3:
            	hienThiGia();
            	break;
            case 0:
                printf("Quay lai menu chinh.\n");
                return;
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
        }
    } while (choice != 0);
}

