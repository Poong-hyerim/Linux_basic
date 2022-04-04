#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration : 함수 정의 */
int** create_matrix(int row, int col);                                     /* f1.row x col배열 생성 */
void print_matrix(int** matrix, int row, int col);                         /* f2.row x col배열 출력 */
int free_matrix(int** matrix, int row, int col);                           /* f3.배열 메모리 사용 해제 */
int fill_data(int** matrix, int row, int col);                             /* f4.row x col배열 난수 입력 */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);     /* f5.행렬 덧셈 연산 후 출력 */                    
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);  /* f6.행렬 뺄셈 연산 후 출력 */                           
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);      /* f7.전치 행렬 출력 */   
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);     /* f8.행렬 곱셈 연산 후 출력 */

int main()
{

    char command;       //Matrix Manipulation에서 사용자가 선택한 모드를 의미
    printf("[----- [풍혜림]  [2019020028] -----]\n");

    int row, col;       //차례로 matrix의 행과 열의 크기를 의미
    srand(time(NULL));  //랜덤으로 난수 생성(매번 다른 수를 생성, 그냥 rand()만을 쓰면 매번 같은 수가 생성됨)

    /*[1] 사용자로부터 row, col을 입력받고 row*col크기의 배열 a, b, a_t 생성*/
    printf("Input row and col : ");             
    scanf("%d %d", &row, &col);                 //1.사용자로부터 row와 col값을 입력받음
    int** matrix_a = create_matrix(row, col);   //2.row*col 크기의 2d 배열 a 생성
    int** matrix_b = create_matrix(row, col);   //3.row*col 크기의 2d 배열 b 생성
    int** matrix_a_t = create_matrix(col, row); //4.row*col 크기의 2d 배열 a_t 생성
    //배열 생성 완료! 출력으로 준비완료를 알림
    printf("Matrix Created.\n");

    /*[2] 생성된 배열 a,b가 NULL일 경우 manipulation을 진행하지 않고 -1을 리턴(종료)*/
    if (matrix_a == NULL || matrix_b == NULL) {return -1;}
    
    /*[3] 생성된 배열 a,b가 NULL이 아니라면, manipulation을 최소 한 번 실행*/
    //이때 종료조건은 사용자가 'q' 또는 'Q'를 입력했을 경우이고, 1을 리턴(종료)
    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");   //Matrix Manipulation 메뉴시스템에서 명령 선택
        scanf(" %c", &command); //입력

    /*[4] 사용자 선택 command에 따라 분기해 실행*/
        switch(command) {
            /* z(또는Z)를 입력할 경우 matrix 초기화 진행 - fill_data 호출, 난수를 행렬에 할당 */
        case 'z': case 'Z':
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
            /* p(또는P)를 입력할 경우 matrix 출력 - print_data 호출, 행렬 출력 */
        case 'p': case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
            /* a(또는A)를 입력할 경우 두 matrix를 더하기 연산 후 출력 - addition_matrix 호출, 연산 진행 후 결과 출력 */
        case 'a': case 'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
            /* s(또는S)를 입력할 경우 두 matrix를 빼기 연산 후 출력 - subtraction_matrix 호출, 연산 진행 후 결과 출력 */
        case 's': case 'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
            /* t(또는T)를 입력할 경우 matrix를 transpose(row x col -> col x row) - transpose_matrix 호출 transpose_a_t 생성 후 출력 */
        case 't': case 'T':
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
            break;
            /* m(또는M)를 입력할 경우 두 matrix를 곱하기 연산 후 출력 - transpose_matrix로 transpose_a_t 생성 후 multiply_matrix로 연산 진행, 결과 출력 */
        case 'm': case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
            /* q(또는Q)를 입력할 경우 종료 - malloc한 matrix_a_t, matrix_a, matrix_b 해제 */
        case 'q': case 'Q':
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
            /* command가 메뉴 선택지를 벗어날 경우 경고문 출력 */
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q');

    return 1;
}
/* f1.row x col배열 생성 */
/* create a 2d array whose size is row x col using malloc() */
/* : malloc() 함수를 사용해 row x col 크기의 2차원 배열 생성 */
int** create_matrix(int row, int col)
{
    /* pre conditions */
    if(row<=0||col<=0){
        printf("행렬의 크기가 유효하지 않습니다. 크기를 확인해주세요.\n");
        return NULL;
    }
    //[1] 생성된 matrix를 return해 줄 이중포인터 matrix 선언 - matrix 시작을 가리키는 이중포인터(포인터를 가리키기 때문에 이중포인터 사용)
    int** matrix;
    //[2] matrix에 row개수만큼 int 포인터 공간을 할당 - 각 row를 가리키는 포인터
    matrix = (int**)malloc(sizeof(int*)*row);
    //[3] matrix[i]번째(row)에 col개수만큼 int 공간을 할당 - 각 row에 col만큼 공간 할당(int 크기로)
    for(int i=0; i<row; i++){
        matrix[i] = (int*)malloc(col*sizeof(int));
    }
    /* pro condtions */
    if(matrix==NULL){
        printf("메모리 할당에 실패했습니다.\n");
        return NULL;
    }
    //[4] 생성된 matrix 반환
    return matrix;
}
/* f2.row x col배열 출력 */
/* print matrix whose size is row x col */
/* : row x col 크기의 배열을 화면에 출력 */
void print_matrix(int** matrix, int row, int col)
{
    /* pre conditions */
    if(row<=0||col<=0){
        printf("행렬의 크기가 유효하지 않습니다. 크기를 확인해주세요.\n");
        return;
    }
    //[1] matrix[0][0] ~ matrix[row-1][col-1]까지 반복하며 출력, 각 행은 줄바꿈으로 구분
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    /* pro condtions */
    if(matrix==NULL){
        printf("메모리 할당에 실패했습니다.\n");
        return;
    }
    return;
}
/* f3.배열 메모리 사용 해제 */
/* free memory allocated by create_matrix() */
/* : create_matrix()로 할당된 메모리를 해제 */
int free_matrix(int** matrix, int row, int col)
{
    /* pre conditions */
    if(row<=0||col<=0){
        printf("행렬의 크기가 유효하지 않습니다. 크기를 확인해주세요.\n");
        return -1;
    }
    //[1] matrix[i]번째(row)에 할당해준 메모리 해제
    for(int i=0; i<row; i++){
        free(matrix[i]);
    }
    //[2] matrix에 할당한 메모리 해제
    free(matrix);
    return 1;
    /* pro conditions은 메모리 해제만 진행하므로 따로 없다 */
}
/* f4.row x col배열 난수 입력 */
/* assign random values to the given matrix */
/* : 주어진 배열에 난수 할당 */
int fill_data(int** matrix, int row, int col)
{
    /* pre conditions */
    if(row<=0||col<=0){
        printf("행렬의 크기가 유효하지 않습니다. 크기를 확인해주세요.\n");
        return -1;
    }
    //[1] matrix[0][0] ~ matrix[row-1][col-1]까지 rand()로 생성한 난수를 할당
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            matrix[i][j]=rand()%20;
        }
    }
    /* pro condtions */
    if(matrix==NULL){
        printf("메모리 할당에 실패했습니다.\n");
        return -1;
    }
    return 1;
}
/* f5.행렬 덧셈 연산 후 출력 */
/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    /* pre conditions */
    if(row<=0||col<=0){
        printf("행렬의 크기가 유효하지 않습니다. 크기를 확인해주세요.\n");
        return -1;
    }
    //[1] 덧셈 결과를 저장할 이중포인터 matrix_sum 선언(메모리 할당)
    int** matrix_sum = create_matrix(row, col);
    //[2] matrix_sum의 각 위치에 matrix_a와 matrix_b의 합을 저장
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            matrix_sum[i][j] = matrix_a[i][j]+matrix_b[i][j];
        }
    }
    /* pro condtions */
    if(matrix_a==NULL||matrix_b==NULL||matrix_sum==NULL){
        printf("메모리 할당에 실패했습니다.\n");
        return -1;
    }
    //[3] 결과인 matrix_sum을 print_matrix로 출력
    print_matrix(matrix_sum, row, col);
    //[4] matrix_sum에 할당된 메모리 해제
    free_matrix(matrix_sum, row, col);
    return 1;
}
/* f6.행렬 뺄셈 연산 후 출력 */
/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    /* pre conditions */
    if(row<=0||col<=0){
        printf("행렬의 크기가 유효하지 않습니다. 크기를 확인해주세요.\n");
        return -1;
    }
    //[1] 뺄셈 결과를 저장할 이중포인터 matrix_sub 선언(메모리 할당)
    int** matrix_sub = create_matrix(row, col);
    //[2] matrix_sub의 각 위치에 matrix_a와 matrix_b의 차를 저장
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            matrix_sub[i][j] = matrix_a[i][j]-matrix_b[i][j];
        }
    }
    /* pro condtions */
    if(matrix_a==NULL||matrix_b==NULL||matrix_sub==NULL){
        printf("메모리 할당에 실패했습니다.\n");
        return -1;
    }
    //[3] 결과인 matrix_sub를 print_matrix로 출력
    print_matrix(matrix_sub, row, col);
    //[4] matrix_sub에 할당된 메모리 해제
    free_matrix(matrix_sub, row, col);
    return 1;
}
/* f7.전치 행렬 생성 */
/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    /* pre conditions */
    if(row<=0||col<=0){
        printf("행렬의 크기가 유효하지 않습니다. 크기를 확인해주세요.\n");
        return -1;
    }
    //[1] 전치행렬 matrix_t에 matrix의 index를 row, col을 col, row로 뒤집어 할당
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            matrix_t[i][j] = matrix[j][i];
        }
    }
    /* pro condtions */
    if(matrix==NULL||matrix_t==NULL){
        printf("메모리 할당에 실패했습니다.\n");
        return -1;
    }
    return 1;
}
/* f8.행렬 곱셈 연산 후 출력 */
/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    /* pre conditions */
    if(row<=0||col<=0){
        printf("행렬의 크기가 유효하지 않습니다. 크기를 확인해주세요.\n");
        return -1;
    }
    //[1] 곱셈 연산을 저장할 matrix_axt 행렬을 생성 - create_matrix함수 호출(malloc 함수포함)
    int** matrix_axt=create_matrix(row, row);
    //[2] 임시 변수 temp에 matrix_a[i_a][j]*matrix_t[j][i_t] 값을 j를 변경하며 반복해 계산 후 더함
    for(int i_a=0; i_a<row; i_a++){
        for(int i_t=0; i_t<row; i_t++){
            int temp = 0;
            for(int j=0; j<col; j++){
                temp += matrix_a[i_a][j]*matrix_t[j][i_t];
    //[3] temp에 값을 각 matrix_axt위치에 할당
                matrix_axt[i_a][i_t] = temp;
            }
        }
    }
    /* pro condtions */
    if(matrix_t==NULL||matrix_axt==NULL){
        printf("메모리 할당에 실패했습니다.\n");
        return -1;
    }
    //[4] 곱셈 연산의 결과인 matrix_axt를 print_matrix함수를 호출해 출력
    print_matrix(matrix_axt, row, row);
    //[5] matrix_axt에 할당된 메모리를 free_matrix함수를 호출해 해제
    free_matrix(matrix_axt, row, row);
    /*[!] 솔루션엔 free_matrix(matrix_axt, row, col)로 표기되어있는데, matrix_axt는 row x row 배열이므로 row, row로 수정 */
    return 1;
}