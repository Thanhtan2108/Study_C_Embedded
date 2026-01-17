/*
========================================
TỪ KHÓA register TRONG C EMBEDDED
========================================

I. Ý nghĩa của register:
------------------------
✔ Là keyword gợi ý compiler đưa biến vào thanh ghi CPU
✔ Mục đích: tăng tốc truy cập (thay vì RAM)
✔ CHỈ LÀ GỢI Ý → compiler có thể bỏ qua
✔ Không thể lấy địa chỉ của biến register (đa số compiler sẽ báo lỗi)
✔ Không liên quan đến hardware register

II. Tại sao ngày nay ít dùng?
------------------------------
Modern compiler (GCC/Clang) đã tự tối ưu tốt hơn con người
→ Thường không cần keyword này nữa
→ Nhưng vẫn có thể dùng để giải thích ý định trong sâu thời gian thực

III. Trường hợp hợp lý:
-----------------------
✔ biến loop counter
✔ biến tính toán cường độ cao
✔ ISR / critical section

========================================
CODE DEMO
========================================
*/

#include <stdio.h>

void compute_sum() {
    register int sum = 0;         // compiler có thể tối ưu thành register
    for (register int i = 0; i < 100000; i++) {
        sum += i;
    }
    printf("Register sum = %d\n", sum);
}

int main() {
    printf("=== register keyword demo ===\n");
    compute_sum();
    return 0;
}
