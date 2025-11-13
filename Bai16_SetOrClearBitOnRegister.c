/*
Để set 1 bit, dùng toán tử |
- Để set 1 bit ở vị trí thứ i lên 1:

unsigned char res = 0;
res = res | (1 << i);

- Có thể viết lại 

unsigned char res = 0;
res |= (1 << i);

Để clear 1 bit, dùng toán tử & với ~
- Để clear 1 bit ở vị trí thứ i về 0:

unsigned char res = 0;
res = res & (~(1 << i));

- Có thể viết lại 

unsigned char res = 0;
res &= (~(1 << i));
*/

/*
Ví dụ:
ĐỀ BÀI: Thay đổi giá trị của một bit trong thanh ghi
Mục tiêu:

Viết chương trình C cho phép người dùng thay đổi giá trị của một bit cụ thể trong một thanh ghi 8-bit (kiểu unsigned char).
Chương trình cần cho phép bật (set) hoặc tắt (clear) bit theo vị trí và chế độ được nhập từ bàn phím.

Yêu cầu chi tiết:

Nhập dữ liệu từ bàn phím:

Một số nguyên không dấu 8-bit (reg) – biểu diễn giá trị hiện tại của thanh ghi.

Vị trí bit cần thay đổi (pos), với pos nằm trong khoảng 0–7 (bit thấp nhất là bit 0).

Giá trị mode:

1 → bật bit (set bit) tại vị trí pos.

0 → tắt bit (clear bit) tại vị trí pos.

Xử lý:

Sử dụng phép toán bit (bitwise operators) để thay đổi giá trị bit trong biến reg theo yêu cầu.

Trả về giá trị mới của thanh ghi sau khi thay đổi.

Xuất kết quả:

In ra giá trị thập phân của thanh ghi sau khi bit được thay đổi.

Mô tả thuật toán (ngắn gọn):

Nếu mode == 1 → thực hiện phép OR:
reg = reg | (1 << pos) → bật bit tại vị trí pos.

Nếu mode == 0 → thực hiện phép AND với phủ định:
reg = reg & (~(1 << pos)) → tắt bit tại vị trí pos.
*/

#include <stdio.h>

unsigned char modifyBit(unsigned char reg, int pos, int mode) {
    return (mode == 1) ? (reg | (1 << pos)) : (reg & (~(1 << pos)));
}

int main() {
    unsigned char reg;
    int pos, mode;
    printf("Nhập lần lượt giá trị thập phân của thanh ghi reg, vị trí bit cần thay đổi trong thanh ghi và mode thay đổi 0/1\n");
    scanf("%hhu %d %d", &reg, &pos, &mode);
    printf("Kết quả thanh ghi sau khi thay đổi là: %d", modifyBit(reg, pos, mode));
    return 0;
}
