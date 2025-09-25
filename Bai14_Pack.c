/*
- Quy tắc quan trọng nhất của lập trình nhúng là phả tiết kiệm ram, tối ưu code nhất có thể

- Để tránh dư byte trong RAM do struct,... gây ra, Pack được ra đời để giải quyết vấn đề này

- Sytax:
    #pragma pack(push, số_byte_căn_chỉnh) // bắt đầu căn chỉnh theo số_byte_căn_chỉnh
    #pragma pack(pop) // dừng căn chỉnh, quay lại như ban đầu như chưa căn chỉnh gì
*/

#include <stdio.h>
#include <stdint.h>

// struct ăn theo trường dữ liệu có kiểu dữ liệu to nhất
#pragma pack(push, 1)
typedef struct {
    uint32_t header;
    uint8_t cnt;
} MEM_Typedef;
#pragma pack(pop)

#pragma pack(push, 2)
typedef struct {
    uint32_t header;
    uint8_t cnt;
} MEM_Typedef1;
#pragma pack(pop)

typedef struct {
    uint32_t header;
    uint8_t cnt;
} MEM_Typedef2;

MEM_Typedef x;
MEM_Typedef1 z;
MEM_Typedef2 y;

int main() {
    printf("%d\n", sizeof(x)); // 5 byte do bắt đầu căn chỉnh theo 1 byte
    printf("%d\n", sizeof(z)); // 6 byte do bắt đầu căn chỉnh theo 2 byte
    printf("%d\n", sizeof(y)); // 8 byte do kết thúc căn chỉnh
}