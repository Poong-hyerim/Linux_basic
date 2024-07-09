#include <stdio.h>
void print1 (int *ptr, int rows); //(사용자 정의 함수)포인터 이용, 1차원 배열 출력 함수 정의

int main()
{
    printf("[----- [풍혜림] [2019020028] -----]\n");
    int one[] = {0, 1, 2, 3, 4};        //int형 배열 one 선언과 동시에 5개 원소{0, 1, 2, 3, 4}를 차례로 할당
    printf("one = %p\n", one);          //배열 이름 one이 나타내는 주소 : 0x16b16f260
    printf("&one = %p\n", &one);        //배열 one의 주소(&one) : 0x16b16f260
    printf("&one[0] = %p\n", &one[0]);  //배열의 첫번째 원소 one[0]의 주소 : 0x16b16f260
    printf("\n");
    print1(&one[0], 5);                 //print1 함수 이용 배열의 원소 출력
    
    return 0;
}

/*int형 포인터와 int형 rows를 입력받아 배열의 0번째 원소부터 rows-1번째 원소까지를 출력해주는 함수*/
void print1 (int *ptr, int rows)
{
    /* print out a one-dimensional array using a pointer */
    int i;
    printf ("Address \t Contents\n");           //출력 시 주소와 할당된 값을 구분해서 보기 편하게 해줌

    for (i = 0; i < rows; i++)
    printf("%p \t %5d\n", ptr + i, *(ptr + i));
    /*ptr+i를 서식지정자 %p로 출력해 address를*/
    /*주소 (ptr+i)를 역참조(*기호)해 주소가 가리키는 배열 값 contents를 출력함*/
    printf("\n");
}