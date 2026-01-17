/*
Resolve Exam.pdf
*/

/*
Q1.
int i; 
    for (i = 1; i < 101; ++i) 
    { 
        i++; 
    } 
 
    printf("%d", i);

* Note: Kiến thức về vòng for

- Cấu trúc thực hiện của các biểu thức điều khiển trong for loop:

  - initial : khởi tạo: đây là biểu thức chỉ khởi tạo duy nhất 1 lần của vòng for khi vòng for bắt đầu lặp, khi thực hiện xong vòng for, biểu thức này không có thực hiện khởi tạo lại giá trị.

  - condition : điều kiện lặp, đây là biểu thức điều kiện để kiểm tra xem có thỏa điều kiện để thực thi vòng for, biểu thức này sẽ được kiểm tra xuyên suốt vòng for cho đến khi điều kiện lặp sai sẽ thoát vòng for

  - control : điều khiển vòng for : đây là biểu thức điều khiển vòng lặp for, nó sẽ điều khiển biến lặp, nó sẽ hoạt động xuyên suốt vòng for, khi kết thúc vòng for, nếu điều kiện lặp còn đúng thì nó sẽ quay lại đây để thực hiện tiếp chứ không phải quay lại initial để khởi tạo lại biến lặp

- Flow:

  - đầu tiên khởi tạo initial

  - kiểm tra condition, đúng thì thực hiện trong for, sai thì thoát for

  - Thực hiện control

  - So sánh condition, đúng thì thực hiện for, sai thì thoát for

  - Tiếp tục cho đến khi condition sai

=> Resolve Q1.

- Vòng for thứ 1:

  - Ban đầu : initial : i = 1

  - kiểm tra i < 101 => true

  - thực hiện i++ : i tăng 1 đơn vị => i =2

  - quay lại thực hiện control ++i : tăng tiếp i 1 đơn vị => i =3

  => Tổng kết sau 1 vòng for thì i tăng thêm 2 đơn vị

- Vòng for thứ 2:

  - không khởi tạo lại initial

  - Dùng i = 3 ở vòng for trước để so sánh condition ( i = 3 < 101) => thực hiện trong for

  - tăng i++ => i = 4

  - thực hiện control ++i => i = 5

- Vòng for thứ 3, ....

  - thực hiện như các vòng for trước

- Vòng for thứ i <101:

  - Vì mỗi vòng for i tăng 2 đơn vị, đến khi i < 101 => i = 99
  
  - i = 99 nhỏ hơn condition => thực hiện trong for tăng i++ => i = 100

  - tăng i control ++ i => i = 101

  - quay lại kiểm tra condition thấy false => thoát for

=> i cuối cùng = 101
*/

/*
Q2.
char i; 
    for (i = 0; i < 128;) 
    { 
        i++; 
    } 
    printf("%d", i);

=> Resolve

* Note: Kiến thức về byte/bit

- char : kiểu số có dấu, kích thước 1 byte => max value = 127

- đến khi max value = 127, sau khi tăng thêm 1 đơn vị sẽ quay về lại value = 0 chứ không phải lên value = 128

=> Resolve Q2

- Vì max value = 127, nên condition i < 128 luôn true => infinite loop

=> không in ra được gì
*/

