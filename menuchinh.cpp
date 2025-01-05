#include <stdio.h>	
#include "phong.cpp"
#include "sinhvien.cpp"
#include "gia.cpp"
#include "hoadon.cpp"
#include "thongke.cpp"

void menuChinh(){
	int choice;
	system("cls");	
	taiDanhSachSinhVien();
    taiDanhSachPhong();
    taiDanhSachLoaiPhong();
    taiGia();  
    docHoaDonTuFile();
    do {
    	system("cls");
        printf("\n===== MENU CHINH =====\n");
        printf("1. Quan ly sinh vien\n");
        printf("2. Quan ly phong\n");
        printf("3. Quan ly gia\n");
        printf("4. Quan ly hoa don\n");
        printf("5. Thong ke ky tuc xa\n");
        printf("0. Thoat chuong trinh\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: menuSinhVien(); break;
            case 2: menuPhong();break;
            case 3: menuGia();break;
            case 4: menuHoaDon();break;
            case 5: menuThongKe();break;
            case 0: break;
        }
    } while (choice != 0);
}


