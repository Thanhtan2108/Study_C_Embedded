/*
========================================
MEMORY MODEL TRONG C EMBEDDED
========================================

Các vùng bộ nhớ chính trong MCU (ví dụ STM32):
------------------------------------------------
               +-----------------+
               | FLASH (ROM)     |
               |  .text  (code)  |
               |  .rodata (const)|
               +-----------------+
               | RAM             |
               |  .data          |
               |  .bss           |
               |  stack          |
               |  heap           |
               +-----------------+

----------------------------------
SECTION | Chứa gì | Ví dụ | Ghi chú
----------------------------------
.text    | code chương trình | hàm main() | nằm trong FLASH, không bị mất khi reset
.rodata  | hằng số const     | const char name[] | FLASH, read-only, giữ giá trị qua reset
.data    | global init       | int x = 5; | RAM, giá trị khởi tạo được copy từ FLASH lúc startup
.bss     | global chưa init  | int y;     | RAM, zero khi MCU khởi động
stack    | biến local        | int a trong hàm | RAM, mất khi hàm return
heap     | malloc/free       | dynamic memory | RAM, ít dùng trong MCU, volatile

----------------------------------
Flash (ROM) trong Embedded:
----------------------------------
✔ Lưu chương trình (.text) và hằng số (.rodata)
✔ Không mất dữ liệu khi mất nguồn
✔ Ghi mới vào flash cần erase theo page, ghi chậm, hạn chế số lần ghi
✔ Dùng để lưu dữ liệu const, lookup tables, firmware

RAM (volatile):
----------------------------------
✔ Lưu biến toàn cục (.data, .bss), stack, heap
✔ Mất dữ liệu khi mất điện
✔ .data được copy từ FLASH khi startup
✔ .bss được zero khi startup
✔ Stack dùng cho biến local, heap cho cấp phát động
✔ Dữ liệu tạm thời trong chương trình runtime

========================================
CODE DEMO
========================================
*/

#include <stdio.h>
#include <stdlib.h>

/* -------------------------
 * Các biến minh họa section
 * -------------------------
 */
const int flash_const = 123; // Nằm trong FLASH (.rodata)
int data_var = 10;           // .data (RAM, giá trị copy từ flash khi startup)
int bss_var;                 // .bss (RAM, auto = 0 khi startup)

/* Hàm in giá trị các biến */
void print_memory_info() {
    printf("flash_const (FLASH) = %d\n", flash_const);
    printf("data_var (.data RAM) = %d\n", data_var);
    printf("bss_var (.bss RAM) = %d\n", bss_var);
}

int main() {
    printf("=== Embedded Memory Model Demo ===\n\n");

    /* In thông tin RAM/FLASH */
    print_memory_info();

    /* Biến cục bộ -> stack */
    int stack_var = 50;
    printf("stack_var (stack) = %d\n", stack_var);

    /* Heap (dùng malloc, ít dùng trong MCU) */
    int *heap_var = malloc(sizeof(int));
    if(heap_var != NULL) {
        *heap_var = 77;
        printf("heap_var (heap) = %d\n", *heap_var);
        free(heap_var);
    }

    /* Giải thích chi tiết hơn */
    printf("\n--- Lưu ý về Flash và RAM ---\n");
    printf("1) Flash:\n");
    printf("   - Lưu chương trình và hằng số const\n");
    printf("   - Dữ liệu vẫn tồn tại khi mất điện\n");
    printf("   - Ghi dữ liệu mới cần erase theo page, tốc độ chậm, số lần ghi hạn chế\n");
    printf("2) RAM:\n");
    printf("   - Lưu biến toàn cục (.data, .bss), stack, heap\n");
    printf("   - Mất dữ liệu khi mất điện\n");
    printf("   - .data được copy từ flash lúc startup\n");
    printf("   - .bss được zero khi startup\n");
    printf("   - Stack dùng cho biến local, heap dùng cho malloc/free runtime\n");

    return 0;
}
