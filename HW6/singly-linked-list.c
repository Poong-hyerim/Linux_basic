/* singly linked list */
#include<stdio.h>
#include<stdlib.h>

/* Node형의 listNode 선언 */
typedef struct Node {
	int key;
	struct Node* link;
} listNode;
/* Head형의 headNode 선언 */
typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */
headNode* initialize(headNode* h);		//f1.singly_linked_list를 초기화(first를 NULL로 초기화)
int freeList(headNode* h);				//f2.headNode포인터 h부터 이어지는 리스트 모두 해제
int insertFirst(headNode* h, int key);	//f3.맨앞에 노드를 삽입해주고, 헤더를 맨앞 노드로 변경
int insertNode(headNode* h, int key);	//f4.리스트를 검색, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
int insertLast(headNode* h, int key);	//f5.입력받은 key 값이 list 맨 마지막에 삽입 될 경우
int deleteFirst(headNode* h);			//f6.맨 첫 노드를 삭제하고 헤더를 그다음으로 변경
int deleteNode(headNode* h, int key);	//f7. 중간에 key 값인 노드를 삭제
int deleteLast(headNode* h);			//f8. 리스트의 맨 마지막 노드를 삭제
int invertList(headNode* h);			//f9. 리스트의 순서를 역순으로 변경
void printList(headNode* h);			//f10. 리스트를 출력

