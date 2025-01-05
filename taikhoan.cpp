#include <stdio.h>
#include <string.h>
#include "menuchinh.cpp"

struct Taikhoan {
    char taiKhoan[50];
    char matKhau[50];
};

int kiemTraTaiKhoanTonTai(char *taiKhoan) {
    struct Taikhoan tk;
    char taiKhoanDaLuu[50], matKhauLuu[50];

    FILE *file = fopen("taikhoan.txt", "r");
    if (file == NULL) {
        printf("Khong the mo file!\n");
        return 0;
    }

    while (fscanf(file, "%s %s", taiKhoanDaLuu, matKhauLuu) != EOF) {
        if (strcmp(taiKhoanDaLuu, taiKhoan) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void luuTaiKhoan() {
    struct Taikhoan tk;
    FILE *file = fopen("taikhoan.txt", "a");
    if (file == NULL) {
        printf("Khong the mo file!\n");
        return;
    }

    do {
        printf("Nhap tai khoan moi: ");
        scanf("%s", tk.taiKhoan);

        if (kiemTraTaiKhoanTonTai(tk.taiKhoan)) {
            printf("Tai khoan da ton tai. Vui long chon tai khoan khac.\n");
        } else {
            break;
        }
    } while (1);

    printf("Nhap mat khau moi: ");
    scanf("%s", tk.matKhau);

    fprintf(file, "%s %s\n", tk.taiKhoan, tk.matKhau);

    fclose(file);
    printf("Tai khoan da duoc luu.\n");
}

int kiemTraDangNhap() {
    struct Taikhoan tk;
    char taiKhoanDaLuu[50], matKhauDaLuu[50];

    printf("Nhap tai khoan: ");
    scanf("%s", tk.taiKhoan);
    printf("Nhap mat khau: ");
    scanf("%s", tk.matKhau);

    FILE *file = fopen("taikhoan.txt", "r");
    if (file == NULL) {
        printf("Khong the mo file!\n");
        return 0;
    }

    while (fscanf(file, "%s %s", taiKhoanDaLuu, matKhauDaLuu) != EOF) {
        if (strcmp(taiKhoanDaLuu, tk.taiKhoan) == 0 && strcmp(matKhauDaLuu, tk.matKhau) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

int main() {
    int choice;
	system("cls");
    do {
        printf("\nChao mung den voi he thong!\n");
        printf("1. Dang nhap\n");
        printf("2. Dang ky\n");
        printf("0. Thoat\n");

        printf("Nhap lua chon: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (kiemTraDangNhap()) {
                    printf("Dang nhap thanh cong!\n");
                    menuChinh();
                } else {
                    printf("Sai tai khoan hoac mat khau. Vui long thu lai.\n");
                }
                break;
            case 2:
                luuTaiKhoan();
                break;
            case 0:
                exit(1);
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 0); 
}


