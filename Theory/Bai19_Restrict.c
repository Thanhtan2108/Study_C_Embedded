/*
========================================
TỪ KHÓA restrict TRONG C EMBEDDED
(C99)
========================================

I. Ý nghĩa của restrict:
------------------------
✔ Chỉ dùng được với con trỏ
✔ Báo cho compiler biết rằng con trỏ là “unique owner”
✔ Tức: không có con trỏ nào khác cùng trỏ vào vùng nhớ này
✔ Giúp compiler tối ưu mạnh → nhất là copy/memset/DMA

II. Lợi ích khi dùng restrict:
-------------------------------
✔ Tránh dependency/alias khiến code chạy chậm
✔ Tăng tốc, đặc biệt trong pipeline CPU / ARM
✔ Dùng nhiều trong embedded DSP / DMA buffer

III. Cảnh báo:
--------------
❌ Không dùng restrict nếu 2 con trỏ có thể overlap
✔ Nếu dùng sai → BUG KHÓ TÌM

========================================
CODE DEMO
========================================
*/

#include <stdio.h>
#include <string.h>

/* -----------------------------
 * Hàm dùng restrict đúng
 * -----------------------------
 */
void fast_copy(int * restrict dst, const int * restrict src, int size) {
    while(size--) {
        *dst++ = *src++;
    }
}

/* -----------------------------
 * Hàm dùng restrict sai (vùng nhớ overlap)
 * -----------------------------
 */
void fast_copy_overlap(int * restrict dst, const int * restrict src, int size) {
    while(size--) {
        *dst++ = *src++; // Nếu dst và src trùng vùng -> kết quả không xác định
    }
}

int main() {
    printf("=== restrict keyword demo ===\n\n");

    /* === Ví dụ dùng đúng === */
    int src[4] = {1, 2, 3, 4};
    int dst[4] = {0};

    printf("Example 1: correct restrict usage\n");
    fast_copy(dst, src, 4);
    printf("Copied: ");
    for(int i = 0; i < 4; i++) {
        printf("%d ", dst[i]);
    }
    printf("\n\n");

    /* === Ví dụ dùng sai (vùng nhớ overlap) === */
    int buffer[6] = {10, 20, 30, 40, 50, 60};

    printf("Example 2: wrong restrict usage (overlap)\n");
    printf("Original buffer: ");
    for(int i = 0; i < 6; i++) printf("%d ", buffer[i]);
    printf("\n");

    /* dst và src trùng vùng nhớ -> undefined behavior khi dùng restrict */
    fast_copy_overlap(&buffer[1], &buffer[0], 5);

    printf("After fast_copy_overlap: ");
    for(int i = 0; i < 6; i++) printf("%d ", buffer[i]);
    printf("\n\n");

    /* === Ví dụ không dùng restrict nhưng overlap vẫn an toàn === */
    int buffer2[6] = {10, 20, 30, 40, 50, 60};

    printf("Example 3: no restrict, overlap safe\n");
    printf("Original buffer2: ");
    for(int i = 0; i < 6; i++) printf("%d ", buffer2[i]);
    printf("\n");

    int *dst2 = &buffer2[1];
    int *src2 = &buffer2[0];
    for(int i = 0; i < 5; i++) {
        dst2[i] = src2[i]; // safe, compiler không tối ưu giả định unique pointer
    }

    printf("After manual copy: ");
    for(int i = 0; i < 6; i++) printf("%d ", buffer2[i]);
    printf("\n");

    return 0;
}
