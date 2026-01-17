/*
3. Con trỏ hàm

- Khi khởi tạo 1 function thì function đó được quản lý bởi 1 địa chỉ
- để quản lý địa chỉ hàm cần dùng 1 con trỏ hàm và để gọi đến hàm đó
- những hàm có cùng KDL trả về, cùng KDL tham số truyền vào thì có thể quản lý chúng thông qua con trỏ hàm
- Định nghĩa 1 con trỏ hàm:
    + Syntax: typedef KDL_trả_về (*tên_con_trỏ_hàm)(KDL_Tham_số_truyền_vào);
- Khởi tạo 1 con trỏ hàm đã định nghĩa:
    + Syntax: tên_con_trỏ_hàm tên_khởi_tạo_con_trỏ_hàm;
- Lúc này con trỏ hàm đã được khởi tạo và có thể dùng nó để gán các hàm muốn dùng có cùng KDL trả về và cùng KDL tham số truyền vào
    m = tên_hàm;
    => m đóng vai trò như là hàm đó, có chức năng của hàm đó.
- Thực chất không cần call function thông qua name_function mà có thể call thông qua địa chỉ của function đó
- Ứng dụng của con trỏ hàm trong thực tế:
    + VD năm 2025 1 ic có 3 thanh ghi => viết 5 function có cùng KDL trả về là void, cùng tham số truyền vào là uint8_t
    + đến 2026, phát triển từ 3 function lên 10 function cần viết thêm code để tối ưu và dễ code, bảo trì 
*/

