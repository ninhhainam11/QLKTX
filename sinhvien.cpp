#include "sinhvien.h"
#include "phong.h"


SinhVien* danhSachSinhVien = NULL;

// Function to create a new SinhVien
// Function to create a new SinhVien
SinhVien* taoSinhVien(char* maSinhVien, char* hoTen, char* ngSinh, char* lop, char* maPhong) {
    SinhVien* sv = (SinhVien*)malloc(sizeof(SinhVien));
    strcpy(sv->maSinhVien, maSinhVien);
    strcpy(sv->hoTen, hoTen);
    
    // Parse ngSinh into ngaysinh structure (dd/mm/yyyy)
    sscanf(ngSinh, "%d/%d/%d", &sv->ngaysinh.ngay, &sv->ngaysinh.thang, &sv->ngaysinh.nam);

    strcpy(sv->lop, lop);
    strcpy(sv->maPhong, maPhong);
    sv->next = NULL;
    return sv;
}


// Add a new SinhVien
// Add a new SinhVien
void themSinhVien() {
    char maSinhVien[10], hoTen[50], ngSinh[50], lop[50], maPhong[10];
    Phong* phong = NULL;

    printf("Nhap ma sinh vien: ");
    scanf("%s", maSinhVien);

    printf("Nhap ho ten: ");
    getchar(); // Consume newline
    fgets(hoTen, sizeof(hoTen), stdin);
    strtok(hoTen, "\n"); // Remove trailing newline

    printf("Nhap ngay sinh (dd/mm/yyyy): ");
    scanf("%s", ngSinh);  // Input as string
    
    printf("Nhap lop: ");
    scanf("%s", lop);

    do {
        printf("Nhap ma phong: ");
        scanf("%s", maPhong);

        phong = timPhong(maPhong);
        if (!phong) {
            printf("Phong voi ma %s khong ton tai. Vui long nhap lai.\n", maPhong);
        }
    } while (!phong);

    // Create new SinhVien using the provided information
    SinhVien* sv = taoSinhVien(maSinhVien, hoTen, ngSinh, lop, maPhong);
    sv->next = danhSachSinhVien;
    danhSachSinhVien = sv;

    printf("Them sinh vien thanh cong.\n");
}


// Display all SinhVien in the list
void hienThiDanhSachSinhVien() {
    SinhVien* current = danhSachSinhVien;
    if (!current) {
        printf("Danh sach sinh vien rong.\n");
        return;
    }

    printf("\n--- Danh sach sinh vien ---\n");
    while (current) {
        printf("Ma Sinh Vien: %s\n", current->maSinhVien);
        printf("Ho Ten: %s\n", current->hoTen);
        printf("Ngay Sinh: %s\n", current->ngSinh);
        printf("Lop: %s\n", current->lop);
        printf("Ma Phong: %s\n", current->maPhong);
        printf("---------------------------\n");
        current = current->next;
    }
}

