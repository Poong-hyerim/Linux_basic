/* hw12-sorting-hashing.c */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_ARRAY_SIZE 13					/* 배열의 최대 크기 : 13 */
#define MAX_HASH_TABLE_SIZE MAX_ARRAY_SIZE	/* 해쉬테이블의 최대 크기(=배열의 최대 크기) : 13 */
/* 배열관련 함수 - 초기화/해제/출력 함수 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);
/* 정렬 함수 */
int selectionSort(int *a);		
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
int quickSort(int *a, int n);	/* recursive function으로 구현 */
/* 해싱관련 함수 */
/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);
/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);
/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);

int main()
{
	printf("[-----  [풍혜림]  [2019020028]-----]");
	char command;			/* 사용자 선택 명령 저장 변수 */
	int *array = NULL;		/* 함수들이 실행될 배열 */
	int *hashtable = NULL;	/* 해싱에서 이용될 해시테이블 배열 */
	int key = -1;			/* key값 선언 후 초기화 */
	int index = -1;			/* index값 선언 후 초기화 */
	srand(time(NULL));		/* 배열값 할당용 난수 발생 시키기! */
	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");
		/* 사용자 명령 입력 */
		printf("Command = ");
		scanf(" %c", &command);
		/* 명령에 따라 사용자 정의 함수 호출&동작 */
		switch(command) {
		/* 배열의 주소를 입력받아(배열을 복사하는 것이 아닌 수정을 위해 주소로!) 초기화 후 출력 */
		case 'z': case 'Z':
			initialize(&array);
			break;
		/* array에 해당된 메모리들을 해제 */	
		case 'q': case 'Q':
			freeArray(array);
			break;
		/* 선택 정렬 호출! */
		case 's': case 'S':
			selectionSort(array);
			break;
		/* 삽입 정렬 호출! */
		case 'i': case 'I':
			insertionSort(array);
			break;
		/* 버블 정렬 호출! */
		case 'b': case 'B':
			bubbleSort(array);
			break;
		/* 쉘 정렬 호출! */
		case 'l': case 'L':
			shellSort(array);
			break;
		/* 퀵 정렬 호출! */
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);
			break;
		/* 해싱 호출! */
		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;
		/* 해시로 탐색! */
		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;
		/* 배열을 가리키는 포인터 array를 입력 받아 출력 */
		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	}while(command != 'q' && command != 'Q');
	return 1;
}
/* 이중포인터로 주소를 넘겨준다(call by reference)! */
int initialize(int** a)
{
	/* a가 빈 array가 아닌 경우 임시로 배열 칸들을 할당해 해제 하는 용도로 사용할 임시 temp 선언! */
	int *temp = NULL;
	/* array가 NULL인 경우 우선 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  
	} else
		temp = *a;
	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;
	return 0;
}
/* 할당된 메모리 해제!(메모리 누수 방지!) */
int freeArray(int *a)
{
	/* a가 NULL이 아닌 경우, a를 free! 해제함 */
	if(a != NULL)
		free(a);
	return 0;
}
/* 현재 배열상황을 출력! */
void printArray(int *a)
{
	/* a가 널인 경우에는 출력할 배열 요소가 없음 */
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	/* 아닌 경우 a의 요소를 MAX_ARRAY_SIZE만큼 반복하면서 출력(첫번째 for:인덱스 출력/두번째 for:인데스 해당하는 실제 배열 값 출력) */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}
/* 선택정렬 */
int selectionSort(int *a)
{
	int min;
	int minindex;
	int i, j;
	/* 정렬 전 array 원본 출력! */
	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a);
	/* 선택 정렬 실시! - 주어진 리스트에서 최솟값 탐색, 최솟값을 맨 앞 값과 교체 정렬이 이뤄지지 않은 나머지에 대해 반복수행 */
	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;	/* 최초에 minindex를 i로 설정 */
		min = a[i];		/* min값 역시 a[i]로 설정 */
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j]) 	/* min값보다 작은 배열 값이 있을 경우 */
			{
				/*min값을 그 값으로 바꿔줌!*/
				min = a[j];	
				minindex = j;
			}
		}
		/* 값 교체! */
		a[minindex] = a[i];
		a[i] = min;
	}
	/* 정렬 완료된 배열 재출력! */
	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}
