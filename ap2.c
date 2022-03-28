#include <stdio.h>
#include <stdlib.h>

void main()
{
    printf("[----- [풍혜림] [2019020028] -----]\n");
    int list[5];    //int형 배열 list선언(크기 5)
    int *plist[5];  //int형 포인터 배열 plist선언(크기 5)
    list[0] = 10;   //list 첫번째 값 = 10 할당
    list[1] = 11;   //list 두번째 값 = 11 할당
    plist[0] = (int*)malloc(sizeof(int));
    /*malloc으로 포인터 배열 첫번째 자리인 plist[0]에 int size(4byte) 메모리 주소값 할당*/

    printf("list[0] \t= %d\n", list[0]);             //list[0]에 할당되어있는 값 : 10
    printf("address of list \t= %p\n", list);        //list의 주소(&list) : 0x16d077264
    printf("address of list[0] \t= %p\n", &list[0]); //list[0]의 주소(&list[0]) : 0x16d077264
    printf("address of list + 0 \t= %p\n", list+0);  //list+0의 주소(=&list[0]) : 0x16d077264 
    printf("address of list + 1 \t= %p\n", list+1);  //list+1의 주소(=&list[1]) : 0x16d077268 
    printf("address of list + 2 \t= %p\n", list+2);  //list+2의 주소(=&list[2]) : 0x16d07726c
    printf("address of list + 3 \t= %p\n", list+3);  //list+3의 주소(=&list[3]) : 0x16d077270 
    printf("address of list + 4 \t= %p\n", list+4);  //list+4의 주소(=&list[4]) : 0x16d077274
    printf("address of list[4] \t= %p\n", &list[4]); //list[4]의 주소(=list+4)  : 0x16d077274
    /*list는 메모리 상에 연속된 배열이므로 그 크기인 4byte(int의 크기) 간격으로 주소값이 떨어져 있음을 볼 수 있다 :D*/

    free(plist[0]);
    /*malloc 사용 후 메모리 반드시 해제!*/
}