// Find a SinhVien by maSinhVien
SinhVien* timSinhVien(const char* maSinhVien) {
    SinhVien* current = danhSachSinhVien;
    while (current) {
        if (strcmp(current->maSinhVien, maSinhVien) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Update SinhVien information
void suaSinhVien() {
    char maSinhVien[10];
    char maPhong[10];
    Phong* phong = NULL;

    printf("Nhap ma sinh vien can sua: ");
    scanf("%s", maSinhVien);

    SinhVien* sv = timSinhVien(maSinhVien);
    if (!sv) {
        printf("Khong tim thay sinh vien voi ma: %s\n", maSinhVien);
        return;
    }

    printf("Nhap thong tin moi:\n");
    printf("Ho Ten: ");
    getchar(); // Consume newline
    fgets(sv->hoTen, sizeof(sv->hoTen), stdin);
    strtok(sv->hoTen, "\n");

    printf("Ngay Sinh (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &sv->ngaysinh.ngay, &sv->ngaysinh.thang, &sv->ngaysinh.nam);  // Input as separate integers

    printf("Lop: ");
    scanf("%s", sv->lop);

    do {
        printf("Nhap ma phong: ");
        scanf("%s", maPhong);

        phong = timPhong(maPhong);
        if (!phong) {
            printf("Phong voi ma %s khong ton tai. Vui long nhap lai.\n", maPhong);
        }
    } while (!phong);

    strcpy(sv->maPhong, maPhong);
    printf("Sua thong tin sinh vien thanh cong.\n");
}


// Delete SinhVien
void xoaSinhVien() {
    char maSinhVien[10];
    printf("Nhap ma sinh vien can xoa: ");
    scanf("%s", maSinhVien);

    SinhVien *current = danhSachSinhVien, *prev = NULL;
    while (current) {
        if (strcmp(current->maSinhVien, maSinhVien) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                danhSachSinhVien = current->next;
            }
            free(current);
            printf("Xoa sinh vien thanh cong.\n");
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Khong tim thay sinh vien voi ma: %s\n", maSinhVien);
}

// Free allocated memory
void giaiPhongBoNhoSinhVien() {
    SinhVien* current = danhSachSinhVien;
    while (current) {
        SinhVien* temp = current;
        current = current->next;
        free(temp);
    }
    danhSachSinhVien = NULL;
}

// Save SinhVien list to file
void luuDanhSachSinhVien() {
    FILE* file = fopen("sinhvien.txt", "w");
    if (!file) {
        printf("Khong mo duoc file.\n");
        return;
    }

    SinhVien* current = danhSachSinhVien;
    while (current) {
        fprintf(file, "%s %s %s %s %s\n", 
                current->maSinhVien, 
                current->hoTen, 
                current->ngSinh, 
                current->lop, 
                current->maPhong);
        current = current->next;
    }
    fclose(file);
    printf("Luu danh sach sinh vien thanh cong.\n");
}

// Load SinhVien list from file
void taiDanhSachSinhVien() {
    FILE* file = fopen("sinhvien.txt", "r");
    if (!file) {
        printf("Khong mo duoc file.\n");
        return;
    }

    char maSinhVien[10], hoTen[50], ngSinh[50], lop[50], maPhong[10];
    while (fscanf(file, "%s %s %s %s %s", maSinhVien, hoTen, ngSinh, lop, maPhong) == 5) {
        SinhVien* sv = taoSinhVien(maSinhVien, hoTen, ngSinh, lop, maPhong);
        sv->next = danhSachSinhVien;
        danhSachSinhVien = sv;
    }
    fclose(file);
}

// Function to add a student to a room
void themSinhVienVaoPhong() {
    char maSinhVien[10];
    char maPhong[10];
    Phong* phong = NULL;

    printf("Nhap ma sinh vien: ");
    scanf("%s", maSinhVien);

    SinhVien* sv = timSinhVien(maSinhVien);
    if (!sv) {
        printf("Khong tim thay sinh vien voi ma: %s\n", maSinhVien);
        return;
    }

    do {
        printf("Nhap ma phong: ");
        scanf("%s", maPhong);

        phong = timPhong(maPhong);
        if (!phong) {
            printf("Phong voi ma %s khong ton tai. Vui long nhap lai.\n", maPhong);
        }
    } while (!phong);

    strcpy(sv->maPhong, maPhong);
    printf("Da them sinh vien %s vao phong %s.\n", maSinhVien, maPhong);
}

// Function to transfer a student to another room
void chuyenPhongChoSinhVien() {
    char maSinhVien[10];
    char maPhongMoi[10];
    Phong* phongMoi = NULL;

    printf("Nhap ma sinh vien: ");
    scanf("%s", maSinhVien);

    SinhVien* sv = timSinhVien(maSinhVien);
    if (!sv) {
        printf("Khong tim thay sinh vien voi ma: %s\n", maSinhVien);
        return;
    }

    do {
        printf("Nhap ma phong moi: ");
        scanf("%s", maPhongMoi);

        phongMoi = timPhong(maPhongMoi);
        if (!phongMoi) {
            printf("Phong voi ma %s khong ton tai. Vui long nhap lai.\n", maPhongMoi);
        }
    } while (!phongMoi);

    strcpy(sv->maPhong, maPhongMoi);
    printf("Da chuyen sinh vien %s sang phong %s.\n", maSinhVien, maPhongMoi);
}


// Menu for SinhVien functions
void menusv() {
    int choice;
    system("cls");
    do {
        printf("\n--- Menu Sinh Vien ---\n");
        printf("1. Them sinh vien\n");
        printf("2. Hien thi danh sach sinh vien\n");
        printf("3. Sua sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Them sinh vien vao phong\n");
        printf("6. Chuyen phong cho sinh vien\n");
        printf("0. Thoat\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: themSinhVien();luuDanhSachSinhVien(); break;
            case 2: hienThiDanhSachSinhVien(); break;
            case 3: suaSinhVien();luuDanhSachSinhVien(); break;
            case 4: xoaSinhVien();luuDanhSachSinhVien(); break;
            case 5: themSinhVienVaoPhong();luuDanhSachSinhVien(); break;
            case 6: chuyenPhongChoSinhVien();luuDanhSachSinhVien(); break;
            case 0: break;
            default: printf("Lua chon sai, vui long chon lai.\n"); break;
        }
    } while (choice != 0);
}

