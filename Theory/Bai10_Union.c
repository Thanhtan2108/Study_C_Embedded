/*
Union trong C Embedded

1. Union là gì?
- Union là kiểu dữ liệu do người dùng tự định nghĩa
- Các thành viên trong Union dùng chung một vùng nhớ, nghĩa là trong cấu trúc của 1 union tạo ra 1 vùng nhớ sẽ được chia nhỏ ra để quản lý 
- Kích thước của Union là kích thước của thành viên lớn nhất

2. Khác biệt giữa Union và Struct:
- Struct: Các thành viên có địa chỉ khác nhau, kích thước = tổng các thành viên, quản lý 1 đối tượng thông qua nhiều KDL khác nhau
- Union: Các thành viên dùng chung địa chỉ, kích thước = max các thành viên, quản lý 1 đối tượng, có thể chia nhỏ đối tượng ra thành các bit để quản lý thông qua struct lồng

3. Khi nào dùng Union?
- Khi muốn tiết kiệm bộ nhớ
- Khi làm việc với bit fields
- Khi làm việc với các protocol, driver
*/

#include <stdio.h>
#include <stdint.h>
#include <string.h>

// 1. Ví dụ cơ bản về Union
void basicUnionExample() {
    printf("\n1. Basic Union Example:\n");
    
    union MyUnion {
        uint8_t value8;    // 1 byte
        uint16_t value16;  // 2 bytes
        uint32_t value32;  // 4 bytes
    };

    union MyUnion data;
    printf("Size of union: %lu bytes\n", sizeof(data)); // = 4 (max size của các thành viên)

    data.value32 = 0x12345678;
    printf("value32 = 0x%X\n", data.value32);  // 0x12345678
    printf("value16 = 0x%X\n", data.value16);  // 0x5678 (2 bytes cuối)
    printf("value8  = 0x%X\n", data.value8);   // 0x78 (1 byte cuối)
}

// 2. Ví dụ về Memory Saving với Union
void memorySavingExample() {
    printf("\n2. Memory Saving Example:\n");
    
    // Với Struct
    struct DataStruct {
        int integer;     // 4 bytes
        float floating;  // 4 bytes
        char character;  // 1 byte
    };

    // Với Union
    union DataUnion {
        int integer;     // 4 bytes
        float floating;  // 4 bytes
        char character;  // 1 byte
    };

    struct DataStruct s;
    union DataUnion u;

    printf("Size of struct: %lu bytes\n", sizeof(s)); // = 9 bytes (có padding)
    printf("Size of union: %lu bytes\n", sizeof(u));  // = 4 bytes (max size)
}

// 3. Ví dụ về Bit Fields với Union
void bitFieldExample() {
    printf("\n3. Bit Field Example:\n");
    
    typedef union {
        uint8_t value; // tạo ra 1 vùng nhớ lưu biến value có kích thước 1 byte = 8 bit
        struct { // chia nhỏ vùng nhớ ra thành từng bit/ vùng bit để quản lý
            uint8_t enable : 1;     // bit 0
            uint8_t mode : 2;       // bit 1-2
            uint8_t direction : 1;  // bit 3
            uint8_t speed : 4;      // bit 4-7
        } bits;
    } ControlRegister;

    ControlRegister reg;
    reg.value = 0;

    // Set các bit
    reg.bits.enable = 1;      // Enable = 1
    reg.bits.mode = 2;        // Mode = 10
    reg.bits.direction = 1;   // Direction = 1
    reg.bits.speed = 10;      // Speed = 1010

    printf("Control Register: 0x%X\n", reg.value);
}

// 4. Ví dụ về Protocol/Data Conversion
void protocolExample() {
    printf("\n4. Protocol/Data Conversion Example:\n");
    
    union Protocol {
        uint32_t value32;
        struct {
            uint8_t byte0;
            uint8_t byte1;
            uint8_t byte2;
            uint8_t byte3;
        } bytes;
    };

    union Protocol data;
    data.value32 = 0x12345678;

    printf("32-bit value: 0x%X\n", data.value32);
    printf("Byte 0: 0x%X\n", data.bytes.byte0);
    printf("Byte 1: 0x%X\n", data.bytes.byte1);
    printf("Byte 2: 0x%X\n", data.bytes.byte2);
    printf("Byte 3: 0x%X\n", data.bytes.byte3);
}

// 5. Ví dụ về Union lồng Struct
void unionWithStructExample() {
    printf("\n5. Union with Struct Example:\n");
    
    typedef struct {
        uint8_t id;
        char name[20];
    } DeviceInfo;

    typedef union {
        DeviceInfo info;
        struct {
            uint8_t raw[21]; // size = sizeof(DeviceInfo)
        } data;
    } DeviceData;

    DeviceData device;
    device.info.id = 123;
    strcpy(device.info.name, "Sensor");

    printf("Device ID: %d\n", device.info.id);
    printf("Device Name: %s\n", device.info.name);
    printf("Raw data[0]: 0x%X (ID)\n", device.data.raw[0]);
}

int main() {
    // Test tất cả các ví dụ
    basicUnionExample();
    memorySavingExample();
    bitFieldExample();
    protocolExample();
    unionWithStructExample();

    return 0;
}