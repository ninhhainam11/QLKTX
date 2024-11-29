#include <stdio.h>
#include "phong.cpp"
#include "sinhvien.cpp"
#include "gia.cpp"
#include "hoadon.cpp"
#include "thongke.cpp"
void mainmenu(){
	int choice;
	system("cls");	
    do {
    	system("cls");
        printf("\n===== MAIN MENU =====\n");
        printf("1. Quan ly sinh vien\n");
        printf("2. Quan ly phong\n");
        printf("3. Quan ly gia\n");
        printf("4. Quan ly hoa don\n");
        printf("5. Thong ke ky tuc xa\n");
        printf("0. Thoat chuong trinh\n");
        printf("Chon: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: menusv(); break;
            case 2: menuphong();break;
            case 3: menugia();break;
            case 4: menuhoadon();break;
            case 5: menuthongke();break;
            case 0: exit(1);
        }
    } while (choice != 0);
}



int main() {
	taiDanhSachSinhVien();
    taiDanhSachPhong();
    taiDanhSachLoaiPhong();
    docGiaTuFile();  
    docHoaDonTuFile();
    mainmenu();
}

