/*
các câu lệnh bắt đầu bằng # được gọi là tiền xử lý, nó sẽ được xử lý trước khi run chương trình 
Ngoài ra sử dụng các tiền xử lý giúp tiết kiệm rất nhiều bộ nhớ, đều này tối ưu rất nhiều trong embedded
Các tiền xử lý thường dùng là 
    #define : định nghĩa 1 giá trị cho 1 biến
    #ifdef : nếu biến đó đã đc định nghĩa rồi
    #else : biến đó chưa được định nghĩa trước đó
    #endif : kết thúc quá trình kiểm tra biến đã được định nghĩa trước đó chưa
Ngoài ra còn được dùng để viết các file thư viện .h
    #ifndef __tên__
    #define __tên__

    #endif
*/

#include <stdio.h>
#include <stdint.h>

#define PI 3.14

#ifdef PI
void mFunction() {
    printf("PI = %.2f\n", PI);
}
#else
void mFunction() {
    printf("PI = %.2f\n", 0);
}
#endif

/*
nếu không dùng tiền xử lý như trên mà muốn kiểm tra xem PI bằng cách viết 2 hàm riêng thì 
2 hàm này lại tốn 2 kích thước trong bộ nhớ 
So với việc dùng tiền xử lý thì bộ nhớ được tiết kiệm gấp 
*/

int main() {
    mFunction();
    return 0;
}