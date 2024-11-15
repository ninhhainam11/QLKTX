#ifndef SINHVIEN_H
#define SINHVIEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct SinhVien {
    char maSinhVien[10];
    char hoTen[50];
    char ngSinh[50];
    char lop[50];
    char maPhong[10];
};

struct node {
    struct SinhVien data;
    struct node *next;
};

struct list {
    struct node *Head;
};

// Function declarations
void initlist(struct list *l);
struct node *createnode(struct SinhVien data);
void docDanhSachSinhVien(struct list *l);
void ghiDanhSachSinhVien(struct list *l);
void themSinhVien(struct list *l);
struct node* timSinhVien(struct list *l, const char *maSinhVien);
void hienthiDanhSachSinhVien(struct list *l);
void suaSinhVien(struct list *l);
void xoaSinhVien(struct list *l);
void timVaInSinhVien(struct list *l);
void menusv();

#endif

