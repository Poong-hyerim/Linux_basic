/* Binary Search Tree #1 */

#include <stdio.h>
#include <stdlib.h>

/* 트리에 노드 형식을 구조체로 선언 */
typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);				/* f0.binary search tree를 초기화*/
/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  		/* f1.recursive하게 중위순회 - inorder traversal */
void preorderTraversal(Node* ptr);    		/* f2.recursive하게 전위순회 - preorder traversal */
void postorderTraversal(Node* ptr);	  		/* f3.recursive하게 후위순회 - postorder traversal */
int insert(Node* head, int key);  			/* f4.트리에 새 노드 삽입 */
int deleteLeafNode(Node* head, int key);  	/* f5.key에 해당하는 단말노드 삭제 */
Node* searchRecursive(Node* ptr, int key);  /* f6.recursive 방식으로 key에 해당하는 노드 탐색 */
Node* searchIterative(Node* head, int key); /* f7.iterative 방식으로 key에 해당하는 노드 탐색 */
int freeBST(Node* head); 					/* f8.트리에 해당된 메모리 해제 */

int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;
	do{
		printf("\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");
		/* 사용자 명령 입력 */
		printf("Command = ");
		scanf(" %c", &command);
		/* 명령에 따라 분기하며 각 함수를 호출 */
		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	}while(command != 'q' && command != 'Q');
	return 1;
}
/* f0.binary search tree를 초기화*/
int initializeBST(Node** h) {
	/* 헤더가 가리키는 곳이 널이 아니면(트리에 노드가 존재함), 남아있는 노드를 모두 free시킴으로써 노드를 삭제함 */
	if(*h != NULL)
		freeBST(*h);
	/* 새로이 헤더를 만들고, 트리를 초기화해둠 */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* 루트노드! */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}
/* f1.recursive하게 중위순회 - inorder traversal */
void inorderTraversal(Node* ptr)
{
	/* 입력된 노드가 NULL이 아니면, 재귀적으로(recursive) inorderTraversal을 호출! */
	if(ptr) {
		//ptr->left 좌측 노드로 이동!
		inorderTraversal(ptr->left);
		//(ptr의 좌측노드) key 값 출력
		printf(" [%d] ", ptr->key);
		//ptr->right 우측 노드로 이동!		
		inorderTraversal(ptr->right);	
	}
}
/* f2.recursive하게 전위순회 - preorder traversal */
void preorderTraversal(Node* ptr)
{
	/* 입력된 노드가 NULL이 아니면, 재귀적으로(recursive) preorderTraversal을 호출! */
	if(ptr) {
		//먼저 ptr의 key 값을 출력!
		printf(" [%d] ", ptr->key);
		//ptr의 좌측으로 이동해 preorderTraversal을 호출 값을 출력!
		preorderTraversal(ptr->left);
		//ptr의 우측으로 이동하며 preorderTraversal을 호출
		preorderTraversal(ptr->right);
	}
}
/* f3.recursive하게 후위순회 - postorder traversal */
void postorderTraversal(Node* ptr)
{
	/* 입력된 노드가 NULL이 아니면, 재귀적으로(recursive) postorderTraversal을 호출! */
	if(ptr) {
		//ptr의 좌측으로 이동해 호출
		postorderTraversal(ptr->left);
		//ptr의 우측으로 이동해 호출
		postorderTraversal(ptr->right);
		//key 값을 출력!
		printf(" [%d] ", ptr->key);
	}
}
/* f4.트리에 새 노드 삽입 */
int insert(Node* head, int key)
{
	//삽입할 새 노드 생성!
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;
	//1. 만약, head left가 NULL이라면 루트노드에 바로 연결!
	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* 임시노드를 ptr을 head의 left로 설정! */
	Node* ptr = head->left;
	/* 부모노드는 임시로 NULL 설정! ptr을 전진시키며 그 전 노드를 부모노드로 설정 */
	Node* parentNode = NULL;
	// ptr이 마지막에 다다를 때 까지(NULL아닌 동안 반복)!
	while(ptr != NULL) {
		/* key에 일치하는 노드가 있을 경우! 1을 리턴하고 종료 */
		if(ptr->key == key) return 1;
		// 부모노드에 ptr을 할당해두고, ptr을 이동시키면서 부모노드를 추정가능한 상태로 만듦
		parentNode = ptr;
		/* 만약, ptr의 key와 주어진 key값을 비교 */
		//노드의 키 >> input key 이면, 우측 subtree
		if(ptr->key < key)
			ptr = ptr->right;
		//노드의 키 << input key 이면, 좌측 subtree
		else
			ptr = ptr->left;
	}
	/* 뒤 따라오던 parentnode에 새로운 삽입노드를 연결! */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}
