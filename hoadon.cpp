#include "hoadon.h"

struct HoaDon *danhSachHoaDon = NULL;
char maHoaDon[20];


// Kiem tra ma phong da ton tai hay chua
int kiemTraMaPhongTonTai(struct HoaDon *danhSachHoaDon, const char *maPhong) {
    struct HoaDon *current = danhSachHoaDon;
    while (current != NULL) {
        if (strcmp(current->maPhong, maPhong) == 0) {
            return 1; // Ma phong ton tai
        }
        current = current->next;
    }
    return 0; // Ma phong khong ton tai
}


void taoMaHoaDon(char *maHoaDon) {
    int soLuongHoaDon = 0;
    HoaDon* hd = danhSachHoaDon;

    // Count the number of invoices in the linked list
    while (hd != NULL) {
        soLuongHoaDon++;
        hd = hd->next;
    }

    sprintf(maHoaDon, "HD%04d", soLuongHoaDon + 1); 
}

// Them hoa don moi
void themHoaDon() {
    struct HoaDon *newHoaDon = (struct HoaDon*)malloc(sizeof(struct HoaDon));
    if (newHoaDon == NULL) {
        printf("Loi cap phat bo nho.\n");
        return;
    }

    printf("Nhap ma phong: ");
    scanf("%s", newHoaDon->maPhong);

    // Use timPhong to check if the room exists
    if (timPhong(newHoaDon->maPhong) == NULL) {
        printf("Phong %s khong ton tai. Khong the them hoa don.\n", newHoaDon->maPhong);
        free(newHoaDon);
        return;
    }

    if (kiemTraMaPhongTonTai(danhSachHoaDon, newHoaDon->maPhong)) {
        printf("Ma phong da ton tai, vui long nhap ma phong khac.\n");
        free(newHoaDon);
        return;
    }
	int soDien, soNuoc, soNgay;
	printf("Nhap so dien: ");
    scanf("%d", &soDien);
    printf("Nhap so nuoc: ");
    scanf("%d", &soNuoc);
    printf("Nhap so ngay o: ");
    scanf("%d", &soNgay);

    // Automatically assign predefined values
    taoMaHoaDon(newHoaDon -> maHoaDon);
    newHoaDon->tienPhong = giaDien*soDien;
    newHoaDon->tienDien = giaNuoc*soNuoc;
    newHoaDon->tienNuoc = giaPhong*soNgay;

    // Calculate the total amount
    newHoaDon->tongTien = newHoaDon->tienPhong + newHoaDon->tienDien + newHoaDon->tienNuoc;
    newHoaDon->daThanhToan=0;
    newHoaDon->next = danhSachHoaDon;
    danhSachHoaDon = newHoaDon;

    printf("Hoa don da duoc them thanh cong.\n");

    luuHoaDonVaoFile();
}

// Sua hoa don
void suaHoaDon(struct HoaDon *danhSachHoaDon) {
    char maPhong[50];
    printf("Nhap ma phong can sua: ");
    scanf("%s", maPhong);

    struct HoaDon *current = danhSachHoaDon;
    while (current != NULL) {
        if (strcmp(current->maPhong, maPhong) == 0) {
            int soDien, soNuoc, soNgay;
			printf("Nhap so dien: ");
		    scanf("%d", &soDien);
		    printf("Nhap so nuoc: ");
		    scanf("%d", &soNuoc);
		    printf("Nhap so ngay o: ");
		    scanf("%d", &soNgay);

			current->tienPhong = giaDien*soDien;
    		current->tienDien = giaNuoc*soNuoc;
    		current->tienNuoc = giaPhong*soNgay;

            current->tongTien = current->tienDien + current->tienNuoc + current->tienPhong;
            printf("Sua hoa don thanh cong.\n");
            luuHoaDonVaoFile();
            return;
        }
        current = current->next;
    }

    printf("Khong tim thay ma phong.\n");
}

