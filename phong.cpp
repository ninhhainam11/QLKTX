#include "sinhvien.h"
#include "phong.h"

Phong* danhSachPhong = NULL;
LoaiPhong* danhSachLoaiPhong = NULL;

void taoMaPhong(char *maPhong) {
    int soLuongPhong = 0;
    Phong* phong = danhSachPhong;

    while (phong != NULL) {
        soLuongPhong++;
        phong = phong->next;
    }

    sprintf(maPhong, "P%04d", soLuongPhong + 1);
}

Phong* timPhong(const char* maPhong) {
    Phong* p = danhSachPhong;
    while (p != NULL) {
        if (strcmp(p->maPhong, maPhong) == 0) {
            return p; 
        }
        p = p->next;
    }
    return NULL; 
}

LoaiPhong* timLoaiPhong(int maLoaiPhong) {
    LoaiPhong* p = danhSachLoaiPhong;
    while (p != NULL) {
        if (p->maLoaiPhong == maLoaiPhong) {
            return p; 
        }
        p = p->next;
    }
    return NULL; 
}

void themPhong() {
    Phong* newPhong = (Phong*)malloc(sizeof(Phong));
    newPhong->next = NULL;
    newPhong->soSinhVienHienTai = 0;
    printf("Nhap so phong: ");
    scanf("%d", &newPhong->soPhong);
    printf("Nhap toa nha: ");
    scanf("%s", newPhong->toaNha);
    do{
    	printf("Nhap loai phong: ");
    	scanf("%d", &newPhong->loaiPhong);
    	if(!timLoaiPhong(newPhong->loaiPhong)){
    		printf("Loai phong nay khong ton tai. Vui long nhap la\n");
		}
	}while(!timLoaiPhong(newPhong->loaiPhong));
	
    
    taoMaPhong(newPhong->maPhong);
    newPhong->next = danhSachPhong;
    danhSachPhong = newPhong;

    luuDanhSachPhong();
}

void suaPhong() {
    char maPhong[10];
    printf("Nhap ma phong can sua: ");
    scanf("%s", maPhong);

    Phong* p = timPhong(maPhong);

    if (p != NULL) {
        printf("Nhap so phong moi (hien tai: %d): ", p->soPhong);
        scanf("%d", &p->soPhong);

        printf("Nhap toa nha moi (hien tai: %s): ", p->toaNha);
        scanf("%s", p->toaNha);

        do {
            printf("Nhap loai phong moi (hien tai: %d): ", p->loaiPhong);
            scanf("%d", &p->loaiPhong);
            if (!timLoaiPhong(p->loaiPhong)) {
                printf("Loai phong nay khong ton tai. Vui long nhap lai.\n");
            }
        } while (!timLoaiPhong(p->loaiPhong));

        luuDanhSachPhong();
        printf("Cap nhat phong thanh cong.\n");
    } else {
        printf("Khong tim thay phong.\n");
    }
}


