// KQ: 4 5 3 2 2 2

/*
Kiến thức cực kỳ quan trọng:
1. hàm printf() thực hiện từ phải qua trái chứ không phải từ trái qua phải.
2. Kiến thức về poiter.
    - Cộng giá trị con trỏ trước khi thực hiện: ++*ptr
    - Cộng giá trị con trỏ sau khi thực hiện : (*ptr)++
    - Dịch con trỏ sang phải 1 đơn vị trước khi thực hiện: ++ptr
    - Dịch con trỏ sang phải 1 đơn vị sau khi thực hiện: ptr++ 
*/
#include <stdio.h>

int main() {
    int arr[] = {1,2,3,4,5};
    int* ptr = arr; // trỏ vào phần tử đầu tiên của mảng : 1 
    printf("%d %d %d %d %d %d", *ptr, ++*ptr++, (*ptr)++, *ptr++, *++ptr, ++*ptr);
    /*
    lúc đầu : *ptr = 1 , index 0 => 1 2 3 4 5
    ++*ptr = ++1 = 2 , index 0 => 2 2 3 4 5
    ++ptr : thực hiện tính trước, dịch con trỏ sang phải 1 đơn vị cùng số byte tương ứng = index 1 => 2 2 3 4 5
    *++ptr : lấy giá trị của con trỏ đã được thực hiện phép tính xong rồi = * index 1 = 2 => 2 2 3 4 5
    ptr++ : thực hiện tính sau, dịch con trỏ sang phải 1 đơn vị cùng số byte tương ứng = index 2 => 2 2 3 4 5
    *ptr++ : lấy giá trị tại con trỏ chưa được thực hiện phép tính, xong lệnh này con trỏ mới đến index 2 = * index 1 = 2 => 2 2 3 4 5
    con trỏ đã đến index 2 sau khi thực hiện xong lệnh trên
    (*ptr)++ : in ra giá trị index 2 trước rồi sau đó tăng giá trị index 2 lên 1 đơn vị = 3 => 2 2 4 4 5
    ++*ptr++ : thực hiện tăng giá trị con trỏ lên 1 đơn vị trước, in ra rồi mới dịch sang phải 1 đơn vị = 5 => 2 2 5 4 5
    sau lệnh này con trỏ đang tại index 3
    *ptr : giá trị con trỏ đang trỏ tới tại vị trí index nó đang đứng = *index 3 = 4
    => kết thúc chương trình được kq: 4 5 3 2 2 2, con trỏ ở index 3.
    */
    return 0;
}