#include <stdio.h>
#define MAX_SIZE 100            //배열의 크기(전역변수로)를 100으로 선언
float sum(float [], int);       //sum 함수(사용자 정의함수)정의
float input[MAX_SIZE], answer;  //float형 배열 input(현재 크기는 100)와 float형 변수 answer 선언
int i;                          //int형 변수 i 선언

void main(void)
{
    printf("[----- [풍혜림] [2019020028] -----]\n");
    //0부터 MAX_SIZE까지 i를 1씩 증가시키며 float형 배열 input에 i를 할당함(0-99까지 차례대로 할당)
    for(i=0; i < MAX_SIZE; i++)
    input[i] = i;

    /* for checking call by reference : 주소값을 전달해 줌 */
    printf("address of input = %p\n", input);  //배열 input의 주소 : 0x104960008
    answer = sum(input, MAX_SIZE);             //함수 sum에 float형 배열 input과 MAX_SIZE를 대입한 후 결과를 float형 변수 answer에 할당
    /*함수가 호출되며 value of list : 0x104960008, address of list : 0x16b4a7248 출력*/

    printf("The sum is: %f\n", answer);        //합계로 answer의 값 출력 : 4950.000000
}

/*float형 배열과 int형 n을 입력받아 배열의 0번째 원소부터 n-1번째 원소까지의 합계를 구해주는 함수*/
float sum(float list[], int n)
{
    printf("value of list = %p\n", list);      //0x104960008 sum에 대입된 float 배열(함수 내에서 list로 표현)의 주소 (이 경우 넘겨준 input의 주소)
    printf("address of list = %p\n\n", &list); //0x16b4a7248 float 배열을 대입하는 실제 list의 주소(이 주소에 input의 주소를 넘겨받음)
    
    int i;
    float tempsum = 0;
    
    for(i = 0; i < n; i++)                     //이 경우 0부터 MAX_SIZE-1인 99까지 합을 구함
    tempsum += list[i];
    
    return tempsum;                            //tempsum = 4950.000000
}