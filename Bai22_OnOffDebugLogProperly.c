/*
** Khi làm 1 project luôn có 2 giai đoạn:

- Dev/Debug: giai đoạn phát triển

  - Thường dùng từ khóa "printf" để đạt "log" nhưng khi dùng thì tốn bộ nhớ của VDK
  
- Release: giai đoạn phát hành

  - Xóa các "log" được tạo bởi "printf"

=> 2 giai đoạn có xự xung đột nhau về "log"

=> Để giải quyết, trong project cần có 1 file thư viện "inlcude" chứa "Token: Value" là các tiền xử lý như "#define"

=> Sau đó dùng các lệnh tiền xử lý điều kiện để kiểm tra
*/

/*
Ví dụ:

Cách 1: Dùng #if để kiểm tra giá trị

#define PI 3.14

#if PI
void mFunction() {
    printf("PI = %.2f\n", PI);
}
#else
void mFunction() {
    printf("PI = %.2f\n", 0);
}
#endif
*/

/*
Cách 2: Dùng #ifdef nhưng điều khiển từ nơi khác

/Có thể comment/uncomment dòng này để bật/tắt
#define PI 3.14

#ifdef PI
void mFunction() {
    printf("PI = %.2f\n", PI);
}
#else
void mFunction() {
    printf("PI = %.2f\n", 0);
}
#endif
*/

/*
Cách 3: Dùng cơ chế điều khiển riêng (tốt hơn)

/Định nghĩa ở file config.h hoặc từ compiler
#define USE_PI 1  // 1 để bật, 0 để tắt

#if USE_PI
    #define PI_VALUE 3.14
#else
    #define PI_VALUE 0
#endif

void mFunction() {
    printf("PI = %.2f\n", PI_VALUE);
}
*/

/*
Cách 4: Dùng #if defined() linh hoạt hơn

/ Có thể định nghĩa hoặc không
/ #define PI 3.14

#if defined(PI) && (PI != 0)
void mFunction() {
    printf("PI = %.2f\n", PI);
}
#else
void mFunction() {
    printf("PI = %.2f\n", 0);
}
#endif
*/

/*
Trong embedded, thường dùng:

/ Trong file config.h
#define FEATURE_PI_ENABLED  1

/ Trong file implementation
#if FEATURE_PI_ENABLED
    #define PI 3.14
#else
    #define PI 0
#endif

void mFunction() {
    printf("PI = %.2f\n", PI);
}
*/