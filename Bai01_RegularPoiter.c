/*
- Con trỏ : là 1 biến quản lý địa chỉ của 1 ô nhớ khác

1. Con trỏ thông thường

- khi tạo 1 biến ra thì biến đó được lưu vào ô nhớ trong bộ nhớ, ô nhớ đó sẽ có địa chỉ để quản lý
- Để lấy địa chỉ của ô nhớ, dùng toán tử &.
- để quản lý giá trị địa chỉ của ô nhớ đó, cần khai báo 1 biến con trỏ.
    + Syntax: KDL* name_ptr = &name_value; // toán tử & để lấy địa chỉ của biến đó gán cho con trỏ quản lý
- để lấy giá trị của biến (ô nhớ) được con trỏ quản lý, dùng toán tử *
- Mặc định size của con trỏ đối với x86 là 4byte, x64 là 8byte, khi dùng con trỏ trỏ tới vùng dữ liệu có bao nhiêu byte đii nữa thì trong bộ nhớ chỉ tạo ra thêm 4/8byte cho con trỏ thôi
- con trỏ sẽ quản lý và thực hiện các phép toán bằng số byte con trỏ được khởi tạo - kích thước vùng nhớ con trỏ trỏ tới

*/

#include <stdio.h>
#include <stdint.h>

void mPrint1(uint8_t x) {
    printf("%d\n", x);
}

void mPrint2(uint8_t *ptr) { // tham số là con trỏ cho hàm thì dùng toán tử *
    printf("%d\n", *ptr);
}

// ================================
// 40byte
typedef struct {
    int a;
    int b;
    int x;
    int f;
    int r;
    int d;
    int e;
    int t;
    int k;
    int l;
} Reg;

Reg re;
Reg* ptrStruct;

// ================================
uint8_t* ptr8;// con trỏ 1 byte
uint32_t* ptr32; // con trỏ 4byte

uint8_t arr[5] = {1,2,3,4,5}; // mảng 5 byte do có 5 phần tử 1 byte

int main() {
    uint8_t x = 15;
    uint8_t* ptr = &x;

    // printf("Dia chi cua x : %X\n", &x);
    printf("Dia chi cua x : %p\n", (void *)&x);
    printf("Gia tri cua x : %d\n", x);
    printf("gia tri cua bien duoc con tro quan ly : %d\n", *ptr);

    // ============================================
    mPrint1(x); // truyền tham trị, sẽ tạo thêm 1 vùng nhớ để chứa biến x trong hàm mPrint1 -> tốn bộ nhớ vì tạo thêm byte bằng với byte của đối số
    
    mPrint2(&x); // truyền tham chiếu, truyền đối số cho hàm có tham số là con trỏ dùng toán tử &
    mPrint2(ptr); // tương tự như trên vì đã gán &x cho biến con trỏ ptr
    // => bản chất là con trỏ sẽ trỏ đến nơi lưu trữ dữ liệu được truyền trong bộ nhớchuws không làm phát sinh thêm nhiều byte trong bộ nhớ

    // ======================================================
    printf("size re %d byte\n", sizeof(re)); // 40byte
    printf("size ptrStruct %d byte\n", sizeof(ptrStruct)); // 8byte
    // ======================================================
    ptr8 = &arr[0]; // lấy địa chỉ của mảng thông qua phần tử đầu tiên trong mảng
    ptr32 = (uint32_t*)&arr[0];

    ptr8++; // dịch thêm 1 đơn vị => 1 byte
    ptr32++; // dịch thêm 1 đơn vị => 4 byte
    printf("ptr8 %d\n", *ptr8); // 2
    printf("ptr32 %d\n", *ptr32); // 5

    return 0;
}