#include <stdio.h>
#include <string.h>

struct SinhVien{
    int id;
    char name[50];
    int age;
};

void docFile(struct SinhVien sv[],int n,char name[]){
    FILE *f = fopen(name,"rb");
    if (f == NULL){
        return 1;
    }
    fread(n,sizeof(int),1,f); 
    fread(sv,sizeof(sv),n,f);
    fclose(f);
}

void ghiFile(struct SinhVien sv[], int n,char name[]){
    FILE *f = fopen(name,"wb");
    if (f == NULL){
        printf("Loi file\n");
        return;
    }
    fwrite(&n,sizeof(int),1,f);
    fwrite(&sv, sizeof(sv),n,f); 
    fclose(f);
}

void inDanhSach(struct SinhVien sv[], int n,FILE *f){
    printf("\Danh sach sinh vien:\n");
    for (int i = 0; i < n; i++) {
        printf("ID: %d, Name: %s, Age: %d\n",sv[i].id,sv[i].name,sv[i].age);
    }
}

void themSinhVien(struct SinhVien sv[], int *n){
    printf("Nhap vao ID: ");
    scanf("%d",&sv[*n].id);
    printf("Nhap vao ten: ");
    getchar(); 
    fgets(sv[*n].name,sizeof(sv[*n].name),stdin);
    sv[*n].name[strcspn(sv[*n].name,"\n")] = 0; 
    printf("Nhap vao tuoi: ");
    scanf("%d",&sv[*n].age);
    (*n)++;
}

void suaSinhVien(struct SinhVien sv[],int n){
    int id, cout = 0;
    printf("Nhap vao ID sinh vien muon them: ");
    scanf("%d",&id);
    for (int i = 0; i < n; i++){
        if (sv[i].id == id){
            printf("Nhap vao ten moi: ");
            getchar();
            fgets(sv[i].name,sizeof(sv[i].name),stdin);
            sv[i].name[strcspn(sv[i].name,"\n")] = 0;
            printf("Nhap vao tuoi moi: ");
            scanf("%d",&sv[i].age);
            cout = 1;
            break;
        }
    }
    if (cout == 0){
        printf("Khong tim thay sinh vien co ID: %d\n",id);
    }
}

void xoaSinhVien(struct SinhVien sv[], int *n){
    int id, cout = 0;
    printf("Nhap vao ID sinh vien muon xoa: ");
    scanf("%d",&id);
    for (int i = 0; i < *n; i++){
        if (sv[i].id == id){
            for (int j = i; j < *n - 1; j++){
                sv[j] = sv[j + 1];
            }
            (*n)--;
            cout = 1;
            break;
        }
    }
    if (cout == 0){
        printf("Khong tim thay sinh vien co ID: %d\n",id);
    }
}

void timKiemSinhVien(struct SinhVien sv[],int n){
    int id, cout = 0;
    printf("Nhap vao ID sinh vien muon tim: ");
    scanf("%d",&id);
    for (int i = 0; i < n; i++){
        if (sv[i].id == id) {
            printf("ID: %d, Name: %s, Age: %d\n",sv[i].id,sv[i].name,sv[i].age);
            cout = 1;
            break;
        }
    }
    if (cout == 0){
        printf("Khong tim thay sinh vien co ID: %d\n",id);
    }
}

void sapXepSinhVien(struct SinhVien sv[],int n){
    for (int i = 0; i < n - 1; i++){
        for (int j = i + 1; j < n; j++){
            if (sv[i].id > sv[j].id){
                struct SinhVien temp = sv[i];
                sv[i] = sv[j];
                sv[j] = temp;
            }
        }
    }
    printf("Danh sach duoc sap xep theo ID\n");
}

int main() {
    struct SinhVien sv[100];
    int n;
    char name[] = "sv.bin";
    FILE *f = fopen(name, "wb");
    if (f == NULL) {
        printf("Loi file\n");
        return 1;
    }
    fwrite(&n,sizeof(int),1,f); 
    fwrite(&sv,sizeof(sv),n,f);
    fclose(f);
    
    docFile(sv,&n,name);

    int chose;
    do {
        printf("--------MENU--------\n");
		printf("1. In danh sach sinh vien\n");
		printf("2. Them sinh vien\n");
		printf("3. Sua thong tin sinh vien\n");
		printf("4. Xoa sinh vien\n");
		printf("5. Timkiem sinh vien\n");
		printf("6. Sap xep danh sach sinh vien\n");
		printf("7. Thoat\n");
		printf(" Lua chon cua ban: ");
		scanf("%d",&chose);
        switch (chose) {
            case 1:
                inDanhSach(sv,n,NULL);
                break;
            case 2:
                themSinhVien(sv,&n);
                ghiFile(sv,n,name);
                break;
            case 3:
                suaSinhVien(sv,n);
                ghiFile(sv,n,name);
                break;
            case 4:
                xoaSinhVien(sv,&n);
                ghiFile(sv,n,name);
                break;
            case 5:
                timKiemSinhVien(sv,n);
                break;
            case 6:
                sapXepSinhVien(sv,n);
                ghiFile(sv,n,name);
                break;
            case 7:
                printf("Thoat chuong trinh\n");
                break;
            default:
                printf("Lua chon khong phu hop");
        }
    } while (chose != 7);

    return 0;
}