/* 삽입정렬 */
int insertionSort(int *a)
{
	int i, j, t;
	/* 정렬 전 array 원본 출력! */
	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a);
	/* 삽입 정렬 실시! - 정렬되어있는 부분집합에 새로운 원소의 위치를 찾아 삽입(맨 처음 0번째는 정렬완료로 취급해 1번부터 시작) */
	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		/* 정렬되지 않은 원소들의 부분집합 중 첫번째 원소를 선언! */
		t = a[i];
		j = i;
		/* 반복문을 돌면서 삽입 위치를 탐색! */
		while (a[j-1] > t && j > 0)
		{
			a[j] = a[j-1];
			j--;
		}
		a[j] = t;
	}
	/* 정렬 완료된 배열 재출력! */
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}
/* 버블정렬 */
int bubbleSort(int *a)
{
	int i, j, t;
	/* 정렬 전 array 원본 출력! */
	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a);
	/* 버블정렬 - 인접한 두원소만을 비교, 순서를 정렬을 반복함! 2중 반복문을 실시! */
	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j])
			{	
				/* 앞이 뒤보다 크면 둘을 swap!-버블버블! */
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}
	/* 정렬 완료된 배열 재출력! */
	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}
/* 쉘정렬 */
int shellSort(int *a)
{
	int i, j, k, h, v;
	/* 정렬 전 array 원본 출력! */
	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");
	printArray(a);
	/* 쉘정렬 실시! - 삽입정렬의 보완책으로 h간격만큼 떨어진 레코드를 삽입 정렬함! */
	/* max사이즈의 h를 절반씩 감소시킴! */
	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				/* 임시로 j(i+h)번째 값과 인덱스를 할당 */
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	/* 정렬 완료된 배열 재출력! */
	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}
/* 퀵정렬 */
int quickSort(int *a, int n)
{
	int v, t;
	int i, j;
	/* 기준 값(피봇)을 중심으로 왼쪽 부분집합, 오른쪽 부분집합을 나눠서 정렬 */
	if (n > 1)
	{
		/* 맨마지막 항, 인덱스를 할당해줌! */
		v = a[n-1];
		i = -1;
		j = n - 1;
		while(1)
		{
			while(a[++i] < v); /* 기준값보다 작은 key 찾기! 좌-->우! */
			while(a[--j] > v); /* 기준값보다 큰 key 찾기! 우-->좌! */

			if (i >= j) break; /* 종료조건! */
			/* 아니면 swap! */
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;
		/* pivot 업데이트 후 재귀호출로 정렬 다시 반복 */
		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
	}
	return 0;
}
/* 해쉬코드를 리턴해주는 역할! */
int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}
/* 해싱 */
int hashing(int *a, int **ht)
{
	/* 해쉬테이블을 초기에 NULL설정 */
	int *hashtable = NULL;
	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		/* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
		*ht = hashtable;
	} else {
		/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
		hashtable = *ht;	
	}
	/* -1로 리셋하는 과정! 반복문 이용 */
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;
	/* -1로 리셋이 잘됐는지 출력해 확인도 가능함!
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/
	/* 키와 해쉬코드 인덱스를 모두 초기화! */
	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];					/* i에 해당하는 배열 값을 키로 할당 */
		hashcode = hashCode(key);	/* 키에해당하는 해쉬코드를 리턴받아 저장 */
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		/* 해시코드를 인덱스로한 해시테이블 값이 -1일 경우 키를 할당함! */
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
		}
		/* 해시코드를 인덱스로한 해시테이블 값이 -1아닌 경우 인덱스를 업데이트해 -1을 찾음! */
		else 	
		{
			index = hashcode;
			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;
		}
	}
	return 0;
}
/* 해쉬테이블과 인덱스를 활용한 서치! */
int search(int *ht, int key)
{
	/* 해쉬코드를 인덱스에 할당 */
	int index = hashCode(key);
	/* 키와 일치하는 해쉬테이블값을 찾으면 인덱스를 리턴! */
	if(ht[index] == key)
		return index;
	/* 아닐경우 인덱스를 업데이트 해준 뒤 최종적으로 리턴! */
	while(ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}