#include <stdio.h>
#include "phong.cpp"
#include "sinhvien.cpp"

void mainmenu(){
	int choice;
	system("cls");
    do {
        printf("\n===== MAIN MENU =====\n");
        printf("1. Quan ly sinh vien\n");
        printf("2. Quan ly phong\n");
        printf("3. Thoat\n");
        printf("Chon: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: menusv(); break;
            case 2: menuphong();break;
            case 3: exit(1);
        }
    } while (choice != 8);
}



int main() {
    // Load the list from the file at the start
    // Call the menu to allow user interaction
    mainmenu();

    // Clean up dynamically allocated memory
    giaiPhongBoNho();
    
    return 0;
}

