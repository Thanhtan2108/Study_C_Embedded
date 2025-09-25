/*
3. Con trỏ hàm

- Khi khởi tạo 1 function thì function đó được quản lý bởi 1 địa chỉ
- để quản lý địa chỉ hàm cần dùng 1 con trỏ hàm và để gọi đến hàm đó
- những hàm có cùng KDL trả về, cùng KDL tham số truyền vào thì có thể quản lý chúng thông qua con trỏ hàm
- Định nghĩa 1 con trỏ hàm:
    + Syntax: typedef KDL_trả_về (*tên_con_trỏ_hàm)(KDL_Tham_số_truyền_vào);
- Khởi tạo 1 con trỏ hàm đã định nghĩa:
    + Syntax: tên_con_trỏ_hàm tên_khởi_tạo_con_trỏ_hàm;
- Lúc này con trỏ hàm đã được khởi tạo và có thể dùng nó để gán các hàm muốn dùng có cùng KDL trả về và cùng KDL tham số truyền vào
    m = tên_hàm;
    => m đóng vai trò như là hàm đó, có chức năng của hàm đó.
- Thực chất không cần call function thông qua name_function mà có thể call thông qua địa chỉ của function đó
- Ứng dụng của con trỏ hàm trong thực tế:
    + VD năm 2025 1 ic có 3 thanh ghi => viết 5 function có cùng KDL trả về là void, cùng tham số truyền vào là uint8_t
    + đến 2026, phát triển từ 3 function lên 10 function cần viết thêm code để tối ưu và dễ code, bảo trì 
*/

#include <stdio.h>
#include <stdint.h>

#define CNT 3

// khai báo nguyên hàm
void view(uint8_t x);
void viewx2(uint8_t x);

// định nghĩa hàm
void view(uint8_t x) {
    printf("%d\n", x);
}

void viewx2(uint8_t x) {
    printf("%d\n", x*2);
}

// =======================================
typedef void (*mFunction)(uint8_t);

// =======================================
void reg1() {
    printf("reg1\n");
}

void reg2() {
    printf("reg2\n");
}

void reg3() {
    printf("reg3\n");
}

void (*mfunction[CNT])() = {reg1, reg2, reg3};

int main() {

    mFunction m;
    m = view;
    m(2);

    m = viewx2;
    m(2);

    // ===============================================
    uint64_t address;
    printf("add = %p\n", address = (uint64_t)view);

    ((mFunction)address)(1);

    // ================================================
    for (int i = 0 ; i < CNT ; i++) {
        mfunction[i]();
    }
    /*
    nếu không dùng con trỏ hàm mà muốn thực thi từng hàm cần phải call
    reg1();
    reg2();
    reg3();
    nếu sau cần thêm vào reg4() chỉ cần khai báo nguyên hàm và định nghĩa hàm, rồi thêm vào mảng con trỏ hàm thì không cần sửa code trong main, tránh lỗi code
    */

    return 0;
}