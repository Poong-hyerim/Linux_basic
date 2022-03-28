#include <stdio.h>
//malloc사용을 위한 헤더 선언
#include <stdlib.h> 

void main()
{
    printf("[----- [풍혜림] [2019020028] -----]\n");
    int list[5];                           //이름은 list, 5개 짜리 int형 배열 선언
    int *plist[5] = {NULL,};               //이름은 plist, 5개 짜리 int형 포인터 배열 선언과 동시에 NULL로 초기화
    plist[0] = (int *)malloc(sizeof(int)); //malloc으로 포인터 배열 첫번째 자리인 plist[0]에 int size(4byte) 메모리 주소값 할당
    list[0] = 1;                           //int형 배열 list 첫번째 자리인 list[0]에 값 1 할당
    list[1] = 100;                         //int형 배열 list 두번째 자리인 list[1]에 값 100 할당
    *plist[0] = 200;                       //plist[0]이 가리키는 위치(*의미)에 값 200 할당

    printf("value of list[0] = %d\n", list[0]);       //list[0]에 할당된 값 : 1
    printf("address of list[0] = %p\n", &list[0]);    //list[0]의 주소 : 0x16dac7264       
    printf("value of list = %p\n", list);             //list에 할당된 값(주소값) : 0x16dac7264 
    printf("address of list (&list) = %p\n", &list);  //list의 주소(&list) : 0x16dac7264
    /*&list==list==list[0]==배열이 시작되는 주소!*/

    printf("----------------------------------------\n\n");
    printf("value of list[1] = %d\n", list[1]);       //list[1]에 할당된 값 : 100
    printf("address of list[1] = %p\n", &list[1]);    //list[1]의 주소 : 0x16dac7268
    printf("value of *(list+1) = %d\n", *(list + 1)); //(list+1)주소에 할당되어있는 값 : 100
    printf("address of list+1 = %p\n", list+1);       //(list+1)의 주소(&(list+1)) : 0x16dac7268

    printf("----------------------------------------\n\n");
    printf("value of *plist[0] = %d\n", *plist[0]);   //plist[0]에 할당된 주소에 할당된 값 : 200
    printf("&plist[0] = %p\n", &plist[0]);            //plist[0]의 주소 : 0x16dac7238
    printf("&plist = %p\n", &plist);                  //plist의 주소(&plist) : 0x16dac7238
    printf("plist = %p\n", plist);                    //plist에 할당된 값(주소값) : 0x16dac7238
    printf("plist[0] = %p\n", plist[0]);              //plist[0]에 할당된 값(주소) : 0x600003ac4030(이 주소에 200이 할당되어있음)
    printf("plist[1] = %p\n", plist[1]);              //plist[1]에 할당된 값(주소) : 0x0 초기화된 NULL 그대로
    printf("plist[2] = %p\n", plist[2]);              //plist[2]에 할당된 값(주소) : 0x0 초기화된 NULL 그대로
    printf("plist[3] = %p\n", plist[3]);              //plist[3]에 할당된 값(주소) : 0x0 초기화된 NULL 그대로
    printf("plist[4] = %p\n", plist[4]);              //plist[4]에 할당된 값(주소) : 0x0 초기화된 NULL 그대로
    free(plist[0]);                                   //malloc으로 plist[0]에 할당한 메모리 해제 free.
}