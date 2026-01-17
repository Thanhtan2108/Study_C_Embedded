/*
and bit : & : cái gì and với 0 đều bằng 0, mục đích để clear bit về 0
or bit : | : cái gì or với 1 đều = 1, mục đích để set bit lên 1
not bit : ~ : đảo bit
xor bit : giống nhau bằng 0, khác nhau bằng 1
shift left : <<
shift right : >>
*/

#include <stdio.h>
#include <stdint.h>

uint8_t data = 0; // 0b00000000
uint8_t Data = 0x08;

int main() {
    data |= (1 << 3);
    /*
    số 1 : 0000 0001
    1 << 3 : 0000 1000
    data = 0000 0000
    data | (1 << 3) = 0000 1000 = 8
    */
    Data &= ~(1 << 3);
    /*
    số 1 : 0000 0001
    1 << 3 : 0000 1000
    ~(1 << 3) : 1111 0111
    Data : 0000 1000
    Data & ~(1 << 3) : 0000 0000 = 0
    */
    return 0; 
}
