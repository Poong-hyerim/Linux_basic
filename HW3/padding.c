#include <stdio.h>
struct student {
char lastName[13];  /* 13 bytes */
int studentId;      /*  4 bytes */
short grade;        /*  2 bytes */
};

int main()
{
    printf("[----- [풍혜림] [2019020028] -----]\n");
    struct student pst;
    printf("size of student = %ld\n", sizeof(struct student));
    /*
    13+4+2 = 19인데 sizeof(struct student)의 출력 결과는 24byte를 나타냄
    이는 gcc 컴파일러가 padding을 지원하기 때문인데, 메모리 상의 빈공간을 채워주는 것을 뜻함!
    lastName 13 byte = 4+4+4+1(1byte 뒤에 남는 3byte padding!) = 16byte
    student Id 4 byte = 4byte
    grade = 2(2byte 뒤에 남는 2byte padding!) = 4byte
    struct student = 16+4+4 = 24byte!
    */
    printf("size of int = %ld\n", sizeof(int));       //int 크기 : 4byte
    printf("size of short = %ld\n", sizeof(short));   //short 크기 : 2byte
    
    return 0;
}