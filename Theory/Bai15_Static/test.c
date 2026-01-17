/*
🧠 Giải thích:

static int counter: chỉ tồn tại một bản duy nhất, và chỉ dùng trong file test.c.
→ main.c không thể truy cập dù có extern.

static void privateHelper(): chỉ có phạm vi trong file test.c.
→ không thể gọi từ main.c.

testFunction() và printCounter() là public, có thể gọi từ file khác.

| Biến/Hàm          | Loại static        | Phạm vi (Scope)                  | Đặc điểm                                                        |
| ----------------- | ------------------ | -------------------------------- | --------------------------------------------------------------- |
| `counter`         | Toàn cục           | Trong file `test.c`              | Giữ giá trị suốt chương trình, không truy cập được từ file khác |
| `privateHelper()` | Hàm                | Trong file `test.c`              | Chỉ gọi nội bộ, không public                                    |
| `localCount`      | Cục bộ (trong hàm) | Trong hàm `localStaticExample()` | Giữ giá trị giữa các lần gọi                                    |
| `normalVar`       | Cục bộ bình thường | Trong hàm                        | Mất giá trị sau khi hàm kết thúc                                |

*/

// test.c
#include <stdio.h>
#include "test.h"

// ────────────────────────────────────────
// Biến static toàn cục – chỉ dùng trong test.c
// ────────────────────────────────────────
static int counter = 0;

// Hàm static – chỉ gọi được trong test.c
static void privateHelper(void) {
    printf("    [privateHelper] counter = %d\n", counter);
}

// Hàm public – được gọi từ main.c
void testFunction(void) {
    counter++;
    printf("testFunction() called, counter = %d\n", counter);
    privateHelper();
}

// Hàm public – in giá trị biến static toàn cục
void printCounter(void) {
    printf("printCounter(): counter = %d\n", counter);
}

// ────────────────────────────────────────
// Ví dụ về biến static cục bộ
// ────────────────────────────────────────
void localStaticExample(void) {
    static int localCount = 0; // Chỉ được khởi tạo 1 lần duy nhất
    int normalVar = 0;         // Biến cục bộ bình thường (auto)

    localCount++;
    normalVar++;

    printf("localStaticExample() → localCount = %d, normalVar = %d\n",
           localCount, normalVar);
}
