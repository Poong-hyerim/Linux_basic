/* doubly-linked-list.c - 양쪽으로 연결된 형태의 리스트 구현 */

#include<stdio.h>
#include<stdlib.h>
/* doubly-linked-list 노드 listNode 설정 */
typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;
/* head 노드 설정 */
typedef struct Head {
	struct Node* first;
}headNode;
/* 함수 리스트 */
int initialize(headNode** h);			/* f1.초기화 메뉴 */
int freeList(headNode* h);				/* f2.list를 해제(비움) */
int insertNode(headNode* h, int key);	/* f3.노드 삽입 */
int insertLast(headNode* h, int key);	/* f4.맨 끝에 노드 삽입 */
int insertFirst(headNode* h, int key);	/* f5.맨 앞에 노드 삽입 */
int deleteNode(headNode* h, int key);	/* f6.노드 삭제 */
int deleteLast(headNode* h);			/* f7.맨 끝에 노드 삭제 */
int deleteFirst(headNode* h);			/* f8.맨 앞에 노드 삭제 */
int invertList(headNode* h);			/* f9.역순으로 배열 */
void printList(headNode* h);			/* f10.현재 리스트 출력 */

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;
	/* 사용자 메뉴얼 */
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

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
/* f1.초기화 메뉴 */
int initialize(headNode** h) {
	/* 1. headNode가 NULL이 아니면(리스트가 채워져있는 상태), freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);
	/* 2. 새로 headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;
	return 1;
}
/* f2.list를 해제(비움)-listnode 해제 */
int freeList(headNode* h){
	/* 1.해제할 listnode를 지칭할 포인터 선언 */
	listNode* p = h->first;  //첫번째 노드를 p에 복사
	listNode* prev = NULL;   //노드를 NULL로 초기화
	/* 2.노드 p가 NULL이 아닌 동안(마지막 노드까지) 반복 */
	while(p != NULL) {
		prev = p;			 //이전 노드에 현재 p를 저장(p의 이전위치 저장)
		p = p->rlink;		 //p를 한칸 전진
		free(prev);			 //prev를 해제(노드 한개 해제!)
	}
	/* 3.head노드 해제 */
	free(h);
	return 0;
}
/* f3.노드 삽입-리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	/* 1. insert할 노드를 생성-key 내용 입력/rlink.link NULL 초기화 */
	listNode* insert_node = (listNode*)malloc(sizeof(listNode));
	insert_node->key = key;
	insert_node->llink = insert_node->rlink = NULL;
	/* 2. 만약 list가 빈 상태로, 삽입 노드가 첫 노드가 되는 경우 */
	if (h->first == NULL)
	{
		h->first = insert_node;
		return 0;
	}
	/* 3. 그렇지않으면, list에 기존 노드 존재하므로 삽입 위치를 탐색 */
	listNode* n = h->first;
	/* key를 기준으로 삽입위치 탐색 */
	while(n != NULL) {
		if(n->key >= key) {
			/* 3_1.첫 노드 앞쪽에 삽입 */
			if(n == h->first) {
				insertFirst(h, key);
			}
			/* 3_2.중간이거나 마지막에 삽입 */
			else { 
				insert_node->rlink = n;
				insert_node->llink = n->llink;
				n->llink->rlink = insert_node;
			}
			return 0;
		}
		n = n->rlink;
	}
	/* 4. 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}
/* f4.맨 끝에 노드 삽입-list에 key에 대한 노드하나를 추가 */
int insertLast(headNode* h, int key) {
	/* 1. insert할 노드를 생성-key 내용 입력/rlink.link NULL 초기화 */
	listNode* insert_node = (listNode*)malloc(sizeof(listNode));
	insert_node->key = key;
	insert_node->rlink = NULL;
	insert_node->llink = NULL;
	/* 2. 만약 list가 빈 상태로, 삽입 노드가 첫 노드가 되는 경우 */
	if (h->first == NULL)
	{
		h->first = insert_node;
		return 0;
	}
	/* 3. 맨 마지막 노드를 탐색 후 이동, 연결 */
	listNode* n = h->first;
	while(n->rlink != NULL) {
		n = n->rlink;
	}
	n->rlink = insert_node;
	insert_node->llink = n;
	return 0;
}
/* f5.맨 앞에 노드 삽입-list 처음에 key에 대한 노드하나를 추가 */
int insertFirst(headNode* h, int key) {
	/* 1. insert할 노드를 생성-key 내용 입력/rlink.link NULL 초기화 */
	listNode* insert_node = (listNode*)malloc(sizeof(listNode));
	insert_node->key = key;
	insert_node->rlink = insert_node->llink = NULL;
	/* 2. 만약 list가 빈 상태로, 삽입 노드가 첫 노드가 되는 경우 */
	if(h->first == NULL)
	{
		h->first = insert_node;
		return 1;
	}
	/* 3. 헤더를 llink에 원래 첫번째 노드 였던 것을 rlink로 연결 */
	insert_node->rlink = h->first;
	insert_node->llink = NULL;
	listNode *p = h->first;
	p->llink = insert_node;
	h->first = insert_node;
	return 0;
}
/* f6.노드 삭제-list에서 key에 대한 노드 삭제 */
int deleteNode(headNode* h, int key) {
	/* 1.빈 리스트일 경우 삭제할 항목이 없음을 안내 */
	if (h->first == NULL)
	{
		printf("리스트내에 삭제할 항목이 없습니다.\n");
		return 1;
	}
	/* 2.아니라면, 리스트내에 항목이 있으므로 key 값으로 위치를 찾아 삭제 */
	listNode* n = h->first;
	while(n != NULL) {
		if(n->key == key) {
			/* 2_1.첫 노드째 노드 인경우 */
			if(n == h->first) {
				deleteFirst(h);
			}
			/* 2_2.마지막 노드인 경우 */
			else if (n->rlink == NULL){
				deleteLast(h);
			}
			/* 2_3.중간인 경우 */
			else { 
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n);
			}
			return 1;
		}
		n = n->rlink;
	}
	/* 3.찾지 못 한경우 */
	printf("key 값에 해당하는 노드를 찾지 못했습니다. = %d\n", key);
	return 1;
}
/* f7.맨 끝에 노드 삭제-list의 마지막 노드 삭제 */
int deleteLast(headNode* h) {
	/* 1.빈 리스트일 경우 삭제할 항목이 없음을 안내 */
	if (h->first == NULL)
	{
		printf("리스트내에 삭제할 항목이 없습니다.\n");
		return 0;
	}
	/* 2.아니라면, 리스트내에 항목이 있으므로 key 값으로 위치를 찾아 삭제 */
	listNode* n = h->first;
	listNode* trail = NULL;
	/* 2_1.노드가 하나만 있는 경우 첫 노드이자 마지막 노드이므로 삭제 */
	if(n->rlink == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}
	/* 3.마지막 노드로 이동 */
	while(n->rlink != NULL) {
		trail = n;
		n = n->rlink;
	}
	/* 3_1.그 전노드를 NULL로 연결 후 마지막 노드를 삭제 */
	trail->rlink = NULL;
	free(n);
	return 0;
}
/* f8.맨 앞에 노드 삭제-list의 첫번째 노드 삭제 */
int deleteFirst(headNode* h) {
	/* 1.빈 리스트일 경우 삭제할 항목이 없음을 안내 */
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}
	/* 2.헤드가 가리키는 맨 첫 노드를 삭제 */
	listNode* n = h->first;
	h->first = n->rlink;
	free(n);
	return 0;
}
/* f9.역순으로 배열-리스트의 링크를 역순으로 재배치 */
int invertList(headNode* h) {
	/* 1.빈 리스트일 경우 역순으로 만들 항목이 없음을 안내 */
	if(h->first == NULL) {
		printf("역순으로 배치할 항목이 없습니다.\n");
		return 0;
	}
	/* 2.n, trail, middle을 선언하고 차례로 n을 middle 한 칸 후,  */
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;
	while(n != NULL){
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}
	/* 3.역전된 마지막 노드를 헤더가 가리키도록 변경 */
	h->first = middle;
	return 0;
}
/* f10.현재 리스트 출력 */
void printList(headNode* h) {
	int i = 0;
	listNode* p;
	printf("\n---PRINT\n");
	/* 1.출력할 항목이 없음을 표시 */
	if(h == NULL) {
		printf("출력할 항목이 존재하지 않습니다\n");
		return;
	}
	/* 2.순서대로 리스트의 항목을 출력 */
	p = h->first;
	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	/* 3.전체 항목 개수를 출력 */
	printf("  items = %d\n", i);
}