int main()
{
	printf("[----- [풍혜림]  [2019020028] -----]\n");
	char command;			 //사용자 명령을 저장할 command 변수 선언
	int key;				 //key
	headNode* headnode=NULL; //headNode형 포인터 headNode를 선언 후, 포인터를 NULL로 초기화

	do{
		/* 사용자 선택 메뉴인 Singly Likned List를 출력해 사용자가 명령을 선택하도록 함 */
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");
		printf("Command = ");	//명령 입력 안내 :
		scanf(" %c", &command); //사용자 명령 입력 후 command로 저장
		/* command에 따라 분기해서 함수를 실행 */
		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}
//f1.singly_linked_list를 초기화(first를 NULL로 초기화)
//(in: headNode형 포인터 h/out: headNode형 리턴)
headNode* initialize(headNode* h) {
	/* headNode가 NULL이 아니면(어떤 다른 Node를 가리키고 있음 즉, 리스트에 노드가 있는 상황), freeList를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);
	/* headNode형 포인터 temp를 선언 후 headNode의 사이즈만큼 메모리를 할당 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL; //temp의 first를 NULL로 할당(headNode형 포인터 temp는 첫번째 first를 NULL로 연결해 초기화 상태가 됨)
	return temp;		//초기화된 headNode 포인터 temp를 리턴
}
//f2.headNode포인터 h부터 이어지는 리스트 모두 해제
//(in: headNode형 포인터 h/out: int형 리턴)
int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제 + headNode도 해제되어야 함. */
	listNode* p = h->first;  //listNode형 포인터 p에 입력받은 h의 first값을 할당함
	listNode* prev = NULL;	 //listNode형 포인터 prev를 NULL로 초기화
	/* p를 prev로 복사해둔 후, p는 한칸 전진시키고 p가 복사된 prev를 해제-(p는 전진역할, prev로 할당) */
	while(p != NULL) {		  
		prev = p;			 //listNode형 포인터 prev에 p를 다시 복사해둠(p값을 prev로 옮김)
		p = p->link;		 //p를 link로 연결된 다음 노드로 한칸 이동시킴(p->link를 p에 할당)
		free(prev);			 //prev(p를 복사)를 해제시킴
	}
	free(h);				 //각노드를 모두 해제하고 head노드인 h를 해제시켜 최종적으로 linked_list를 free
	return 0;
}
//f3.맨앞에 노드를 삽입해주고, 헤더를 맨앞 노드로 변경
//(in: headNode형 포인터 h, int형 변수 key/out: int형 리턴)
int insertFirst(headNode* h, int key) {
	/* listNode형 포인터 node를 선언, listNode(구조체) 크기만큼 메모리를 할당 */
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;		//(*node).key에다가 입력받은 key를 할당
	node->link = h->first;	//(*node).link에다가 (*h).first를 연결
	h->first = node;		//(*h).first에다가 node를 연결
	return 0;
}
//f4.리스트를 검색, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
//(in: headNode형 포인터 h, int형 변수 key/out: int형 리턴)
int insertNode(headNode* h, int key) {
	/* 입력받은 key값을 포함할 노드 생성 */
	listNode* in_node = (listNode*)malloc(sizeof(listNode));
	in_node->key = key;	 	 //(*node).key에 key를 할당
	in_node->link=NULL;		 //(*node).link는 NULL로 일단 설정
	/* 1. 만약 insert해야하는 입력 key노드가 맨 앞에 삽입 되야 할 경우(list is empty) */
	if(h->first==NULL){
		h->first = in_node;
		return 0;
	}
	/* 2. 그렇지 않다면 list와 비교를 통해 삽입 */
	/* 입력받은 key값과 비교해줄 노드를 search로, search의 한 칸 뒤를 prev로 설정(큰 값의 바로 앞에 삽입위함) */
	listNode* search = h->first; //key 값과 계속해 비교해 나갈 search 선언
	listNode* prev = h->first;   //search노드의 한 칸 전 노드를 가리킬 prev 선언
	/* search와 비교하고 삽입은 key보다 큰값이 나오는 노드 바로 앞이므로 search와 prev 사이에 진행 */
	while(search!=NULL){ 
		if(search->key >= key){
			if(search == h->first) {
				h->first = in_node;
				in_node->link = search;	
			}
			else{
				in_node->link = search;
				prev->link = in_node;
			}
			return 0;
		}
		prev = search;			//prev에 현재 search위치를 할당 후
		search = search->link;  //search는 한 칸 이동(prev는 search 한 칸 뒤를 가리키게 됨)
	}
	/* 3. while문에서도 검출이 안된 경우(*in_node).key가 리스트 값중 가장 큼! */
	prev->link = in_node;
	return 0;
}
//f5.입력받은 key 값이 list 맨 마지막에 삽입 될 경우
//(in: headNode형 포인터 h, int형 변수 key/out: int형 리턴)
int insertLast(headNode* h, int key) {
	/* insert Node */
	listNode* in_node = (listNode*)malloc(sizeof(listNode));
	in_node->key = key;	 	 //(*node).key에 key를 할당
	in_node->link = NULL;	 //(*node).link를 NULL로 일단 설정
	/* list가 빈 리스트일 경우에는 첫 노드로 입력 노드를 삽입 후 종료 */
	if(h->first == NULL){
		h->first = in_node;
		return 0;
	}
	/* compare Node */
	//(*last_node)에 h->first인 첫번째 노드를 할당
	listNode* last_node = h->first;
	while(last_node->link!= NULL){
		last_node = last_node->link;
	}
	last_node->link = in_node;
	return 0;
}
//f6.맨 첫 노드를 삭제하고 헤더를 그다음으로 변경
//(in: headNode형 포인터 h/out: int형 리턴)
int deleteFirst(headNode* h) {
	if(h->first == NULL){
		printf("리스트가 비어 삭제할 수 있는 항목이 없습니다.");
		return 0;
	}
	listNode* node = h->first; //삭제할 첫번째 노드 지정
	h->first = node->link;     //두번째 노드로 헤더 바꿈
	free(node); 			   //첫번째 노드를 해제 시킴(삭제)
	return 0;
}
//f7. 중간에 key 값인 노드를 삭제
//(in: headNode형 포인터 h, int형 key/out: int형 리턴)
int deleteNode(headNode* h, int key) {
	/* 1. 리스트가 비어 삭제가 불가능한 경우  */
	if((h->first)==NULL){
		printf("리스트가 비어 삭제할 수 있는 항목이 없습니다.\n");
		return 0;
	}
	/* 2. 그렇지 않다면 list와 비교를 통해 key노드를 찾아내 삭제 */
	listNode* search = h->first;  //삭제할 노드 탐색을 위해 search 선언
	listNode* prev = NULL; 		  //삭제된 노드의 이전노드와 삭제 후 노드를 연결하기 위해 prev 선언
	/* **search->link가 NULL이면 search가 마지막 노드인 상황! */
	while(search!=NULL){
		/* search의 key 값과 key값이 일치하는 점을 찾아 삭제 */
		if(search->key==key){
			//1.만약 delete해야하는 입력 key노드가 맨 앞인 경우
			if(search==h->first)
				h->first=search->link;
			//2.최소 1번 노드 이후 또는 마지막 노드를 삭제하는 경우
			else
				prev->link = search->link;
			free(search);
			return 0;
		}
		prev = search;
		search = search->link;
	}
	/* 3. while문에서도 검출이 안된 경우, key 값이 list에 존재 하지 않음 */
	printf("key값을 찾을 수 없습니다 = %d\n", key);
	return 0;
}
//f8. 리스트의 맨 마지막 노드를 삭제
//(in: headNode형 포인터 h/out: int형 리턴)
int deleteLast(headNode* h) {
	if(h->first == NULL){
		printf("리스트가 비어 삭제할 수 있는 항목이 없습니다.\n");
		return 0;
	}
	listNode* search = h->first; 	//비교와 삭제를 위해 쓰일 노드 지정
	listNode* prev = NULL; 			//search 한칸 전 노드 지정
	/* list에 노드가 하나라서 삭제 후 list empty 상태가 되는 경우 */
	if(search->link==NULL){
		h->first = NULL;
		free(search);
		return 0;
	}
	/* 아니라면, 리스트의 마지막 노드로 이동해 삭제 */
	while(search->link!=NULL){
		prev = search;
		search=search->link;
	}
	/* 맨 뒤 노드는 search, 뒤에서 두번째 노드는 prev이므로 prev를 마지막 노드로 만들어주고, search 해제(삭제) */
	prev->link = NULL;
	free(search);
	return 0;
}
//f9. 리스트의 순서를 역순으로 변경
//(in: headNode형 포인터 h/out: int형 리턴)
int invertList(headNode* h) {
	/* 만약 리스트가 비어있다면, 역전시킬 수 없음 */
	if(h->first == NULL){
		printf("리스트가 비어 역전시킬 수 없습니다\n");
		return 0;
	}
	/* 역전시킬 노드와 해당 노드 앞, 뒤를 가리킬 포인터 세개 선언 */
	listNode* front = h->first;	 //middle 한 칸 앞
	listNode* middle = NULL; 	 //역전시킬 노드가 위치하는 middle
	listNode* trail = NULL;		 //middle 한 칸 뒤

	while(front!=NULL){
		trail = middle;		  //middle의 위치를 trail에 업데이트(뒤)
		middle = front;		  //역전시킬 노드를 middle에 업데이트(중간)
		front = front->link;  //역전시킨 후에 기존 리스트에서 방금 역전된 노드의 다음노드를 표시하기 위해(이동해야할 방향성 보존) 한 칸 이동
		middle->link = trail; //노드를 반대로 역전 시킴
	}
	h->first = middle;		  //맨 마지막노드에 도착한 middle에 first를 연결
	return 0;
}
//f10. 리스트를 출력
void printList(headNode* h) {
	int i = 0;
	listNode* p;
	/* 프린트 모드임을 안내 */
	printf("\n---PRINT\n");
	/* h가 NULL일 경우 리스트에 출력할 노드가 없음 */
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}
	/* 포인터 p에 첫번째 노드를 할당 */
	p = h->first;
	/* 첫 번째 노드 부터 마지막 노드까지 출력 */
	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}
	/* 리스트의 노드 개수(반복문이 돌아간 횟수) 출력 */
	printf("  items = %d\n", i);
}