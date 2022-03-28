#include<stdio.h>
#include<stdlib.h>

void main()
{
    printf("[----- [풍혜림] [2019020028] -----]\n");
    int **x;                                    //int형 이중포인터 x 선언
    printf("sizeof(x) = %lu\n", sizeof(x));     //주소를 저장함 8byte - 64bit 기준
    printf("sizeof(*x) = %lu\n", sizeof(*x));   //주소를 저장함 8byte - 64bit 기준
    printf("sizeof(**x) = %lu\n", sizeof(**x)); //실제 값(int)저장함 4byte
}