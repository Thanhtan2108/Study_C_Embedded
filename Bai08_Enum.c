/*
trong embedded, enum thường dùng để định nghĩa ra các trạng thái của 1 đối tượng nào đó

*/

#include <stdio.h>
#include <stdint.h>

typedef enum {
    SUCCESS, // 0
    NOT_FOUND, // 1
    ERROR // 2
} RETURN_STATUS;


/*
Nếu team work ko có quy ước các trạng thái rõ ràng dẫ đến việc đọc code mất thời gian
Khó quản lý, bảo trì

Trong trường hợp hàm này kiểm tra nếu 1 thì thành công. 
int checkIC() {
    int check;
    if (1) {
       check = 1; 
    }
    return check;
}

Nhưng lỡ có người khác quy ước 0 mới là thành công?
*/

// cho thấy việc dùng enum để quy ước trạng thái được ra đời để giải quyết
RETURN_STATUS checkIC() {
    RETURN_STATUS check = SUCCESS;
    if (check == 0) {

    } else if (check == 2) {
        check = NOT_FOUND;
    } else {
        check = ERROR;
    }
    return check;
}

int main() {

    return 0;
}