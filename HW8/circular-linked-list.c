/* doubly circular linked list */

#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);			/* f1.리스트를 초기화 */
int freeList(listNode* h);				/* f2.리스트의 각 노드들과 헤더를 해제 */
void printList(listNode* h);			/* f3.리스트의 현황을 출력 */
int insertLast(listNode* h, int key);	/* f4.리스트 말단에 노드를 삽입 */
int deleteLast(listNode* h);			/* f5.리스트 말단에서 노드를 삭제 */
int insertFirst(listNode* h, int key);  /* f6.리스트 맨앞에 노드를 삽입 */
int deleteFirst(listNode* h);			/* f7.리스트 맨앞에서 노드를 삭제 */
int invertList(listNode* h);			/* f8.리스트를 역순으로 배열 */
int insertNode(listNode* h, int key);	/* f9.리스트에 노드를 삽입 */
int deleteNode(listNode* h, int key);	/* f10.리스트에서 노드를 삭제 */

int main()
{
	printf("[----- [풍혜림] [2019020028] -----]\n");
	//사용자 명령 입력용, 삽입 또는 삭제를 위한 key, headNode 선언
	char command;
	int key;
	listNode* headnode=NULL;
	//사용자 메뉴얼 출력
	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");
		//사용자 메뉴 선택 (명령 입력)
		printf("Command = ");
		scanf(" %c", &command);
		//입력 명령에 따라 분기함
		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
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

/* f1.리스트를 초기화 */
int initialize(listNode** h) {
	//1. 헤드 h가 NULL이 아니면 이외 노드가 존재하므로 freeNode 함수를 호출해 노드에 할당된 메모리를 모두 해제
	if(*h != NULL)
		freeList(*h);
	//2. 헤드 h에 새로운 메모리를 할당해주고 초기화된 리스트를 리턴
	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* f2.리스트의 각 노드들과 헤더를 해제 */
int freeList(listNode* h){
	//1. 리스트가 비어있을 경우 h만 해제
	if(h->rlink==h){
		free(h);
		return 1;
	}
	//2. 리스트에 h이외의 다른 노드들도 있을 경우
	listNode* p=h->rlink;
	listNode* prev=NULL;
	while(p!=NULL&&p!=h){
		prev=p;
		p=p->rlink;
		free(prev);
	}
	free(h);
	return 0;
}

/* f3.리스트의 현황을 출력 */
void printList(listNode* h) {
	/* 각 노드의 key 값을 출력 */
	int i = 0;
	listNode* p;
	//1. 출력을 안내함
	printf("\n---PRINT\n");
	//2. h가 NULL일 경우 출력 가능한 노드가 없음을 표시 후 종료
	if(h == NULL) {
		printf("출력이 불가능합니다!\n");
		return;
	}
	//3. 그렇지 않으면(출력할 노드가 존재) p에 h의 다음 노드를 할당
	p = h->rlink;
	//4. p가 NULL이 되거나, p가 h가 되면 종료하는 조건으로 노드들을 차례로 출력
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);

	/* 리스트의 주소를 출력 */
	//1. 헤드 노드의 llink, rlink 출력
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);
	//2. 각 노드들의 key와 llink, rlink 출력
	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}
}

/* f4.리스트 말단에 노드를 삽입 */
int insertLast(listNode* h, int key) {
	//리스트가 존재하지 않을 경우는 바로 -1을 리턴하고 종료
	if(h==NULL) return -1;
	//1. 삽입해줄 노드를 선언
	listNode* insert = (listNode*)malloc(sizeof(listNode));
	insert->key = key;
	insert->rlink = NULL;
	insert->llink = NULL;
	//+ 편의상 원래의 말단 노드를 last로 선언
	listNode* last = h->llink;
	//2. 리스트가 비어 노드가 첫 노드로 삽입되는 경우
	if(h->rlink==h){
		h->rlink = insert;
		h->llink = insert;
		insert->rlink = h;
		insert->llink = h;
	}
	//3. 리스트에 이미 1개 이상의 노드가 있을 경우
	else{
		last->rlink = insert;
		insert->llink = last;
		h->llink = insert;
		insert->rlink = h;
	}
	return 1;
}

/* f5.리스트 말단에서 노드를 삭제 */
int deleteLast(listNode* h) {
	//리스트가 존재하지 않거나, 리스트가 빈 경우 삭제가능 항목이 없음을 안내
	if(h==NULL||h->rlink==h){
		printf("삭제가능한 항목이 존재하지 않습니다.\n");
		return 1;
	}
	//1. 삭제할 노드(말단 노드)와 삭제 후 말단노드가 될(말단의 전 노드)를 선언
	listNode* last = h->llink;
	listNode* llast = last->llink;
	//2. 삭제할 노드를 리스트에서 제외하고 링크를 재설정
	h->llink = llast;
	llast->rlink = h;
	//3. 삭제할 노드를 해제해 최종 삭제
	free(last);
	return 1;
}