/*
Q3.
typedef union 
    { 
        struct Register 
        { 
            unsigned int value1 : 3; 
            unsigned int value2 : 2; 
            unsigned int value3 : 3; 
        } value; 
        unsigned int raw; 
 
    } DemoRegister; 
     
    DemoRegister demo_reg; 
    demo_reg.value.value1 = 1; 
    demo_reg.value.value2 = 2; 
    demo_reg.value.value3 = 3; 
 
    demo_reg.raw = 0xFF; 
     printf("%d %d %d %d",demo_reg.value.value1, demo_reg.value.value2, 
demo_reg.value.value3,      demo_reg.raw);

*Note: Kiến thức về bit trong thanh ghi, union, struct

- Union tạo ra 1 vùng nhớ dùng chung, sau đó vùng nhớ này được chia nhỏ ra thành các phần bằng Struct

- Nhưng Struct này có các trường dữ liệu có kích thước nhỏ hơn kích thước trường dữ liệu Union

- Nói cách khác: 

  - Union tạo ra 1 vùng nhớ lưu biến có kích thước max

  - Struct chia nhỏ vùng nhớ ra thành từng phần nhỏ để quản lý

- Cách viết kiểu `: value` thể hiện biến đó chiếm bao nhiêu bit trong 1 byte thanh ghi

=> Resolve Q3.

- Trong union, kích thước union là kích thước của kiểu dữ liệu lớn nhất => unsigned int => 8 bit = 1 byte

- Union tạo ra 1 vùng nhớ dùng chung lưu trữ biến raw và struct value có kích thước là 1 byte = 8 bit => 2 biến này cùng tác động đến 1 vùng nhớ 1 byte này.

- Struct dùng để chia vùng nhớ này ra thành các vùng nhớ nhỏ hơn có kích thước từng bit để dễ quản lý

  - Các trường trong struct dùng chung 1 vùng nhớ của vùng nhớ do union tạo ra => nói cách khác value1, value2, value3 cùng tác động đến 1 vùng nhớ 8 bit.

- Các vùng nhớ nhỏ được chia theo kiểu quy định số bit gộp thành 1 vùng bằng cách quy định số bit thông qua `: numberOfBit`

  => value1 : 3 bit, value2: 2 bit, value3 : 3bit

- Sau đó khởi tạo 1 đối tượng từ kiểu Union, truy cập vào vùng nhớ do union tạo ra, truy cập vào vùng nhớ nhỏ hơn để gắn giá trị lần lượt cho value1, value2, value3 là 1 2 3

  => [0 : 2] bit đầu : 1, [3 : 4] : 2, [5 : 7] : 3

- Nhưng sau đó lại thay đổi gán cho raw = 0xFF => tác động vào vùng nhớ 8 bit này làm thay đổi toàn bộ giá trị trên dùng nhớ sang 1111 1111

  => [0 : 2 ] bit đầu : 7, [3 : 4] = 3, [5 , 7] : 7
*/

/*
Q4.

void hello() 
    { 
        printf("Hello"); 
    } 
    void welcome() 
    { 
        printf("welcome"); 
    } 
 
    int main() 
    { 
        void (*funcPtr)(); 
        void (*funcPtr2)(); 
         
        funcPtr = hello; 
        funcPtr2 = welcome; 
        funcPtr = funcPtr2; 
         
        funcPtr(); 
    }

* Note : Kiến thức về function pointer

- Mỗi hàm tạo ra sẽ có 1 địa chỉ cụ thể

- Các hàm có KDL và tham số giống nhau có thể được quản lý thông qua 1 con trỏ hàm

- việc dùng con trỏ hàm giúp có thể gọi các hàm khác nhau linh hoạt hơn mà không cần phải gọi trực tiếp hàm

=> Resolve Q4

- Kết quả là Welcome
*/

/*
Q5.
#define HCET -1 
    #ifdef  HCET 
    void printMes() 
    { 
        printf("WIN"); 
    } 
    #endif 
 
    #ifndef HCET 
    void printMes() 
    { 
        printf("LOSE"); 
    } 
    #endif 
 
    int main() 
    { 
        printMes(); 
    }

* Note : Kiến thức về tiền xử lý

=> Resolve Q5

- Kết quả là WIN vì HCET đã được define
*/

/*
Q6.
enum number  
{ one = 1, 
       two = 2, 
       three, 
       five, 
       four = 4, 
       six, 
       seven = 7  
    }; 
    int main() 
    { 
        printf(“%d %d %d”, five, four, six); 
    }

* Note : Kiến thức về enum

- Định nghĩa các trường bằng 1 số nguyên

- nếu số sau không được định nghĩa thì sẽ được định nghĩa bằng số nguyên liền trước + 1

- Nếu giữa chừng có giá trị đã được định nghĩa số nguyên thì vẫn ko sao, bình thường.

=> Resolve Q6

three = 2 + 1 = 3

five = 3 + 1 = 4

six = 4 (four) + 1 = 5
*/

