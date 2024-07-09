#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 10
#define MAX_QUEUE MAX_VERTEX+1
/* 정점 뱡문여부 확인용 배열 */
int check[MAX_VERTEX];
/* 그래프 구현에 필요한 구조체 선언 */
typedef struct LIST {
   int vx;
   struct LIST* link;
}List;
typedef struct GRAPH {
   int n;
   List* adj_list[MAX_VERTEX];
}Graph;
/* 사용자 정의 함수! */
Graph* Init_Graph(void);
void Add_Vertex(Graph* g);
void Add_Edge(Graph* g, int u, int v);
void DFS(Graph *g, int n);
void Depth_First_Search(Graph* g, int n);
void BFS(Graph *g, int n);
void Breath_First_Search(Graph* g, int n);
void Add_Queue(int n);
int Delete_Queue(void);
void print_graph(Graph* g);
/* bfs 탐색용 큐 선언 */
int front   = 0;
int rear    = 0;
int queue[MAX_QUEUE];
int main(void) {
	char command = '\0';
	int tail = 0, head = 0;
	int key = 0;
  
	printf("[----- [풍혜림]  [2019020028] -----]");
    printf("\n");
    Graph* g = Init_Graph();
    do{
        printf("----------------------------------------------------------------\n");
        printf("                          Graph Searches                        \n");
        printf("----------------------------------------------------------------\n");
        printf("  Initialize Graph = z                                          \n");
        printf("  Insert Vertex = v               Insert Edge = e               \n");
        printf("  Depth First Search = d          Breath First Search = b       \n");
        printf("  Print Graph = p                 Quit = q                      \n");
        printf("----------------------------------------------------------------\n");
        
        printf("Command : ");
        scanf(" %c", &command);
        switch(command)
        {
        case 'z': case 'Z':
            g = Init_Graph();
            break;
        case 'v': case 'V':
            Add_Vertex(g);
            break;
        case 'e': case 'E':
            scanf("%d %d", &tail, &head);
			Add_Edge(g, tail, head);
			break;
        case 'd': case 'D':
            scanf("%d", &key);
            DFS(g, key);
            break;
        case 'b': case 'B':
            scanf("%d", &key);
            BFS(g, key);
            break;
        case 'p': case 'P':
            print_graph(g);
            break;
        case 'q': case 'Q':
            break;
        default:
            printf("input is wrong, check your command please!\n");
        }
    } while (command!='q' && command!='Q');
    return 0;
}

Graph* Init_Graph(void){
	//새로 초기화해서 리턴해줄 g 선언
    Graph* g = (Graph*)malloc(sizeof(Graph));
	//정점 개수 0으로 초기화, adj_list 모두 초기화!
    g->n = 0;
    for(int i = 0; i < MAX_VERTEX; i++)
        g->adj_list[i] = NULL;
	//초기화 된 그래프 리턴
    return g;
}
 
void Add_Vertex(Graph* g){
	//vertex를 추가한 뒤 공간 연결!
    g->adj_list[g->n] = (List*)malloc(sizeof(List));
	//초기화해둔 상태
    g->adj_list[g->n]->vx = -1;
    g->adj_list[g->n]->link = NULL;
	//정점 수 +1
    g->n++;
}

void Add_Edge(Graph* g, int u, int v){
	//입력이 정점 개수보다 클 경우 인덱스를 벗어났음으로 오류 출력
    if(u >= g->n || v >= g->n){
        printf("인덱스 범위를 벗어나 연결할 수 없습니다!\n");
    }
	//인덱스 범위내에 있을 경우 u,v에 해당하는 노드를 선언해 양쪽으로 연결!
    else{
        List* tmp_u = (List*)malloc(sizeof(List));
        List* tmp_v = (List*)malloc(sizeof(List)); 
        tmp_u->vx = u;
        tmp_v->vx = v;      
        tmp_v->link = g->adj_list[u]->link;
        g->adj_list[u]->link = tmp_v;
        tmp_u->link = g->adj_list[v]->link;
        g->adj_list[v]->link = tmp_u;
    }
}

void DFS(Graph *g, int n){
	//방문 점검 배열 초기화!
    for(int i = 0; i < MAX_VERTEX; i++){
        check[i] = 0;
    }
	//DFS 호출!
    Depth_First_Search(g, n);
    printf("\n");
}

void Depth_First_Search(Graph* g, int n){
	//방문하지 않은 노드라면!
    if(check[n] == 0){
        List* cur;
        List* tmp;
		//노드 전진!
        cur =  g->adj_list[n]->link;
		//프린트 후 n을 방문 처리
        printf("%2d  ", n);
       check[n] = 1;
	   //cur을 전진시키면서 NULL이 될때까지, 재귀 호출!
       while(cur != NULL){
            tmp = cur->link;          
            if(check[cur->vx] == 0)
                Depth_First_Search(g, cur->vx);          
            cur = tmp;
        }
    }
}

void BFS(Graph *g, int n){
	//방문 배열 초기화, 큐 초기화
    for(int i = 0; i < MAX_VERTEX; i++){
        check[i] = 0;
    }
	front   = 0;
    rear    = 0;
	//BFS 호출!
	Breath_First_Search(g, n);
    printf("\n");
}

void Breath_First_Search(Graph* g, int n){
    List* cur;
    List* tmp;
    int queue_out;
	//전진 시킬 노드 선언!
    cur = g->adj_list[n]->link;
	//미방문 노드일 경우! 프린트 후 방문 처리
    if(check[n] == 0){
        printf("%2d  ", n);
        check[n] = 1;
    }
	//cur 노드가 NULL이지 않는 동안! 큐에 add
    while(cur != NULL){
        tmp = cur->link;
        if(check[cur->vx] == 0){
            printf("%2d  ", cur->vx);
            check[cur->vx] = 1;
            Add_Queue(cur->vx);
        }
        cur = tmp;
    }
	//큐에서 delete!
	queue_out = Delete_Queue();
	//큐가 빌때까지 재귀 호출!
    while(queue_out != -1){
        Breath_First_Search(g, queue_out);
        queue_out = Delete_Queue();
    }
}

/* bfs용 큐 사용자 정의 함수 선언 */
/* 각각 큐의 empty, full을 판단한 뒤 enque, deque 진행! */
void Add_Queue(int n){
    if((rear+1)%MAX_QUEUE == front){
        printf("큐가 꽉 찼습니다!\n");
		return;
    }
    else{
        rear = (rear+1)%MAX_QUEUE;
		//1번부터 찬다!
        queue[rear] = n; 
    }
}
int Delete_Queue(void){
    int tmp = -1;
    if(front == rear){
		//printf("큐가 비었습니다!\n");
		return -1;
   }
    else{
        front = (front+1)%MAX_QUEUE;
        tmp = queue[front];
    }
    return tmp;
}

void print_graph(Graph* g){
	//반복문을 돌면서 정점 n개 만큼 연결된 관계를 표시!
    for(int i=0; i<(g->n); i++){
		//이동 시켜줄 임시 노드 생성
        List* ptr = g->adj_list[i];
        printf("\n vertex [%d] : ", i);
		//맨처음 초기화해 둔 -1은 건너뛰고 출력 하기 위함!
		ptr=ptr->link;
		//각 헤드에 연결된 각 노드들을 모두 출력
        while(ptr) {
            printf(" -> %d", ptr->vx);
            ptr=ptr->link;
        }
        printf("\n");
    }
}