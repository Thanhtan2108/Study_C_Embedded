/*
vd 1 project của 4 button, 3 led, 1 pin => cần quản lý 8 device nầy như thế nào?

Thay vì tạo ra 4 byte cờ để quản lý thì sẽ quả lý theo bit để quản lý => bộ nhớ sẽ được tiết kiệm

Ý tưởng:
    - sẽ chỉ tạo ra 1 biến 1 byte (8 bit) để quản lý 8 device, mỗi device là 1 bit
    - mỗi device sẽ quản lý bằng 1 cờ - 1 bit
    - sau đó dùng các define function để quản lý việc set, clear, check bit để khi code trong main hạn chế dùng các phép toán, làm cho code dễ đọc hơn
    - các define function này sẽ được dùng cho từng mục đích, yêu cầu cụ thể
*/

#include <stdio.h>
#include <stdint.h>

/*
status
BIT0            Status BTN1: 1-on 0-off
BIT1            Status BTN2: 1-on 0-off
*/

uint8_t status = 0x00;

#define FLAG_BTN1 0x00
#define FLAG_BTN2 0x01
#define FLAG_BTN3 0x02
#define FLAG_BTN4 0x03
#define FLAG_LED1 0x04
#define FLAG_LED2 0x05
#define FLAG_LED3 0x06
#define FLAG_BAT  0x07

//-------------------FLAG_LED1---------------
#define SET_FLAG_LED1()     (status |= (1 << FLAG_LED1)) // or với bit 1
#define CLR_FLAG_LED1()     (status &= ~(1 << FLAG_LED1)) // and với bit 0
#define CHECK_FLAG_LED1()   (status & (1 << FLAG_LED1)) // and với bit 1

int main() {


    return 0;
}
