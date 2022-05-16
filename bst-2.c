/* Binary Search Tree #2 */

#include <stdio.h>
#include <stdlib.h>
/* 트리의 노드가 될 구조체 선언 */
typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;
/* stack역할을 할 배열설정, size는 20으로 define, stack top은 '-1'로 설정한다 */
#define MAX_STACK_SIZE	20
Node* stack[MAX_STACK_SIZE];
int top = -1;
/* stack관련 함수 정의 */
Node* pop();
void push(Node* aNode);
/* queue역할을 할 배열설정, size는 20으로 define, queue front, rear는 모두 '-1'로 초기 설정한다 */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;
/* queue관련 함수 정의 */
Node* deQueue();
void enQueue(Node* aNode);
/* bst 초기화 함수! 이중포인터 사용으로 실제 호출한 부분을 변경할 수 있음! */
int initializeBST(Node** h);
/* 사용자 정의 함수 */
void recursiveInorder(Node* ptr);	  /* 1. 재귀 전위 순회 - recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* 2. 비재귀 전위 순회 - iterative inorder traversal */
void levelOrder(Node* ptr);	          /* 3. 레벨 순서 순회 - level order traversal */
int insert(Node* head, int key);      /* 4. 노드 삽입! - insert a node to the tree */
int deleteNode(Node* head, int key);  /* 5. 노드 삭제! - delete the node for the key */
int freeBST(Node* head); 			  /* 6. 노드에 할당된 메모리 해제 */
void printStack();

int main()
{
	char command;			/* 사용자 정의 명령 */
	int key;				/* 함수 호출 시 사용할 사용자 입력 key 값 */
	Node* head = NULL;		/* 초기 헤드 NULL */
	printf("[----- [풍혜림]  [2019020028] -----]\n");
	/* 명령 선택 페이지 출력 */
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");
		/* 사용자 정의 명령 입력에 따라 분기 */
		printf("Command = ");
		scanf(" %c", &command);
		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;
		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;
		case 'l': case 'L':
			levelOrder(head->left);
			break;
		case 'p': case 'P':
			printStack();
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	}while(command != 'q' && command != 'Q');
	return 1;
}
/* bst 초기화 함수! 이중포인터 사용으로 실제 호출한 부분을 변경할 수 있음! */
int initializeBST(Node** h) {
	/* 트리에 노드가 있을 경우 freeBST함수를 호출해 모든 노드를 해제함! */
	if(*h != NULL)
		freeBST(*h);

	/* 새로운 헤드 노드(리턴용) 만듦 */
	*h = (Node*)malloc(sizeof(Node));
	/* 루트노드로! */
	(*h)->left = NULL;
	(*h)->right = *h;
	(*h)->key = -9999;
	/* 스택 탑과 큐의 리어 프론트 모두 초기화 후 리턴! */
	top = -1;
	front = rear = -1;
	return 1;
}
/* 1. 재귀 전위 순회 - recursive inorder traversal */
void recursiveInorder(Node* ptr)
{
	/* ptr이 참인 동안! recursiveInorder을 호출해 재귀 순회 진행! */
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}
/* 2. 비재귀 전위 순회 - iterative inorder traversal */
void iterativeInorder(Node* node)
{
	/* 무한 루프를 돌면서 노드의 좌측 */
	for(;;)
	{
		/* node가 참일 동안, node 좌측으로 이동하며 push */
		for(; node; node = node->left)
			push(node);
		node = pop();
		/* 노드가 NULL이 되면 루프 중지! */
		if(!node) break;
		printf(" [%d] ", node->key);
		/* 노드의 우측노드로 이동! */
		node = node->right;
	}
}
/* 3. 레벨 순서 순회 - level order traversal */
void levelOrder(Node* ptr)
{
	// int front = rear = -1;

	if(!ptr) return; /* empty tree */

	enQueue(ptr);

	for(;;)
	{
		ptr = deQueue();
		if(ptr) {
			printf(" [%d] ", ptr->key);

			if(ptr->left)
				enQueue(ptr->left);
			if(ptr->right)
				enQueue(ptr->right);
		}
		else
			break;

	}

}
/* 4. 노드 삽입! - insert a node to the tree */
int insert(Node* head, int key)
{
	/* 삽입할 노드를 선언해 만들어 줌 */
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;
	/* 헤더의 다음노드가 NULL이면 헤더에 바로 삽입노드를 연결해주고 리턴! */
	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}
	/* 헤더 left(루트노드를) ptr에 할당! */
	Node* ptr = head->left;
	/* ptr의 전노드를 기록해둘 부모 노드 선언 */
	Node* parentNode = NULL;
	while(ptr != NULL) {
		/* 키에 해당하는 노드가 있다면! 1을 리턴! */
		if(ptr->key == key) return 1;
		/* 부모노드에 ptr의 전노드를 할당해주고 ptr을 변화시킴으로써 ptr을 추적하도록 함! */
		parentNode = ptr;
		/* ptr의 키가 key보다 작으면 ptr의 우측으로, 크면 ptr의 좌측으로! 이동하며 탐색 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}
	/* 위치를 정한 뒤 삽입 노드와의 링크를 정리해주고 리턴! */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}
