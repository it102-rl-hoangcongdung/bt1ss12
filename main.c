#include <stdio.h>
#include <string.h>

#define MAX_NV 50

struct NhanVien {
    int maNV;
    char hoTen[50];
    int soPhutDiMuon;
    float luongCoBan;
};

int timTheoMaNV(struct NhanVien ds[], int n, int ma);
int themNhanVien(struct NhanVien ds[], int n);
void hienThiDanhSach(struct NhanVien ds[], int n);
void capNhatPhutDiMuon(struct NhanVien ds[], int n);
void timKiemNhanVien(struct NhanVien ds[], int n);

int main() {
    struct NhanVien ds[MAX_NV];
    int n = 0;
    int choice;

    do {
        printf("\n===== HỆ THỐNG QUẢN LÝ CHẤM CÔNG HRM =====\n");
        printf("1. Thêm nhân viên mới\n");
        printf("2. Hiển thị danh sách và tính lương\n");
        printf("3. Cập nhật số phút đi muộn\n");
        printf("4. Tìm kiếm nhân viên theo mã\n");
        printf("0. Thoát\n");
        printf("==========================================\n");
        printf("Nhập lựa chọn: ");
        if (scanf("%d", &choice) != 1) {
            printf("Lựa chọn không hợp lệ!\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                n = themNhanVien(ds, n);
                break;
            case 2:
                hienThiDanhSach(ds, n);
                break;
            case 3:
                capNhatPhutDiMuon(ds, n);
                break;
            case 4:
                timKiemNhanVien(ds, n);
                break;
            case 0:
                printf("Thoát chương trình. Tạm biệt!\n");
                break;
            default:
                printf("Lựa chọn không hợp lệ! Vui lòng chọn từ 0 đến 4.\n");
        }
    } while (choice != 0);

    return 0;
}

int timTheoMaNV(struct NhanVien ds[], int n, int ma) {
    for (int i = 0; i < n; i++) {
        if (ds[i].maNV == ma) {
            return i;
        }
    }
    return -1;
}

int themNhanVien(struct NhanVien ds[], int n) {
    if (n >= MAX_NV) {
        printf("==> Danh sách nhân viên đã đầy (tối đa 50)!\n");
        return n;
    }

    int ma;
    printf("Nhập mã nhân viên: ");
    if (scanf("%d", &ma) != 1) {
        printf("Lỗi nhập liệu!\n");
        while (getchar() != '\n');
        return n;
    }
    while (getchar() != '\n');

    if (timTheoMaNV(ds, n, ma) != -1) {
        printf("==> Lỗi: Mã nhân viên đã tồn tại!\n");
        return n;
    }

    ds[n].maNV = ma;
    printf("Nhập họ và tên: ");
    fgets(ds[n].hoTen, sizeof(ds[n].hoTen), stdin);
    ds[n].hoTen[strcspn(ds[n].hoTen, "\n")] = 0;

    printf("Nhập số phút đi muộn: ");
    if (scanf("%d", &ds[n].soPhutDiMuon) != 1 || ds[n].soPhutDiMuon < 0) {
        printf("==> Số phút đi muộn không hợp lệ!\n");
        while (getchar() != '\n');
        return n;
    }

    printf("Nhập lương cơ bản: ");
    if (scanf("%f", &ds[n].luongCoBan) != 1 || ds[n].luongCoBan < 0) {
        printf("==> Lương cơ bản không hợp lệ!\n");
        while (getchar() != '\n');
        return n;
    }

    printf("=> Thêm nhân viên thành công!\n");
    return n + 1;
}

void hienThiDanhSach(struct NhanVien ds[], int n) {
    if (n == 0) {
        printf("==> Danh sách nhân viên trống!\n");
        return;
    }

    printf("\n--- DANH SÁCH NHÂN VIÊN ---\n");
    printf("%-6s | %-20s | %-10s | %-15s\n", "Ma NV", "Ho ten", "Phut muon", "Luong thuc nhan");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        float tienPhat = (ds[i].soPhutDiMuon > 15) ? 50000 : 0;
        float luongThucNhan = ds[i].luongCoBan - tienPhat;
        printf("%-6d | %-20s | %-10d | %.0f\n", ds[i].maNV, ds[i].hoTen, ds[i].soPhutDiMuon, luongThucNhan);
    }
}

void capNhatPhutDiMuon(struct NhanVien ds[], int n) {
    if (n == 0) {
        printf("==> Danh sách nhân viên trống!\n");
        return;
    }

    int ma;
    printf("Nhập mã NV cần cập nhật: ");
    if (scanf("%d", &ma) != 1) {
        printf("Lỗi nhập liệu!\n");
        while (getchar() != '\n');
        return;
    }

    int idx = timTheoMaNV(ds, n, ma);
    if (idx == -1) {
        printf("=> Không tìm thấy nhân viên!\n");
        return;
    }

    int phutMoi;
    printf("Nhập số phút đi muộn mới: ");
    if (scanf("%d", &phutMoi) != 1 || phutMoi < 0) {
        printf("==> Số phút đi muộn không hợp lệ!\n");
        while (getchar() != '\n');
        return;
    }

    ds[idx].soPhutDiMuon = phutMoi;
    float tienPhat = (ds[idx].soPhutDiMuon > 15) ? 50000 : 0;
    float luongThucNhan = ds[idx].luongCoBan - tienPhat;
    printf("=> Cập nhật thành công! Lương thực nhận mới là: %.0f VNĐ\n", luongThucNhan);
}

void timKiemNhanVien(struct NhanVien ds[], int n) {
    if (n == 0) {
        printf("==> Danh sách nhân viên trống!\n");
        return;
    }

    int ma;
    printf("Nhập mã NV cần tìm: ");
    if (scanf("%d", &ma) != 1) {
        printf("Lỗi nhập liệu!\n");
        while (getchar() != '\n');
        return;
    }

    int idx = timTheoMaNV(ds, n, ma);
    if (idx == -1) {
        printf("=> Không tìm thấy nhân viên!\n");
        return;
    }

    float tienPhat = (ds[idx].soPhutDiMuon > 15) ? 50000 : 0;
    float luongThucNhan = ds[idx].luongCoBan - tienPhat;

    printf("\n--- THÔNG TIN NHÂN VIÊN ---\n");
    printf("Mã NV: %d\n", ds[idx].maNV);
    printf("Họ tên: %s\n", ds[idx].hoTen);
    printf("Số phút đi muộn: %d\n", ds[idx].soPhutDiMuon);
    printf("Lương cơ bản: %.0f\n", ds[idx].luongCoBan);
    printf("Lương thực nhận: %.0f\n", luongThucNhan);
}