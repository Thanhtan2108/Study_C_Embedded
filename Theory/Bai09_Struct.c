/*
PHẦN 1: TRUYỀN THAM SỐ BÌNH THƯỜNG VS TRUYỀN CON TRỎ
1. Truyền tham số bình thường (pass by value):
   - Tạo ra một bản sao của dữ liệu
   - Không thay đổi được giá trị gốc
   - Tốn bộ nhớ vì phải copy dữ liệu
   - Nên dùng khi: chỉ cần đọc dữ liệu, không cần thay đổi giá trị gốc
2. Truyền con trỏ (pass by reference):
   - Truyền địa chỉ của dữ liệu
   - Có thể thay đổi được giá trị gốc
   - Tiết kiệm bộ nhớ vì không copy dữ liệu
   - Nên dùng khi: cần thay đổi giá trị gốc hoặc struct có kích thước lớn
PHẦN 2: STRUCT BÌNH THƯỜNG VS STRUCT CON TRỎ
1. Struct bình thường:
   - Được cấp phát sẵn trên stack
   - Kích thước cố định
   - Tự động giải phóng khi ra khỏi scope
   - Nên dùng khi: kích thước nhỏ, số lượng ít, biết trước số lượng
2. Struct con trỏ (với cấp phát động):
   - Được cấp phát trên heap thông qua malloc
   - Kích thước có thể thay đổi
   - Phải tự giải phóng bằng free
   - Nên dùng khi: kích thước lớn, số lượng nhiều, không biết trước số lượng
PHẦN 3: TẠI SAO CẦN CẤP PHÁT ĐỘNG
1. Nếu không cấp phát động:
   - Con trỏ trỏ đến vùng nhớ không xác định -> crash chương trình
   - Không thể mở rộng kích thước khi cần
   - Bộ nhớ stack bị giới hạn
2. Khi cấp phát động:
   - Quản lý được vùng nhớ heap
   - Có thể mở rộng/thu hẹp kích thước khi cần
   - Tránh tràn stack khi dữ liệu lớn
*/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

// Định nghĩa struct nhỏ
typedef struct {
    int x;
    int y;
} Point;

// Định nghĩa struct lớn
typedef struct {
    char data[1000];
    double values[1000];
    int matrix[100][100];
} BigData;

// Hàm với tham số bình thường - phù hợp với struct nhỏ
void processPoint(Point p) {
    printf("Process Point: (%d, %d)\n", p.x, p.y);
    // p là bản sao, thay đổi p không ảnh hưởng giá trị gốc
    p.x = 100;
    p.y = 100;
}

// Hàm với tham số con trỏ - có thể thay đổi giá trị gốc
void modifyPoint(Point* p) {
    printf("Modify Point: (%d, %d)\n", p->x, p->y);
    // Thay đổi giá trị gốc thông qua con trỏ
    p->x = 100;
    p->y = 100;
}

// Hàm với tham số con trỏ - phù hợp với struct lớn
void processBigData(BigData* data) {
    // Không tốn bộ nhớ copy large struct
    printf("First value: %lf\n", data->values[0]);
}

int main() {
    // 1. Ví dụ với struct nhỏ
    printf("1. Vi du voi struct nho (Point):\n");
    Point p1 = {10, 20};
    
    // Truyền bình thường - tạo bản sao
    processPoint(p1);
    printf("Sau khi processPoint: (%d, %d)\n", p1.x, p1.y); // Giá trị không thay đổi
    
    // Truyền con trỏ - thay đổi giá trị gốc
    modifyPoint(&p1);
    printf("Sau khi modifyPoint: (%d, %d)\n\n", p1.x, p1.y); // Giá trị đã thay đổi

    // 2. Ví dụ với struct lớn
    printf("2. Vi du voi struct lon (BigData):\n");
    
    // KHÔNG NÊN: Khai báo trực tiếp trên stack - có thể gây tràn stack
    // BigData data1;  // Không khuyến khích với struct lớn
    
    // NÊN: Sử dụng con trỏ và cấp phát động
    BigData* data2 = (BigData*)malloc(sizeof(BigData));
    if (data2 != NULL) {
        // Khởi tạo giá trị
        data2->values[0] = 3.14;
        
        // Xử lý dữ liệu
        processBigData(data2);
        
        // Giải phóng bộ nhớ
        free(data2);
    }

    // 3. Ví dụ về mảng động của struct
    printf("\n3. Vi du ve mang dong cua struct:\n");
    
    // Cấp phát động một mảng các Point
    int n = 5;
    Point* points = (Point*)malloc(n * sizeof(Point));
    
    if (points != NULL) {
        // Khởi tạo giá trị
        for(int i = 0; i < n; i++) {
            points[i].x = i;
            points[i].y = i * 2;
        }
        
        // In giá trị
        for(int i = 0; i < n; i++) {
            printf("Point %d: (%d, %d)\n", i, points[i].x, points[i].y);
        }
        
        // Giải phóng bộ nhớ
        free(points);
    }

    // 4. Ví dụ về việc không cấp phát động (SAI)
    printf("\n4. Vi du ve viec KHONG cap phat dong (SAI):\n");
    Point* wrongPoint;  // Con trỏ chưa được cấp phát
    // wrongPoint->x = 10;  // NGUY HIỂM: Có thể gây crash chương trình
    printf("Truy cap con tro chua cap phat co the gay crash chuong trinh!\n");

    return 0;
}