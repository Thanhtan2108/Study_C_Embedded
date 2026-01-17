/*
========================================
TỪ KHÓA const TRONG LẬP TRÌNH C EMBEDDED
========================================

I. Ý NGHĨA CỦA const:
----------------------
- const nghĩa là "giá trị chỉ đọc" (read-only)
- Compiler **ngăn không cho thay đổi giá trị qua biến**
- Không phải là biến được đặt trong flash (trừ khi kết hợp const + static)
- Không tạo ra dữ liệu bất biến tuyệt đối (vẫn có thể thay đổi bằng con trỏ)

II. LỢI ÍCH CỦA const TRONG C EMBEDDED:
---------------------------------------
✔ Bảo vệ dữ liệu không bị ghi nhầm
✔ Tối ưu bộ nhớ (hằng số có thể được đặt vào Flash)
✔ Tài liệu hoá code (biến không đổi → dễ đọc)
✔ Hỗ trợ việc tối ưu hoá compile
✔ Dùng trong API để đảm bảo argument không bị sửa

III. CẤU TRÚC const KHI DÙNG VỚI CON TRỎ
----------------------------------------
1. const int *p;      // Pointer to const data (không thay đổi *p, được đổi p)
2. int *const p;      // Const pointer (không thay đổi p, được đổi *p)
3. const int *const p; // Cả pointer và data đều không đổi

IV. const & Memory trong Embedded
---------------------------------
Trong MCU:
- const mặc định nằm trong Flash
- RAM không dùng cho const
→ tiết kiệm RAM

Trong PC:
- const thường nằm ở .rodata (read-only section)
- vẫn có thể truy cập read-only tại runtime

========================================
VÍ DỤ MINH HỌA
========================================
*/

#include <stdio.h>

// Example hằng số lưu trong Flash (trên embedded)
// và không thể thay đổi giá trị
const int system_id = 1234;

// Sai: cố gắng thay đổi biến const
// system_id = 999;   // ❌ ERROR: assignment of read-only variable

// const trong API (ví dụ nhận dữ liệu không được thay đổi)
void print_data(const char *str) {
    // str[0] = 'X'; // ❌ không được sửa dữ liệu
    printf("Du lieu nhan: %s\n", str);
}

// Minh họa con trỏ const
void pointer_const_demo() {
    int val = 10;
    int newVal = 99;

    const int *ptr1 = &val;  // Read-only data, pointer thay đổi được
    // *ptr1 = 20;            // ❌ lỗi
    ptr1 = &newVal;           // ✔ hợp lệ

    int *const ptr2 = &val;   // Pointer cố định, data thay đổi được
    *ptr2 = 20;               // ✔ hợp lệ
    // ptr2 = &newVal;        // ❌ lỗi

    const int *const ptr3 = &val; // cả 2 đều không đổi
    // *ptr3 = 20;            // ❌ lỗi
    // ptr3 = &newVal;        // ❌ lỗi
}

// const + array (OK vì data không thay đổi)
const char msg[] = "Hello from const";

int main() {
    printf("=== Demo const trong C Embedded ===\n");

    printf("System ID (const): %d\n", system_id);

    print_data("Test const parameter");

    printf("\n--- const array ---\n");
    printf("%s\n", msg);
    // msg[0] = 'A';  // ❌ lỗi vì msg là const

    printf("\n--- Pointer const demo ---\n");
    pointer_const_demo();

    printf("\nChuong trinh ket thuc.\n");
    return 0;
}
