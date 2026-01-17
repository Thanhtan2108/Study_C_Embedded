/*
- khi viết hàm ở 1 file.c khác và muốn dùng hàm đó trong main.c thường sẽ include vào và sử dụng hàm, file.c ko thể include vào main.c
- Nhưng đối với 1 biến trong file.c nmwf ngoài file main.c, để muốn sử dụng được biến này trong main.c cần sử dụng từ khóa extern

- Bản chất là khi khai báo 1 biến ra, tuy nó nằm ở nhiều file khác nhau nhưng nó đã nằm trong bộ nhớ SRAM rồi, dùng từ khóa extern để thông báo rằng biến đã có trong SRAM rồi và có thể sử dụng ở các file khác nhau trong cùng project

- Ngoài extern biến ra còn có thể extern hàm nữa.

- Nhưng thực tế, không ai lại code extern ở nhiều file như vậy làm code ko đc clean, mình nên tạo ra 1 file.h sau đó extern biến/hàm vào đó rồi include vào file.c cần extern là được

*** NÓI CÁCH KHÁC, EXTERN GIỐNG NHU LÀ TÍNH KẾ THỪA TRONG OOP, CHO PHÉP KẾ THỪA LẠI BIẾN HOẶC HÀM TỪ FILE.H/.C KHÁC

** Chú ý : Khi biên dịch để chạy chương trình cần biên dịch cả 2 file chứa biến/hàm được extern và file main.c cùng 1 lúc để linker có thể tìm thấy biến/hàm
    gcc các_file_cần_biên_dịch_1_lúc -o tên_file_thực_thi.exe
    ./tên_file_thực_thi.exe để run
*/

#include <stdio.h>
// Không include file.c được nhưng include được file.h
#include "Bai11_Extern_MoRongThem.h"

// Không cần extern trong main.c vì đã extern trong file.h rồi
// Khai báo extern để sử dụng biến x từ file Bai11_Extern_MoRongThem.c
// extern int x;

// Khai báo extern để sử dụng hàm mFuunction từ file Bai11_Extern_MoRongThem.c
// extern void mFunction(void);

int main() {
    // In giá trị ban đầu của x
    printf("Gia tri ban dau cua x: %d\n", x);
    
    // Gọi hàm mFuunction để thay đổi giá trị x
    mFunction();
    
    // In giá trị của x sau khi thay đổi
    printf("Gia tri cua x sau khi thay doi: %d\n", x);
    
    return 0;
}