/* f6.리스트 맨앞에 노드를 삽입 */
int insertFirst(listNode* h, int key) {
	//1. 삽입 노드를 선언
	listNode* insert = (listNode*)malloc(sizeof(listNode));
	insert->key = key;
	insert->rlink = NULL;
	insert->llink = NULL;
	//+ 기존의 맨 앞노드를 편의상 first로 선언
	listNode* first = h->rlink;
	//2. 링크를 정리
	insert->rlink = first;
	first->llink = insert;
	insert->llink = h;
	h->rlink = insert;
	return 1;
}

/* f7.리스트 맨앞에서 노드를 삭제 */
int deleteFirst(listNode* h) {
	//리스트가 존재하지 않거나 비었을 경우에는 삭제가능 노드가 없음을 안내
	if(h==NULL||h->rlink==h){
		printf("삭제가능한 노드가 존재하지 않습니다!\n");
		return 0;
	}
	//1. 삭제할 노드(맨 앞 노드)와 삭제 후 맨 앞노드가 되는 노드(h로부터 2번째 노드)를 선언
	listNode* first = h->rlink;
	listNode* ffirst = first->rlink;
	//2. 링크를 정리
	ffirst->llink = h;
	h->rlink = ffirst;
	//3. 삭제할 노드(맨 앞 노드인 first)를 해제 시켜 최종 삭제
	free(first);
	return 1;
}

/* f8.리스트를 역순으로 배열 */
int invertList(listNode* h) {
	//리스트가 존재하지 않거나 비었을 경우 역전시킬 항목이 없음을 안내
	if(h==NULL||h->rlink==h){
		printf("역순으로 배열할 항목이 존재하지 않습니다.\n");
		return 0;
	}
	//1.역전시킬 노드(middle)과 middle의 앞 뒤 위치를 기억할(n,trail)을 선언
	listNode* n=h->rlink;
	listNode* middle=h;
	listNode* trail=h;
	//2. 맨마지막에 바뀔 h링크를 먼저 홀드(h의 이전 노드가 h가 원래 다음노드로 가리키던 노드로 바뀜)
	h->llink = h->rlink;
	//3. middle의 다음 노드인 n이 NULL 또는 h와 같아지기 전까지 역전을 반복
	while(n!=NULL&&n!=h){
		trail = middle;
		middle = n;
		n = n->rlink;

		middle->rlink = trail;
		middle->llink = n;		
	}
	//4. 최종으로 역전 시킨 마자막 노드를 h의 다음 노드로 연결해줌
	h->rlink = middle;
	return 0;
}

/* f9.리스트에 노드를 삽입 */
int insertNode(listNode* h, int key) {
	// 리스트가 존재하지 않을 경우 삽입 불가능
	if(h==NULL)
		return -1;
	//1. 일단 삽입할 노드를 먼저 선언
	listNode* insert = (listNode*)malloc(sizeof(listNode));
	insert->key = key;
	insert->rlink = NULL;
	insert->llink = NULL;
	//2. 노드가 리스트의 첫 노드로 삽입되는 경우(insertFirst 함수 호출)
	if(h->rlink==h){
		insertFirst(h, key);
		return 1;
	}
	//3. 그렇지 않으면 이미 기존 노드가 있으므로 key 값으로 삽입할 위치를 탐색
	listNode* p = h->rlink;
	//3-1. key를 기준으로 위치 탐색 시작!
	while(p!=NULL&&p!=h){
		//3-2. 비교한 노드의 key 값이 주어진 key 보다 크므로 위치를 파악하고 삽입 
		if(p->key>=key){
			//3-3. 그 위치가 맨 앞(insertFirst)
			if(p==h->rlink){
				insertFirst(h, key);
			}
			//3-4. 아닐 경우는 리스트 중간이거나 마지막(연결 노드와 링크를 정리)
			else{
				insert->rlink = p;
				insert->llink = p->llink;
				p->llink->rlink = insert;
				p->llink = insert;
			}
			return 0;
		}
		p = p->rlink;
	}
	//4. 앞선 조건에 모두 걸리지 않으면 주어진 key가 모든 노드보다 크므로 맨 마지막에 노드를 새로 삽입(insertLast 함수 호출)
	insertLast(h, key);
	return 0;
}

/* f10.리스트에서 노드를 삭제 */
int deleteNode(listNode* h, int key) {
	// 리스트가 존재하지 않거나 비었을 경우 삭제 불가능
	if(h==NULL||h->rlink==h){
		printf("삭제가능 항목이 존재하지 않습니다!\n");
		return 0;
	}
	//1. 삭제할 노드를 탐색하기 위한 노드를 선언
	listNode* p = h->rlink;
	//2. key값과 일치하는 노드를 탐색
	while(p!=NULL&&p!=h){
		//2-1. key와 일치하는 노드를 발견했다면 노드의 위치 파악
		if(p->key==key){
			//2-2. 맨 첫번째 노드일 경우!(deleteFirst 호출)
			if(p==h->rlink)
				deleteFirst(h);
			//2-3. 그렇지 않을 경우 리스트 중간, 마지막에 노드일 경우!
			else{
				p->llink->rlink = p->rlink;
				p->rlink->llink = p->llink;
				free(p);
			}
			return 0;
		}
		p = p->rlink;
	}
	//3. 그렇지 않으면 리스트에 key와 일치하는 항목이 없음!
	printf("삭제하고자 하는 key에 해당하는 노드가 존재하지 않습니다 = %d\n", key);	
	return 0;
}