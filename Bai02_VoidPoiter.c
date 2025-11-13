/*
2. Con trỏ void

- là 1 con trỏ có kiểu dữ liẹu void, có thể ép sang các kiểu khác để dùng cho từng mục đích cụ thể
- thường dùng trong hàm để ép kiểu của con trỏ khi con trỏ đó cùng thực hiện 1 chức năng nhưng khác kiểu dữ liệu
*/

#include <stdio.h>
#include <stdint.h>

void mFunction(void *ptr, uint8_t size) {
    if (size == 1) {
        uint8_t* p8;
        p8 = (uint8_t*)ptr;
        *p8 = 0x12;
    }
    if (size == 2) {
        uint16_t* p16;
        p16 = (uint16_t*)ptr;
        *p16 = 0x1234;
    }
}

uint8_t a;
uint16_t b;

int main() {
    uint8_t* ptra = &a;
    mFunction(ptra, 1);

    uint16_t* ptrb = &b;
    mFunction(ptrb, 2);

    printf("%X\n", a);
    printf("%X\n", b);

    return 0;
}