void xoaPhong() {
    char maPhong[10];
    printf("Nhap ma phong can xoa: ");
    scanf("%s", maPhong);

    Phong* p = timPhong(maPhong);

    if (p != NULL) {
        Phong* prev = NULL;
        Phong* temp = danhSachPhong;

        while (temp != NULL && temp != p) {
            prev = temp;
            temp = temp->next;
        }

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

void hienThiDanhSachPhong() {
    Phong* p = danhSachPhong;
    if (!p) {
        printf("Danh sach phong rong.\n");
        return;
    }

    printf("\n%-10s | %-10s | %-20s | %-10s\n", 
           "Ma Phong", "So Phong", "Toa Nha", "Loai Phong");
    printf("-------------------------------------------------------------\n");

    while (p) {
        printf("%-10s | %-10d | %-20s | %-10d\n", 
               p->maPhong, p->soPhong, p->toaNha, p->loaiPhong);
        p = p->next;
    }

    printf("-------------------------------------------------------------\n");
}



void giaiPhongBoNho() {
    while (danhSachPhong != NULL) {
        Phong* tempPhong = danhSachPhong;
        danhSachPhong = danhSachPhong->next;
        free(tempPhong);
    }
    
    while (danhSachLoaiPhong != NULL) {
        LoaiPhong* temp = danhSachLoaiPhong;
        danhSachLoaiPhong = danhSachLoaiPhong->next;
        free(temp);
    }
}

void luuDanhSachPhong() {
    FILE* file = fopen("phong.txt", "w");
    if (file == NULL) {
        printf("Khong the mo file de ghi.\n");
        return;
    }

    Phong* p = danhSachPhong;
    while (p != NULL) {
        fprintf(file, "%s %d %s %d %d\n", p->maPhong, p->soPhong, p->toaNha, p->loaiPhong, p->soSinhVienHienTai);
        p = p->next;
    }

    fclose(file);
}

void taiDanhSachPhong() {
    FILE* file = fopen("phong.txt", "r");
    if (file == NULL) {
        printf("Khong the mo file de doc.\n");
        return;
    }

    giaiPhongBoNho();

    while (1) {
        Phong* newPhong = (Phong*)malloc(sizeof(Phong));
        if (fscanf(file, "%s %d %s %d %d\n", newPhong->maPhong, &newPhong->soPhong, newPhong->toaNha, &newPhong->loaiPhong, &newPhong->soSinhVienHienTai) != 5) {
            free(newPhong);
            break;
        }
        newPhong->next = danhSachPhong;
        danhSachPhong = newPhong;
    }

    fclose(file);
    printf("Da tai danh sach phong.\n");
}

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

void suaLoaiPhong() {
    int maLoaiPhong;
    printf("Nhap ma loai phong can sua: ");
    scanf("%d", &maLoaiPhong);

    LoaiPhong* p = timLoaiPhong(maLoaiPhong);

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

void xoaLoaiPhong() {
    int maLoaiPhong;
    printf("Nhap ma loai phong can xoa: ");
    scanf("%d", &maLoaiPhong);

    LoaiPhong* p = timLoaiPhong(maLoaiPhong); 

    if (p != NULL) {
        LoaiPhong *prev = NULL, *temp = danhSachLoaiPhong;

        while (temp != NULL && temp != p) {
            prev = temp;
            temp = temp->next;
        }

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

void hienThiDanhSachLoaiPhong() {
    LoaiPhong* p = danhSachLoaiPhong;

    if (!p) {
        printf("Danh sach loai phong rong.\n");
        return;
    }

    printf("\n%-15s | %-15s | %-15s | %-15s\n",
           "Ma Loai Phong", "So Sinh Vien", "Dien Tich", "Don Gia");
    printf("---------------------------------------------------------------\n");

    while (p) {
        printf("%-15d | %-15d | %-15d | %-15d\n",
               p->maLoaiPhong, p->soSinhVien, p->dienTich, p->donGia);
        p = p->next;
    }

    printf("---------------------------------------------------------------\n");
}

void luuDanhSachLoaiPhong() {
    FILE* file = fopen("loaiphong.txt", "w");
    if (file == NULL) {
        printf("Khong the mo file de ghi.\n");
        return;
    }

    LoaiPhong* p = danhSachLoaiPhong;
    while (p != NULL) {
        fprintf(file, "%d %d %d %d\n", p->maLoaiPhong, p->soSinhVien, p->dienTich, p->donGia);
        p = p->next;
    }

    fclose(file);
}

void taiDanhSachLoaiPhong() {
    FILE* file = fopen("loaiphong.txt", "r");
    if (file == NULL) {
        printf("Khong the mo file de doc.\n");
        return;
    }

    while (1) {
        LoaiPhong* newLoaiPhong = (LoaiPhong*)malloc(sizeof(LoaiPhong));
        if (fscanf(file, "%d %d %d %d\n", &newLoaiPhong->maLoaiPhong, &newLoaiPhong->soSinhVien, &newLoaiPhong->dienTich, &newLoaiPhong->donGia) != 4) {
            free(newLoaiPhong);
            break;
        }
        newLoaiPhong->next = danhSachLoaiPhong;
        danhSachLoaiPhong = newLoaiPhong;
    }

    fclose(file);
    printf("Da tai danh sach loai phong.\n");
}

void hienThiSinhVienTrongPhong() {
    char maPhong[10];
    printf("Nhap ma phong can tim sinh vien: ");
    scanf("%s", maPhong);

    SinhVien* current = danhSachSinhVien;
    int timThay = 0;

    printf("\n%-10s | %-20s | %-12s | %-10s | %-10s\n", 
           "Ma SV", "Ho Ten", "Ngay Sinh", "Lop", "Ma Phong");
    printf("--------------------------------------------------------------------\n");

    while (current != NULL) {
        if (strcmp(current->maPhong, maPhong) == 0) {
            printf("%-10s | %-20s | %-12s | %-10s | %-10s\n", 
                   current->maSinhVien, 
                   current->hoTen, 
                   current->ngaySinh, 
                   current->lop, 
                   current->maPhong);
            timThay = 1;
        }
        current = current->next;
    }

    if (!timThay) {
        printf("Khong tim thay sinh vien trong phong %s.\n", maPhong);
    }

    printf("--------------------------------------------------------------------\n");
}

void menuPhong() {
    int choice;
    system("cls");
	
    do {
        printf("\n===== MENU QUAN LY PHONG =====\n");
        printf("1. Them phong\n");
        printf("2. Sua phong\n");
        printf("3. Xoa phong\n");
        printf("4. Hien thi danh sach phong\n");
        printf("5. Them loai phong\n");
        printf("6. Sua loai phong\n");
        printf("7. Xoa loai phong\n");
        printf("8. Hien thi danh sach loai phong\n");
        printf("9. Hien thi sinh vien trong phong\n");
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
            case 8: hienThiDanhSachLoaiPhong(); break;
            case 9: hienThiSinhVienTrongPhong(); break;
            case 0: break;
            default: printf("Chon sai, vui long chon lai.\n"); break;
        }
    } while (choice != 0);
}