// Xoa hoa don
void xoaHoaDon(struct HoaDon **danhSachHoaDon) {
    char maPhong[50];
    printf("Nhap ma phong can xoa: ");
    scanf("%s", maPhong);

    struct HoaDon *current = *danhSachHoaDon;
    struct HoaDon *previous = NULL;

    while (current != NULL && strcmp(current->maPhong, maPhong) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Khong tim thay ma phong.\n");
        return;
    }

    if (previous == NULL) {
        *danhSachHoaDon = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
    printf("Xoa hoa don thanh cong.\n");
    luuHoaDonVaoFile();
}

// Hien thi tat ca hoa don
void hienThiHoaDon(struct HoaDon *danhSachHoaDon) {
    struct HoaDon *current = danhSachHoaDon;

    if (current == NULL) {
        printf("Danh sach hoa don trong.\n");
        return;
    }

    while (current != NULL) {
    	printf("Ma hoa don", current -> maHoaDon);
        printf("\nMa phong: %s\n", current->maPhong);
        printf("Tien dien: %d\n", current->tienDien);
        printf("Tien nuoc: %d\n", current->tienNuoc);
        printf("Tien phong: %d\n", current->tienPhong);
        printf("Tong tien: %d\n", current->tongTien);
        printf("Trang thai thanh toan: %s\n", current->daThanhToan ? "Da thanh toan" : "Chua thanh toan");
        current = current->next;
    }
}

// Hien thi hoa don theo ma phong
void hienThiHoaDonTheoMaPhong(struct HoaDon *danhSachHoaDon, const char *maPhong) {
    struct HoaDon *current = danhSachHoaDon;

    while (current != NULL) {
        if (strcmp(current->maPhong, maPhong) == 0) {
            printf("\nMa phong: %s\n", current->maPhong);
            printf("Tien dien: %d\n", current->tienDien);
            printf("Tien nuoc: %d\n", current->tienNuoc);
            printf("Tien phong: %d\n", current->tienPhong);
            printf("Tong tien: %d\n", current->tongTien);
            printf("Trang thai thanh toan: %s\n", current->daThanhToan ? "Da thanh toan" : "Chua thanh toan");
            return;
        }
        current = current->next;
    }

    printf("Khong tim thay hoa don cho ma phong %s.\n", maPhong);
}

void thanhToanHoaDon() {
    char maPhong[50];
    printf("Nhap ma phong muon thanh toan: ");
    scanf("%s", maPhong);

    struct HoaDon *current = danhSachHoaDon;
    int found = 0;

    // Duy?t qua danh sách hóa don d? tìm phòng c?n thanh toán
    while (current != NULL) {
        if (strcmp(current->maPhong, maPhong) == 0) {
            // N?u tìm th?y phòng, thay d?i tr?ng thái thanh toán
            if (current->daThanhToan == 0) {
                current->daThanhToan = 1;  // Ðánh d?u là dã thanh toán
                printf("Hoa don cho ma phong %s da duoc thanh toan.\n", maPhong);
            } else {
                printf("Hoa don cho ma phong %s da duoc thanh toan truoc do.\n", maPhong);
            }
            found = 1;
            break;
        }
        current = current->next;
    }

    // N?u không tìm th?y hóa don cho mã phòng
    if (!found) {
        printf("Khong tim thay hoa don cho ma phong %s.\n", maPhong);
    }
}

void hienThiHoaDonChuaThanhToan() {
    if (danhSachHoaDon == NULL) {
        printf("Danh sach hoa don trong.\n");
        return;
    }

    int coHoaDonChuaThanhToan = 0; // Ð? ki?m tra n?u có hóa don chua thanh toán
    struct HoaDon *current = danhSachHoaDon;  // Duy?t qua danh sách mà không thay d?i danhSachHoaDon g?c

    while (current != NULL) {
        if (current->daThanhToan == 0) { // Ki?m tra tr?ng thái chua thanh toán
            if (!coHoaDonChuaThanhToan) {
                // N?u chua có hóa don chua thanh toán thì in tiêu d?
                printf("Danh sach hoa don chua thanh toan:\n");
                printf("%-20s %-10s %-10s %-10s %-10s\n", 
                       "Ma Phong", "Tien Phong", "Tien Dien", "Tien Nuoc", "Tong Tien");
            }
            coHoaDonChuaThanhToan = 1;
            printf("%-20s %-10.2f %-10.2f %-10.2f %-10.2f\n",
                   current->maPhong, current->tienPhong,
                   current->tienDien, current->tienNuoc,
                   current->tongTien);
        }
        current = current->next;  // Ti?n d?n hóa don ti?p theo
    }

    if (!coHoaDonChuaThanhToan) {
        printf("Khong co hoa don chua thanh toan.\n");
    }
}

void docHoaDonTuFile() {
    FILE *file = fopen("hoadon.txt", "r");
    if (file == NULL) {
        printf("Khong the mo tep hoadon.txt de doc.\n");
        return;
    }

    while (!feof(file)) {
        struct HoaDon *newHoaDon = (struct HoaDon *)malloc(sizeof(struct HoaDon));
        if (newHoaDon == NULL) {
            printf("Khong du bo nho de doc hoa don.\n");
            fclose(file);
            return;
        }

        int daThanhToanInt; // Bi?n t?m cho tr?ng thái thanh toán

        // Ð?c d? li?u t? t?p
        if (fscanf(file, "%s %s %f %f %f %f %d", newHoaDon -> maHoaDon,
                   newHoaDon->maPhong, &newHoaDon->tienPhong,
                   &newHoaDon->tienDien, &newHoaDon->tienNuoc,
                   &newHoaDon->tongTien, &daThanhToanInt) == 7) {
            newHoaDon->daThanhToan = daThanhToanInt; 
            newHoaDon->next = danhSachHoaDon;
            danhSachHoaDon = newHoaDon;
        } else {
            free(newHoaDon);
        }
    }

    fclose(file);
    printf("Doc danh sach hoa don tu tep thanh cong.\n");
}


// Luu hoa don vao tep
void luuHoaDonVaoFile() {
    FILE *file = fopen("hoadon.txt", "w");
    if (file == NULL) {
        printf("Loi khi mo tep.\n");
        return;
    }

    struct HoaDon *current = danhSachHoaDon;
    while (current != NULL) {
        fprintf(file, "%s %s %d %d %d %d %d\n", current -> maHoaDon,
                current->maPhong, current->tienPhong,
                current->tienDien, current->tienNuoc,
                current->tongTien, current->daThanhToan);
        current = current->next;
    }

    fclose(file);
    printf("Hoa don da duoc luu vao tep.\n");
}

// Hien thi menu quan ly hoa don
void menuhoadon() {
    int choice;
    do {
        printf("\n--- Quan ly hoa don ---\n");
        printf("1. Them hoa don\n");
        printf("2. Sua hoa don\n");
        printf("3. Xoa hoa don\n");
        printf("4. Hien thi tat ca hoa don\n");
        printf("5. Hien thi hoa don theo ma phong\n");
        printf("6. Hien thi hoa don chua thanh toan\n");
        printf("7. Thanh toan hoa don\n");
        printf("0. Thoat\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                themHoaDon();
                break;
            case 2:
                suaHoaDon(danhSachHoaDon);
                break;
            case 3:
                xoaHoaDon(&danhSachHoaDon);
                break;
            case 4:
                hienThiHoaDon(danhSachHoaDon);
                break;
            case 5: {
                char maPhong[50];
                printf("Nhap ma phong: ");
                scanf("%s", maPhong);
                hienThiHoaDonTheoMaPhong(danhSachHoaDon, maPhong);
                break;
            }
            case 6:
            	hienThiHoaDonChuaThanhToan();
            	break;
            case 7:
            	thanhToanHoaDon();
            	break;
            case 0:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
                break;
        }
    } while (choice != 0);
}

