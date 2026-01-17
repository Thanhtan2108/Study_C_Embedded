/*
- typedef để định nghĩa 1 tên mới cho 1 kiểu dữ liệu 
- Thường được dùng với struct
    khi xây dựng 1 struct thì cơ bản struct nó không phải là 1 kiểu dữ liệu
    để struct trở thành 1 kiểu dữ liệu thì dùng thêm typedef 
*/

/*
Để sử dụng các kiểu dữ liệu như uint8_t thì cần phải khai báo thư viện stdint.h
nếu không sẽ báo lỗi
Nhưng thực chất trong thư viện stdint.h, uint8_t được định nghĩa là unsigned char thông qua typedef
Vì vậy nếu muốn dùng uint8_t mà không cần khai báo thư viện stdint.h thì có thể dùng typedef để định nghĩa
*/

#include <stdio.h>

// ==================================
typedef unsigned char uint8_t;
uint8_t a = 1;

// ==================================
// struct myStruct {
//     int age;
// };
typedef struct {
    int age;
} myStruct;

int main() {
    
    printf("%d\n", a);

    // ==========================
    // myStruct m; // lỗi vì myStruct không phải là 1 KDL
    /*
    để khởi tạo cho biến m có KDL myStruct cần: 
        struct myStruct {
            int age;
        } m; 
    sau đó mới có thể dùng m.age
    */
    // để khác phục và muốn tạo ra 1 KDL myStuct, dùng typedef, lúc này có thể khia báo biến m có KDL myStruct ngay
    myStruct m;
    m.age = 2;
    printf("%d", m.age);
    
    return 0;
}