/*
👉 File header chỉ khai báo các hàm public mà main.c có thể gọi.
Không khai báo biến static ở đây, vì mỗi file include vào sẽ sinh bản sao riêng biệt — dễ gây lỗi.
*/

// test.h
#ifndef TEST_H
#define TEST_H

void testFunction(void);     // Hàm public
void printCounter(void);     // Hàm public
void localStaticExample(void); // Hàm minh họa biến static cục bộ

#endif