/*
1. Câu hỏi gốc của bạn (đặt lại cho đúng bản chất)

“Tại sao không gọi thẳng hàm, mà lại gọi con trỏ hàm?”

👉 Câu trả lời ngắn gọn nhất:

Vì tại thời điểm viết code, ta CHƯA BIẾT sẽ gọi hàm nào, hoặc muốn thay đổi hành vi mà KHÔNG sửa code đang chạy.

Nếu bạn luôn biết chắc hàm cần gọi, thì:

❌ KHÔNG cần con trỏ hàm

Gọi thẳng là đơn giản + nhanh + dễ đọc nhất

👉 Con trỏ hàm chỉ xuất hiện khi:

Hành vi cần linh hoạt

Phần gọi hàm không được quyền biết chi tiết hàm nào sẽ chạy

2. Trường hợp KHÔNG CẦN con trỏ hàm (bạn đang nghĩ đúng)
void LedOn(void) {
    GPIO_SetPin();
}

int main(void) {
    LedOn();   // GỌI THẲNG – quá hợp lý
}


✔ Không vấn đề
✔ 99% code beginner là như vậy
✔ Embedded chạy tốt

➡ Vậy tại sao người ta còn dùng con trỏ hàm?

3. Vấn đề xuất hiện khi: “AI quyết định gọi hàm?”
Ví dụ rất đời thường trong embedded:

Khi có sự kiện → chạy hành động tương ứng

Ví dụ:

Nút 1 → bật LED

Nút 2 → tắt LED

Nút 3 → nháy LED

Nếu bạn viết kiểu gọi thẳng:

if(button == 1) LedOn();
else if(button == 2) LedOff();
else if(button == 3) LedBlink();


✔ OK với 3 nút
❌ Rất tệ nếu:

Có 20 nút

Hành động thay đổi liên tục

Hành động do module khác quyết định

4. Lúc này ta tách làm 2 vai trò (RẤT QUAN TRỌNG)
🔹 Vai trò 1: Người gọi

“Tôi chỉ biết là cần gọi MỘT HÀM, tôi không quan tâm nó là hàm gì”

🔹 Vai trò 2: Người quyết định

“Tùy tình huống, tôi gán cho bạn hàm phù hợp”

👉 Con trỏ hàm chính là cây cầu giữa 2 vai trò này

5. Ví dụ cực đơn giản – thấy ngay lý do tồn tại
void LedOn(void)   { // Bật led }
void LedOff(void)  { // Tắt led }

void (*Action)(void);   // con trỏ hàm

Giai đoạn 1 – quyết định hành vi
if(button == 1)
    Action = LedOn;
else
    Action = LedOff;

Giai đoạn 2 – chỉ việc gọi
Action();   // KHÔNG BIẾT, KHÔNG CẦN BIẾT là hàm nào


👉 Đây chính là điểm “À HÁ!”

Code gọi không thay đổi

Hành vi thay đổi hoàn toàn

Không if–else rối rắm

6. Embedded dùng con trỏ hàm ở ĐÂU TRONG THỰC TẾ?
1️⃣ Interrupt / Callback
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    ButtonHandler();   // thực chất bên trong thường là con trỏ hàm
}


HAL gọi hàm của bạn mà không biết bạn viết gì

2️⃣ Driver độc lập phần cứng (HAL, BSP)
typedef struct {
    void (*Init)(void);
    void (*Write)(uint8_t);
} LCD_Driver;


👉 STM32 / Arduino / ESP sống nhờ cái này

3️⃣ State Machine
state = STATE_IDLE;
StateTable[state]();


➡ Không con trỏ hàm = if–else khổng lồ

4️⃣ RTOS – Task, Hook, Timer
xTimerCreate("T", 1000, pdTRUE, 0, TimerCallback);


⛔ Không có con trỏ hàm → RTOS không tồn tại

7. Vậy TẠI SAO KHÔNG DÙNG switch hay if?
Cách	Nhược điểm
if / switch	code phình to
if / switch	khó mở rộng
if / switch	module bị phụ thuộc nhau
con trỏ hàm	linh hoạt
con trỏ hàm	code gọn
con trỏ hàm	driver độc lập

👉 Embedded ưu tiên:

RAM nhỏ

Flash ít

Dễ bảo trì

8. Tóm lại – GHI VÀO VỞ (RẤT QUAN TRỌNG)
❌ ĐỪNG dùng con trỏ hàm khi:

- Chỉ có 1 hành vi

- Gọi trực tiếp là đủ

- Code đơn giản

✅ DÙNG con trỏ hàm khi:

- Hàm được quyết định tại runtime

- Module gọi không biết chi tiết module được gọi

- Callback / interrupt / driver

- State machine / menu / event system

Con trỏ hàm KHÔNG để “viết cho ngầu”
Nó tồn tại vì Embedded không thể sống nếu thiếu nó

9. Câu hỏi mình muốn bạn tự trả lời (rất quan trọng)

👉 Khi bạn thấy code dùng con trỏ hàm, hãy tự hỏi:

“Ai là người quyết định hàm này?”
“Người gọi có được quyền biết hàm thật hay không?”
*/
    
#include <stdio.h>
#include <stdint.h>

#define CNT 3

// khai báo nguyên hàm
void view(uint8_t x);
void viewx2(uint8_t x);

// định nghĩa hàm
void view(uint8_t x) {
    printf("%d\n", x);
}

void viewx2(uint8_t x) {
    printf("%d\n", x*2);
}

// =======================================
typedef void (*mFunction)(uint8_t);

// =======================================
void reg1() {
    printf("reg1\n");
}

void reg2() {
    printf("reg2\n");
}

void reg3() {
    printf("reg3\n");
}

void (*mfunction[CNT])() = {reg1, reg2, reg3};

int main() {

    mFunction m;
    m = view;
    m(2);

    m = viewx2;
    m(2);

    // ===============================================
    uint64_t address;
    printf("add = %p\n", address = (uint64_t)view);

    ((mFunction)address)(1);

    // ================================================
    for (int i = 0 ; i < CNT ; i++) {
        mfunction[i]();
    }
    /*
    nếu không dùng con trỏ hàm mà muốn thực thi từng hàm cần phải call
    reg1();
    reg2();
    reg3();
    nếu sau cần thêm vào reg4() chỉ cần khai báo nguyên hàm và định nghĩa hàm, rồi thêm vào mảng con trỏ hàm thì không cần sửa code trong main, tránh lỗi code
    */

    return 0;
}
