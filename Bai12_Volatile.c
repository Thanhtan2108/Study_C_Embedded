/*
Ví dụ minh họa sự khác biệt giữa biến thường và biến volatile:
- Khi không dùng volatile: Compiler có thể tối ưu và bỏ qua việc đọc lại giá trị biến từ memory
- Khi dùng volatile: Compiler buộc phải đọc lại giá trị từ memory mỗi lần truy cập biến
*/

#include <stdio.h>
#include <stdlib.h>

// Biến flag giả lập như thể được thay đổi bởi ngắt hoặc thread khác
int normal_flag = 0;
volatile int volatile_flag = 0;

// Hàm giả lập việc thay đổi giá trị từ bên ngoài (như từ ngắt)
void external_change() {
    normal_flag = 1;
    volatile_flag = 1;
    printf("Gia tri flag da bi thay doi tu ben ngoai!\n");
}

int main() {
    printf("Bat dau chuong trinh...\n");
    
    // Vòng lặp với biến thường
    printf("\nTest voi bien thuong (normal_flag):\n");
    while(normal_flag == 0) {
        // Compiler có thể tối ưu và bỏ qua việc đọc lại giá trị normal_flag
        // Do đó vòng lặp có thể không bao giờ kết thúc dù giá trị đã thay đổi
        external_change();
        printf("Dang trong vong lap normal_flag\n");
    }
    
    // Reset giá trị
    normal_flag = 0;
    volatile_flag = 0;
    
    // Vòng lặp với biến volatile
    printf("\nTest voi bien volatile (volatile_flag):\n");
    while(volatile_flag == 0) {
        // Compiler buộc phải đọc lại giá trị volatile_flag từ memory mỗi lần kiểm tra
        // Do đó vòng lặp sẽ kết thúc ngay khi giá trị thay đổi
        external_change();
        printf("Dang trong vong lap volatile_flag\n");
    }
    
    printf("\nChuong trinh ket thuc!\n");
    return 0;
}