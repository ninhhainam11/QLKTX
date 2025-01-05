#include <stdio.h>
#include "phong.cpp"
int giaDien = 3;  
int giaNuoc = 2;  

void taiGia() {
    FILE *file = fopen("gia.txt", "r");
    if (file == NULL) {
        printf("Loi mo file. Su dung gia mac dinh.\n");
        return;
    }

 
    if (fscanf(file, "%d", &giaDien) != 1 || fscanf(file, "%d", &giaNuoc) != 1) {
        printf("Loi doc du lieu tu file.\n");
    }

    fclose(file);
}


void luuGia() {
    FILE *file = fopen("gia.txt", "w");
    if (file == NULL) {
        printf("Loi mo file.\n");
        return;
    }
    fprintf(file, "%d\n", giaDien);
    fprintf(file, "%d\n", giaNuoc);
    fclose(file);
    printf("Gia moi da duoc luu");
}


void hienThiGia() {
    printf("\nGia dien: %d VND\n", giaDien);
    printf("Gia nuoc: %d VND\n", giaNuoc);

    printf("\n%-15s | %-15s\n", "Ma Loai Phong", "Don Gia (VND)");
    printf("-------------------------------------\n");

    LoaiPhong* p = danhSachLoaiPhong;
    while (p != NULL) {
        printf("%-15d | %-15d\n", p->maLoaiPhong, p->donGia);
        p = p->next;
    }

    printf("-------------------------------------\n");
}



void thayDoiGiaDien() {
    int giaDienMoi;
    do {
        printf("Nhap gia dien moi: ");
        scanf("%d", &giaDienMoi);
        if (giaDienMoi <= 0) {
            printf("Gia dien phai lon hon 0. Vui long nhap lai.\n");
        }
    } while (giaDienMoi <= 0);

    giaDien = giaDienMoi;
    printf("Thay doi gia dien thanh cong. Gia moi: %d VND\n", giaDien);
    luuGia();  
}



void thayDoiGiaNuoc() {
    int giaNuocMoi;
    do {
        printf("Nhap gia nuoc moi: ");
        scanf("%d", &giaNuocMoi);
        if (giaNuocMoi <= 0) {
            printf("Gia nuoc phai lon hon 0. Vui long nhap lai.\n");
        }
    } while (giaNuocMoi <= 0);

    giaNuoc = giaNuocMoi;
    printf("Thay doi gia nuoc thanh cong. Gia moi: %d VND\n", giaNuoc);
    luuGia();  
}



void menuGia() {
    int choice;
	system("cls");
    do {
        printf("\n===== MENU QUAN LY GIA =====\n");
        printf("1. Thay doi gia dien\n");
        printf("2. Thay doi gia nuoc\n");
        printf("3. Hien thi gia\n");
        printf("0. Quay lai menu chinh\n");
        printf("Nhap lua chon: ");
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
                break;
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
        }
    } while (choice != 0);
}

