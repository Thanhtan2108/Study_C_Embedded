/*
1. Khái niệm chung

static là một từ khóa (keyword) trong ngôn ngữ C dùng để thay đổi phạm vi truy cập (scope) và thời gian tồn tại (lifetime) của biến hoặc hàm.
Tùy theo nơi khai báo (trong hoặc ngoài hàm), static có ý nghĩa khác nhau.

*** NÓI CÁCH KHÁC, BIẾN STATIC GIỐNG NHU LÀ 1 PRIVATE CỦA TÍNH ĐÓNG GÓI TRONG OOP CỦA FILE.C NÀY

2. Chức năng của static

| Trường hợp sử dụng     | Phạm vi truy cập (Scope)     | Thời gian tồn tại (Lifetime)     | Mục đích chính                   |
| ---------------------- | ---------------------------- | -------------------------------- | -------------------------------- |
| Biến toàn cục (global) | Giới hạn trong file khai báo | Suốt thời gian chạy chương trình | Ẩn biến trong nội bộ module      |
| Biến cục bộ (local)    | Trong phạm vi hàm            | Suốt thời gian chạy chương trình | Giữ giá trị giữa các lần gọi hàm, biến không bị clear đi |
| Hàm (function)         | Giới hạn trong file khai báo | Không đổi                        | Ẩn hàm trong nội bộ module       |

3.1. Static với biến cục bộ

Khai báo bên trong hàm:

void counter(void) {
    static int count = 0;
    count++;
    printf("Count = %d\n", count);
}

👉 Biến count chỉ khởi tạo một lần duy nhất, và giữ nguyên giá trị giữa các lần gọi counter().

Ứng dụng trong Embedded:

Giữ trạng thái (state) giữa các lần xử lý ngắt hoặc các vòng lặp.

Dùng thay cho biến toàn cục khi chỉ cần phạm vi trong hàm.

3.2. Static với biến toàn cục

Khai báo bên ngoài tất cả các hàm, thường ở đầu file .c:

static int sensor_value;

👉 Biến này chỉ được truy cập trong file hiện tại (file scope), không thể truy cập từ file khác dù có dùng extern.

Ứng dụng trong Embedded:

Ẩn dữ liệu nội bộ của module (encapsulation).

Tránh xung đột tên biến giữa nhiều file .c.

3.3. Static với hàm

static void updateSensor(void) {
    / chỉ được gọi trong file này
}

👉 Hàm updateSensor() chỉ được gọi trong nội bộ file chứa nó, không thể gọi từ file khác.

Ứng dụng trong Embedded:

Ẩn các hàm phụ (helper functions) chỉ dùng nội bộ.

Giữ cho module gọn gàng, giảm rủi ro khi nhiều module có cùng tên hàm.

4. Khi nào nên dùng static

| Mục đích                              | Nên dùng `static` cho                |
| ------------------------------------- | ------------------------------------ |
| Giữ giá trị biến giữa các lần gọi hàm | Biến cục bộ trong hàm                |
| Giới hạn phạm vi truy cập trong file  | Biến hoặc hàm toàn cục               |
| Tăng tính đóng gói module             | Biến và hàm trong cùng file `.c`     |
| Giảm xung đột tên giữa các file       | Biến/hàm toàn cục trong nhiều module |

5. Lưu ý quan trọng

Biến static được lưu trong vùng nhớ Data hoặc BSS, không nằm trong Stack như biến cục bộ thông thường.

Không thể khai báo static trong file header (.h) nếu có khả năng include nhiều nơi → dễ sinh lỗi liên kết (multiple definition).

static không làm biến “an toàn luồng” (thread-safe), nếu nhiều ngắt hoặc task cùng truy cập, cần khóa (mutex/semaphore).

6. Kết luận

static là công cụ mạnh mẽ giúp:

Giữ trạng thái của biến giữa các lần gọi hàm.

Giới hạn phạm vi truy cập, tăng tính đóng gói và an toàn cho mã nguồn.

Là một phần quan trọng trong thiết kế module và quản lý tài nguyên trong Embedded Systems.
*/

// main.c
#include <stdio.h>
#include "test.h"   // include header để dùng hàm public

int main(void) {
    printf("== Test static toàn cục và hàm nội bộ ==\n");
    testFunction();
    testFunction();
    printCounter();

    printf("\n== Test static cục bộ trong hàm ==\n");
    localStaticExample();
    localStaticExample();
    localStaticExample();

    // ❌ Không thể gọi privateHelper() – vì nó là static trong test.c
    // privateHelper();  // -> Error: implicit declaration

    // ❌ Không thể truy cập biến counter – vì nó là static trong test.c
    // extern int counter; // -> Error: undefined reference to 'counter'

    return 0;
}

/*
🧠 Giải thích:

Khi main.c include test.h, nó chỉ biết đến các hàm public (testFunction, printCounter).

counter và privateHelper() hoàn toàn bị ẩn, dù bạn có cố dùng extern.
*/

/*
Phân tích kết quả
🔹 Với biến static toàn cục (counter)

Có một vùng nhớ duy nhất trong RAM.

Giữ giá trị giữa các lần gọi hàm.

Không thể truy cập từ file khác vì bị “ẩn” (internal linkage).

🔹 Với biến static cục bộ (localCount)

Chỉ được khai báo bên trong hàm, nhưng giữ giá trị giữa các lần gọi.

Không tạo lại mỗi khi hàm chạy.

Giá trị được khởi tạo một lần duy nhất khi chương trình bắt đầu.

🔹 Với biến cục bộ bình thường (normalVar)

Được tạo lại mỗi lần hàm được gọi.

Mất giá trị sau khi hàm kết thúc.

Luôn khởi tạo lại về 0.
*/