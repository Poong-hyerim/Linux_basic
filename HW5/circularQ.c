#include <stdio.h>
#include <stdlib.h>
/* 큐의 최대 크기는 4 */
#define MAX_QUEUE_SIZE 4
/* 큐를 나타내는 기본 구조체와 원소를 나타내는 element 타입 선언 */
typedef char element;	 			//큐에 저장될 원소 타입인 element형을 미리 선언
typedef struct {		 			//원형 큐를 나타내는 구조체 QueueType 선언
	element queue[MAX_QUEUE_SIZE];  //실제 원소가 저장되는 element형 배열 queue 선언
	int front, rear;				//원소가 삭제되는 지표 front(맨앞), 원소가 삽입되는 지표 rear(맨뒤)를 각각 선언
}QueueType;
/* 사용자 정의 함수 선언 */
QueueType *createQueue();					//f1.큐 생성 후 front,rear 초기화
int freeQueue(QueueType *cQ);				//f2.원형 큐에 할당된 메모리 해제
/* f3은 맨아래에 선언함 - 사용자 정의 함수 선언 순서는 번호와 같음! */
int isEmpty(QueueType *cQ);					//f4.큐가 비었을 경우
int isFull(QueueType *cQ);					//f5.큐가 꽉찼을 경우
void enQueue(QueueType *cQ, element item);  //f6.입력받은 원소를 원형 큐에 삽입
void deQueue(QueueType *cQ, element* item); //f7.입력받은 원소를 원형 큐에서 삭제, item에 업데이트 해줌
void printQ(QueueType *cQ);					//f8.현재 원형 큐의 원소 배치 상태를 출력
void debugQ(QueueType *cQ); 				//f9.현재 원형 큐의 구성상황(rear와 front 배치상황 등)을 출력
element getElement();						//+ f3.큐에 원소 할당
/* main 함수 - circularQ 조작의 핵심부 사용자 선택 메뉴를 입력받고 해당 함수를 실행시킴 */
int main(void)
{
	printf("[----- [풍혜림]  [2019020028] -----]");
	QueueType *cQ = createQueue(); //큐 생성
	element data;				   //element형 변수 data 선언
	char command;				   //명령 종류를 저장할 변수 command 선언
	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");	 //명령 입력 안내 :
		scanf(" %c", &command);  //사용자가 명령 입력
		/* 사용자 명령 입력에 따라 분기함 */
		switch(command) {
        //i(또는I)를 입력한 경우 : Insert 모드(data에 원소를 할당 받고 data를 새로 큐에 추가)
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		//d(또는D)를 입력한 경우 : Delete 모드(큐에서 원소를 제거, 제거된 원소는 data로 저장)
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		//p(또는P)를 입력한 경우 : Print 모드(현재 큐의 원소 배치 상황을 출력)
		case 'p': case 'P':
			printQ(cQ);
			break;
		//b(또는B)를 입력한 경우 : Debug 모드(현재 큐에서 front, rear의 배치 상황을 추가로 출력)
		case 'b': case 'B':
			debugQ(cQ);
			break;
		//q(또는Q)를 입력한 경우 : Quit 모드(Circular Q 조작을 마치고 종료)
		case 'q': case 'Q':
   	        freeQueue(cQ);
			break;
		//선택지 이외의 입력 경우 : 명령을 재선택할 수 있도록 안내
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	/* Quit 모드인 q, Q 입력이 있기 전까지 Circular Q 조작을 반복함 */
	}while(command != 'q' && command != 'Q');
	return 1;
}
/* f1.큐 생성 후 front,rear 초기화 */
QueueType *createQueue()
{
	QueueType *cQ; 								 //큐타입형 구조체 포인터 cQ선언
	cQ = (QueueType *)malloc(sizeof(QueueType)); //cQ(포인터)에 구조체 크기만큼 메모리 할당
	cQ->front = 0; 								 //cQ front를 0으로 초기화-(초기 상태의 빈 원형 큐)
	cQ->rear = 0; 								 //cQ rear를 0으로 초기화-(초기 상태의 빈 원형 큐)
	return cQ;									 //생성된 cQ를 return
}
/* f2.원형 큐에 할당된 메모리 해제 */
int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1; //큐가 NULL이면 해제하지 않고 1 return
    free(cQ);			     //아니면 free로 cQ에 해당된 메모리 해제
    return 1;
}
/* f3.큐에 원소 할당 */
element getElement()
{
	element item;
	printf("Input element = ");  //안내문 출력
	scanf(" %c", &item);		 	 //입력된 원소를 item에 임시 저장
	return item;				 //item에 저장된 입력 원소 return
}
/* f4.큐가 비었을 경우 */
/* 원형 큐에서 큐가 비었을 조건은 front와 rear가 같을 경우임 */
int isEmpty(QueueType *cQ)
{
	/* 초기상태와 같이 front, rear가 같아지면 큐의 empty를 뜻하므로 둘의 일치를 판단 */
	if(cQ->front==cQ->rear){
		printf("원형 큐가 비어있습니다.");
		return 1;
	}
	else return 0;
}
/* f5.큐가 꽉찼을 경우 */
/* 원형 큐에서 큐가 꽉찰 조건은 최대 원소의 수가 MAX_QUE_SIZE-1로, front와 rear 사이의 1칸 공백이 있음 */
int isFull(QueueType *cQ)
{
	/* front와 rear사이 공백을 고려해 rear에 +1을 하고 모듈러 연산을 통한 값과 front 위치를 비교해 일치를 판단 */
	if((cQ->front)==((cQ->rear+1)%MAX_QUEUE_SIZE)){
		printf("원형 큐가 모두 찼습니다.");
		return 1;
	}
   return 0;
}
/* f6.입력받은 원소를 원형 큐에 삽입 */
void enQueue(QueueType *cQ, element item)
{
	/* 큐가 full일 경우(isFull이 1을 리턴, 조건문이 참이 됨), 더이상의 삽입이 불가하므로 */
	if(isFull(cQ))
	/* 바로 return */
	return;
	/* 그렇지 않다면, 원소 삽입을 진행 */
	else{
		/* rear를 1 증가시킴 */
		cQ->rear = (cQ->rear+1)%MAX_QUEUE_SIZE;
		/* 업데이트된 rear가 가리키는 곳 원형 큐의 위치에 item 원소를 삽입 */
		cQ->queue[cQ->rear] = item;
	}
}
/* f7.입력받은 원소를 원형 큐에서 삭제, item에 업데이트 해줌 */
void deQueue(QueueType *cQ, element *item)
{
	/* 큐가 empty일 경우(isEmpty가 1을 리턴, 조건문이 참이 됨), 더이상의 삭제가 불가하므로 */
	if(isEmpty(cQ))
	/* 바로 return */
	return;
	/* 그렇지 않다면, 원소 삭제를 진행 */
	else{
		/* front를 1 증가시킴 */
		cQ->front = (cQ->front+1)%MAX_QUEUE_SIZE;
		/* front가 가리키는 곳 원형 큐의 위치에 원소를 삭제해 꺼낸 후 입력받은 item의 주소로 업데이트(호출 한 위치에 값을 변경/업데이트 해줌) */
		*item = cQ->queue[cQ->front];
		return;
	}
}
/* f8.현재 원형 큐의 원소 배치 상태를 출력 */
void printQ(QueueType *cQ)
{
	int i, first, last;
	/* front부터 rear사이 범위의 원소를 출력하기 위해 first, last를 각각 front+1, rear+1로 지정 */
	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");
	/* first부터 last까지 queue[]의 원소를 차례로 출력 */
	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;
	}
	printf(" ]\n");
}
/* f9.현재 원형 큐의 구성상황(rear와 front 배치상황 등)을 출력 */
/* front의 경우 : 맨 처음 값이 할당되어있는 칸 -1을 가리킴(삭제 진행) */
/* rear의 경우 : 마지막 값이 할당되어있는 칸을 가리킴(삽입 진행) */
void debugQ(QueueType *cQ)
{
	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);
	}
	/* cQ의 rear와 front를 출력 */
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}