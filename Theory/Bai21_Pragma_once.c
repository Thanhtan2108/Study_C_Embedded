/*
========================================
#PRAGMA ONCE TRONG C / EMBEDDED
========================================

I. Ý nghĩa:
-------------
- `#pragma once` là chỉ dẫn cho preprocessor báo "chỉ include file này một lần".
- Thay thế cho include-guard (#ifndef/#define/#endif) truyền thống.
- Không chuẩn C/C++, nhưng hầu hết compiler hiện đại (GCC, Clang, MSVC, IAR, Keil) đều hỗ trợ.

II. Lợi ích:
-------------
✔ Giảm khả năng include trùng lặp
✔ Code ngắn gọn, dễ đọc
✔ Compiler có thể tối ưu build (không mở lại file nhiều lần)

III. Hạn chế / Cảnh báo:
-------------------------
❌ Dựa trên đường dẫn/file ID, có thể fail nếu cùng file có nhiều path (symlink, copy)
❌ Không portable với compiler cực kỳ cũ
✔ Nếu dùng đúng -> an toàn và nhanh
*/

#include <stdio.h>

/* -----------------------------
 * Ví dụ 1: Dùng #pragma once đúng
 * -----------------------------
 */

/*
// file: my_header_correct.h
#pragma once

int add(int a, int b);
*/

/* main.c */
int add(int a, int b) { return a + b; }

/* -----------------------------
 * Ví dụ 2: Không dùng được #pragma once
 * -----------------------------
 * Giả sử có 2 file header giống hệt nhau nhưng nằm ở
 * đường dẫn khác nhau (vd: vendor/module/include/my_header.h và 
 * user/project/include/my_header.h), cùng content:
 *
 * #pragma once sẽ coi là 2 file khác nhau -> bị include 2 lần
 * -> lỗi định nghĩa trùng (multiple definition)
 *
 * Trường hợp này nên dùng include-guard truyền thống.
 */

/*
// file: my_header_duplicate1.h
#pragma once
int subtract(int a, int b);

// file: my_header_duplicate2.h (copy ở đường dẫn khác)
#pragma once
int subtract(int a, int b);
*/

/* -----------------------------
 * Ví dụ minh họa main
 * -----------------------------
 */
int main(void) {
    printf("=== #pragma once demo ===\n");

    int x = add(5, 7);
    printf("add(5,7) = %d\n", x);

    /* Trường hợp đúng:
       - chỉ có 1 file header -> include một lần
       - safe, compile nhanh hơn
    */

    /* Trường hợp không nên:
       - cùng nội dung nhưng nhiều bản copy khác path
       - #pragma once không nhận diện trùng -> multiple definition
       - phải dùng include-guard
    */

    return 0;
}

/* -----------------------------
 * Tóm tắt:
 * -----------------------------
 * ✔ Dùng #pragma once khi project dùng toolchain hiện đại và file header duy nhất
 * ✔ Nếu header có thể duplicate hoặc dùng compiler cũ -> dùng include-guard
 * ✔ Có thể kết hợp: #pragma once + include-guard (an toàn và nhanh)
 */