/*
Q7.
int a = 1, b = 2, c = 3, d = 4; 
    int *pa = &a, *pb = &b, *pc = &c, *pd = &d; 
    pb = &c; 
    pb = &d; 
    pa = &b; 
    pc = &a; 
    b = a + d; 
    d = b + c; 
    pb = pc; 
    pb = pa; 
    pa = &b; 
    pc = pd; 
    pb = &c; 
    pd = &d; 
    printf("%d %d %d %d",*pa, *pb, *pc, *pd);

* Note : Kiến thức liên quan đến con trỏ

- Con trỏ có tính chất:

  - Tại 1 thời điểm, con trỏ chỉ trỏ đến 1 địa chỉ nhất định tại thời điểm đó.

=> Resolve Q7.

- Quan tâm con trỏ tại thời điểm đó thì con trỏ đang trỏ đến biến, địa chỉ nào và giá trị của nó đang là bao nhiêu

- b = a + c = 5

- d = b + c = 8

- pa = &b => pa trỏ đến b = 5

- pb = &c => pc trỏ đến c = 3

- pc = pd => (*pd = &d) => pd = 8

- pd = &d => pd trỏ đến d = 8
*/

/*
Q8.
int main() 
    { 
        int arr[] = {1, 2, 3, 4, 5}; 
        int *ptr = arr; 
        printf("%d %d %d %d %d %d", *ptr, ++*ptr++, (*ptr)++, *ptr++, *++ptr, ++*ptr); 
        return 0; 
    }

=> Resolve Q8

- Xem trong Theory/Bai04_BaiTapPointer.c
*/

/*
Q9.
typedef struct  
    { 
        int a; 
        int b; 
        int c; 
        int d; 
        int f; 
        int g; 
        int h; 
 
    } MyStruct; 
 
    typedef struct 
    { 
        char a; 
    } MyStruct2; 
 
    int main() 
    { 
 
        MyStruct a; 
        a.a = 65; 
        a.b = 66; 
        a.c = 67; 
        a.d = 68; 
 
        MyStruct2 *b = (MyStruct2 *)&a; 
 
        b += 4; 
         
   printf(“%c”, b -> a); 
    }

* Note: Ép kiểu con trỏ

=> Resolve Q9

- Vì MyStruct có kiểu dữ liệu int 4 byte

- MyStruc2 có kiểu dữ liệu char 1 byte

- Để MyStruct2 truy cập được vào Data của MyStruct thì cần phải ép kiểu về cùng kiểu char và cùng truy cập vào 1 vùng Data nên khai báo con trỏ

- b += 4 nghĩa là + thêm 4 byte để nhảy từ index thứ 2 trong Data MyStruct

=> B
*/

/*
Q10.
typedef struct  
    { 
        short a; 
        long b; 
        char c; 
    } tem; 
 
    typedef struct  
    { 
        short a; 
        char c; 
        long b; 
    } tem2; 
 
    int main() 
    { 
 
        tem a; 
        tem2 b; 
        printf("%d %d", sizeof(a), sizeof(b));     
    }

* Note : Size Struct

- Khi tạo Struct, nó sẽ căn lề theo kiểu dữ liệu nguyên thủy có kiểu dữ liệu có kích thước lớn nhất

- Padding sẽ là kích thước của kDL nguyên thủy lớn nhất.

- các trường trong Struct sẽ chiếm kích thước như sau:

  - Khi khởi tạo 1 trường, Struct sẽ tạo ra 1 padding để lưu trường đó.

  - Nếu < kích thước padding, thì sẽ còn dư lại 1 phần padding

  - Trường tiếp theo sẽ được lưu vào tiếp, nhưng nếu trường tiếp theo có kích thước > padding còn dư lại thì sẽ tạo thêm 1 padding mới và lưu trường mới vào padding mới chứ không phải padding còn dư

  - Nhưng nếu trường mới có kích thước lưu vừa với padding còn lại thì tiếp tục lưu vào padding con lại đó chứ không tạo thêm trường mới

=> Resolve Q10

- struct tem có lần lượt:

  - short : 2 byte

  - long : 4 byte

  - char : 1 byte

  => padding 4 byte. Lưu 2 byte đầy ok, 4 byte tiếp theo > padding còn lại nên tạo thêm padding 4 byte nữa để lưu, lưu hết padding tạo thêm 1 padding để lưu 1 byte cuối cùng = > 12 byte

- struct tem2:

  - short : 2 byte

  - char : 1 byte

  - long : 4 byte

  => padding 4 byte. Lưu 2 byte đầu k, còn dư 2 byte padding, vừa đủ cho 1 byte tiếp theo nên cx lưu vào mà ko tạo padding mới, 4 byte cuối không đủ padding còn lại nên tạo thêm padding mới và lưu 4 byte cuối vào => 8 byte

=> 12, 8
*/

#include <stdio.h>

int main() {

    return 0;
}