/* f5.key에 해당하는 단말노드 삭제 */
int deleteLeafNode(Node* head, int key)
{
	/* head가 NULL이면 트리 존재하지 않으므로, 삭제할 노드가 없음! */
	if (head == NULL) {
		printf("\n삭제할 항목이 존재하지 않습니다!\n");
		return -1;
	}
	/* 마찬가지로 삭제할 노드가 없음! */
	if (head->left == NULL) {
		printf("\n삭제할 항목이 존재하지 않습니다!\n");
		return -1;
	}
	//이동을 위한 ptr과, 부모노드 기록을 위한 parentnode 생성
	Node* ptr = head->left;
	Node* parentNode = head;
	while(ptr != NULL) {
		//만약에 ptr 노드의 key와 input key가 같으면!
		if(ptr->key == key) {
			if(ptr->left == NULL && ptr->right == NULL) {
				/* 부모노드가 루트인 경우! */
				if(parentNode == head)
					head->left = NULL;
				if(parentNode->left == ptr)
					parentNode->left = NULL;
				else
					parentNode->right = NULL;
				//임시노드 메모리 해제
				free(ptr);
			}
			else {
				printf("키 [%d]가 단말노드가 아닙니다.\n", ptr->key);
			}
			return 1;
		}
		//ptr노드 변경 전에 parentnode에 기록함
		parentNode = ptr;
		//ptr노드의 key 값이 input key 보다 작으면 오른쪽 subtree로,
		if(ptr->key < key)
			ptr = ptr->right;
		//아니면 왼쪽 subtree로
		else
			ptr = ptr->left;
	}
	printf("키에 해당하는 노드를 찾을 수 없습니다 : [%d]\n ", key);
	return 1;
}
/* f6.recursive 방식으로 key에 해당하는 노드 탐색 */
Node* searchRecursive(Node* ptr, int key)
{
	//ptr이 NULL일 경우 NULL을 리턴하고 곧 바로 종료
	if(ptr == NULL)
		return NULL;
	//ptr의 key가 input key보다 작으면 재귀호출로 ptr right을 동일 key값으로 다시 search
	if(ptr->key < key)
		ptr = searchRecursive(ptr->right, key);
	//ptr의 key가 input key보다 크면 재귀호출로 ptr left를 동일 key값으로 search
	else if(ptr->key > key)
		ptr = searchRecursive(ptr->left, key);

	/* if ptr의 key값이 input key와 동일하다면, 그대로 리턴!*/
	return ptr;
}
/* f7.iterative 방식으로 key에 해당하는 노드 탐색 */
Node* searchIterative(Node* head, int key)
{
	/* 루트노드를 임시로 지정 */
	Node* ptr = head->left;
	//ptr이 NULL이 아닐 때까지..!
	while(ptr != NULL)
	{
		//ptr의 키와 input 키가 같아지면 바로 ptr 리턴
		if(ptr->key == key)
			return ptr;
		//ptr의 키가 key보다 작으면 ptr의 우측으로 이동
		if(ptr->key < key) 
			ptr = ptr->right;
		//아니면 ptr을 좌측으로 이동!
		else
			ptr = ptr->left;
	}
	return NULL;
}
void freeNode(Node* ptr)
{

	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}
/* f8.트리에 해당된 메모리 해제 */
int freeBST(Node* head)
{
	if(head->left == head)
	{
		free(head);
		return 1;
	}
	Node* p = head->left;
	freeNode(p);
	free(head);
	return 1;
}