/* 5. 노드 삭제! - delete the node for the key */
int deleteNode(Node* head, int key)
{
	/* 헤더가 널이라면 트리가 존재하지 않으므로 삭제항목이 없음을 고지! */
	if (head == NULL) {
		printf("\n삭제할 항목이 존재하지 않습니다!\n");
		return -1;
	}
	/* 헤더의 다음이 NULL일 경우, 헤더 이외 삭제가능 노드가 존재하지 않음! */
	if (head->left == NULL) {
		printf("\n삭제할 항목이 존재하지 않습니다!\n");
		return -1;
	}
	/* head->left가 루트노드이므로 전진시킬 노드를 설정해, 초기 루트로 지정 */
	Node* root = head->left;
	/* 부모노드는 NULL로, ptr을 추적하고 ptr을 기본 root로 설정 */
	Node* parent = NULL;
	Node* ptr = root;
	/* ptr이 널이 아니고, ptr의 key가 입력된 key가 같지 않으면 탐색을 계속함 */
	while((ptr != NULL)&&(ptr->key != key)) {
		if(ptr->key != key) {
			/* ptr의 경로를 parent에 저장하고 ptr 전진! */
			parent = ptr;
			/* ptr의 키값과 입력 key를 비교해 좌, 우로 이동! */
			if(ptr->key > key)
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}
	}
	/* 반복문이 종료될 경우는 key 값 탐색에 실패한 경우! 트리에 key값이 존재하지 않음 */
	if(ptr == NULL)
	{
		printf("key[%d]에 해당하는 노드가 존재하지 않습니다!\n ", key);
		return -1;
	}
	/* case 1: 삭제노드가 말단노드(leaf node)일 경우 */
	if(ptr->left == NULL && ptr->right == NULL)
	{
		if(parent != NULL) { 
			/* 부모노드가 존재할 경우! 부모 노드의 link를 정리해줌! */
			if(parent->left == ptr)
				parent->left = NULL;
			else
				parent->right = NULL;
		} 
		else {
			/* 부모노드가 존재하지 않는다는 것은! 루트의 바로 하단 노드임! */
			head->left = NULL;
		}
		/* 링크 정리후 ptr을 해제해 최종 삭제! */
		free(ptr);
		return 1;
	}

	/* case 2: 삭제할 노드가 자식을 하나 가지고 있을 경우 */
	if ((ptr->left == NULL || ptr->right == NULL))
	{
		Node* child;
		if (ptr->left != NULL)
			child = ptr->left;
		else
			child = ptr->right;

		if(parent != NULL)
		{
			if(parent->left == ptr)
				parent->left = child;
			else
				parent->right = child;
		}
		/* 부모노드가 널인 경우, 삭제될 노드가 루트이므로.. 삭제 후 루트의 자식이 루트가 되어야 함! */
		else {
			root = child;
		}
		free(ptr);
		return 1;
	}

	/* case 3: 삭제 노드가 두개 이상의 자식을 가질 경우 */
	/* 좌측 서브트리의 가장 큰 자손 노드를 찾거나 */ 
	/* 우측 서브트리의 가장 작은 자손 노드를 찾는다! -> 우리의 픽! */
	/* ptr의 우측 노드로 비교 대상이 될 후보 선언! */
	Node* candidate;
	parent = ptr;
	candidate = ptr->right;
	/* 가장 작은 노드는 우측 서브트리의 가장 왼편에 있는 노드! 따라서 후보의 좌측노드가 NULL(말단)이 될 때까지 반복문 진행 */
	while(candidate->left != NULL)
	{
		parent = candidate;
		candidate = candidate->left;
	}
	/* 후보 노드의 우측 노드는 삭제되어야할 노드이다!(**주의! 후보노드의 좌측은 NULL인 상황) */
	if (parent->right == candidate)
		parent->right = candidate->right;
	else
		parent->left = candidate->right;
	/* ptr의 삭제 대신에 후보의 key 값을 ptr의 키값과 바꾼 뒤 후보 노드를 삭제할 수 도 있다! */
	ptr->key = candidate->key;
	free(candidate);
	return 1;
}
/* freeBST에 호출될 freeNode 선언! */
void freeNode(Node* ptr)
{
	/* ptr이 NULL아닌 참 일경우(노드가 있음!) ptr left, right 해제 후 ptr 해제! */
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}
/* 6. 노드에 할당된 메모리 해제 */
int freeBST(Node* head)
{
	/* head의 다음이 head 일 경우, head노드 하나만 존재하므로 헤드 해제 후 리턴 */
	if(head->left == head)
	{
		free(head);
		return 1;
	}
	/* 아니라면, head외에 최소 1개 노드가 존재하므로 p를 설정해 차례로 헤제 후 헤드 헤제! 리턴 */
	Node* p = head->left;
	freeNode(p);
	free(head);
	return 1;
}
/* stack 관련 함수 정의 */
Node* pop()
{
	/* 만약 top이 0이하이면, 스택이 비었으므로 return NULL */
	if (top < 0) return NULL;
	/* top이 가리키는 stack 위치를 리턴하고 top을 1 감소 */
	return stack[top--];
}
void push(Node* aNode)
{
	/* top을 한칸 증가, 증가된 top이 가리키는 위치에 노드 삽입 */
	stack[++top] = aNode;
}
/* 스택 현황 출력 */
void printStack()
{
	/* i가 top보다 작은동안 반복문을 실시해 출력 후, stack을 다음으로 이동 반복! */
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top)
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}
/* queue 관련 함수 정의 */
Node* deQueue()
{
	/* 만약에 front==rear가 같다면, 큐가 비었으므로 dequeue 불가능! */
	if (front == rear) {
		//printf("\n큐가 비어 삭제가능 항목이 없습니다.\n" );
		return NULL;
	}
	/* 그렇지 않다면, front를 한 칸 전진시키고, 전진시킨 front 위치 queue 리턴 */
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];
}
void enQueue(Node* aNode)
{
	/* rear를 한칸 전진! */
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	/* rear를 한칸 전진시켰을때 front와 같아진다면, 큐가 꽉찬 상태로 항목추가가 불가능! */
	if (front == rear) {
		//printf("\n큐가 꽉 차 항목 추가가 불가능합니다.\n");
		return;
	}
	/* 그렇지 않다면, queue배열에서 rear위치에 노드를 삽입! */
	queue[rear] = aNode;
}