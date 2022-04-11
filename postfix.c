#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_STACK_SIZE 10      
#define MAX_EXPRESSION_SIZE 20
/* stack 내에서 우선순위, lparen = 0 가장 낮음(우선순위를 하나만 사용!) */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1  /* 피연산자 */
} precedence;
char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	    /* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		    /* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  				/* postfixStack용 top */
int evalStackTop = -1;	   				/* evalStack용 top */
int evalResult = 0;	   					/* 계산 결과를 저장 */

/* 사용자 정의 함수 */
void postfixpush(char x);				//f1.postfix로 삽입(push)
char postfixPop();						//f2.postfix로 삭제(pop)
void evalPush(int x);					//f3.eval과정에서 삽입(push)
int evalPop();							//f4.eval과정에서 삭제(pop)
void getInfix();						//f5.infix expression을 입력받아 infixExp 배열에 저장
precedence getToken(char symbol);		//f6.기호 별 우선순위를 반환(symbol->precedence로)
precedence getPriority(char x);			//f7.f6으로 값 x를 넘겨줌(x->symbol->precedence로)
void charCat(char* c);					//f8.전달받은 하나의 문자를 postfixExp 배열에 추가
void toPostfix();						//f9.infixExp 원소를 하나씩 읽어 stack을 통해 postfix형으로 변경해 postFix배열로 저장
void debug();							//f10.디버깅 모드로 infix, postfix, eval, postfixstack 현황을 한번에 보여줌
void reset();							//f11.infixExp, postfixExp 배열을 각각 초기화해 reset
void evaluation();						//f12.postfix로 표현된 식을 계산

int main()
{
	printf("[----- [풍혜림]  [2019020028] -----]");
	char command;  /* 사용자 명령 저장 변수 command 선언 */
	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);
		/* 사용자 입력 command에 따라 분기 */
		switch(command) {
		/* Infix 모드 */
		case 'i': case 'I':
			getInfix();
			break;
		/* Postfix로 변환 모드 */
		case 'p': case 'P':
			toPostfix();
			break;
		/* Evaluation 모드 */
		case 'e': case 'E':
			evaluation();
			break;
		/* Debug 모드 */
		case 'd': case 'D':
			debug();
			break;
		/* Rester 모드 */
		case 'r': case 'R':
			reset();
			break;
		/* Quit 모드 */
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');
	return 1;
}
//f1.postfix로 삽입(push)-postfixStack[++postfixStackTop]에 입력 값을 삽입
void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x;
}
//f2.postfix로 삭제(pop)-postfixStackTop이 '-1'이 아닐경우(postfixstack이 빈스택이 아닌 값이 저장된 스택) top의 값을 꺼낸 뒤 top -1 감소
char postfixPop()
{
    char x;
    if(postfixStackTop == -1)
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--];
    }
    return x;
}
//f3.eval과정에서 삽입(push)-연산용 evalStack[++evalStackTop]에 입력 값을 삽입
void evalPush(int x)
{
    evalStack[++evalStackTop] = x;
}
//f4.eval과정에서 삭제(pop)-연산용 evalStack에서 top이 가리키는 값을 꺼낸 뒤 top -1 감소
int evalPop()
{
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}
//f5.infix expression을 입력받아 infixExp 배열에 저장
void getInfix()
{
    printf("Type the expression >>> "); 
    scanf("%s",infixExp);				
}
//f6.기호 별 우선순위를 반환(symbol(기호:()+-/*)->precedence(lapren,rparen,plus,minus,divide,times,operand)로)
precedence getToken(char symbol)
{
	switch(symbol) {
	case '(' : return lparen; //왼 괄호
	case ')' : return rparen; //오른 괄호
	case '+' : return plus;   //더하기
	case '-' : return minus;  //빼기
	case '/' : return divide; //나누기
	case '*' : return times;  //곱하기
	default  : return operand; //피연산자
	}
}
//f7.f6으로 값 x를 넘겨줌(x->symbol->precedence로)-char x를 입력받아 f6.getToken함수로 넘겨 줌
precedence getPriority(char x)
{
	return getToken(x);
}
//f8.전달받은 하나의 문자를 postfixExp 배열에 추가
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}
//f9.infixExp 원소를 하나씩 읽어 stack을 통해 postfix형으로 변경해 postFix배열로 저장
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	/* 문자하나를 임시로 저장하기 위한 변수 */
	char x;

	/* exp를 증가시켜가면서 '\0'이 나올때 까지, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0')
	{
		/* infixExp원소가 operand'피연산자'일 경우 */
		if(getPriority(*exp)==operand){
			x=*exp;			   //x에 operand로 판정된 infixExp배열의 원소를 역참조해 할당
			charCat(&x);	   //x를 postfixExp 배열에 추가
		}
		/* infixExp원소가 lparen'('일 경우 */
		else if(getPriority(*exp)==lparen){
			postfixPush(*exp); //'('를 postfixStack 배열에 추가
		}
		/* infixExp원소가 rparen')'일 경우 */
		else if(getPriority(*exp)==rparen){
			//postfixStack에서 '('표시가 나올때 까지 출력해서 postfixExp 배열로 추가
			while((x=postfixPop())!='('){
				charCat(&x);
			}
		}
		/* infixExp원소가 operator'plus+, minus-, divide/, times*'일 경우 */
		else{
			/* postfixStackTop의 우선순위가 exp(infixExp 원소)보다 높거나 같으면 */
			while(getPriority(postfixStack[postfixStackTop])>=getPriority(*exp))
			{
				x=postfixPop(); //x에 postfixStack에서 pop해 할당
				charCat(&x);    //x를 postfixExp 배열에 추가
			}
			/* postfixStackTop의 우선순위가 exp(infixExp 원소)보다 낮아지면 */
			postfixPush(*exp);  //postfixStackdp infixExp에 우선순위 높은 연산자를 삽입
		}
		exp++;					//exp를 옮겨 infixExp의 다음 원소로 비교를 이동!
	}
	/* postfixStack이 비워질때까지 pop해서 postfixExp에 할당 */
	while(postfixStackTop!=-1){
		x=postfixPop();		 //x에 postfixStack에서 pop해 할당
		charCat(&x);		 //x를 postfixExp 배열에 추가
	}
}
//f10.디버깅 모드로 infix, postfix, eval, postfixstack 현황을 한번에 보여줌
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}
//f11.infixExp, postfixExp 배열을 각각 초기화해 reset
void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}
//f12.postfix로 표현된 식을 계산
void evaluation()
{
	int op1, op2, i;			   
	int length=strlen(postfixExp); 		//배열의 길이를 변수 length에 할당
	char symbol;				   
	evalStackTop = -1; 			   		//eval용 stack의 시작을 -1로 지정(마지막 값이 할당된 위치자체를 가리킴!)

	for(i=0;i<length;i++){
		symbol=postfixExp[i];			//postfixExp에 저장된 원소 출력
		//symbol(postfixExp 원소)이 operand'피연산자'이면
		if(getToken(symbol)==operand){ 
			evalPush(symbol - '0');		//symbol에서 0을 빼고 evalStack에 삽입
		}
		//symbol(postfixExp 원소)이 operand'피연산자'가 아닌 기호(()+-/*)이면
		else{
			op2=evalPop();				//pop해서 피연산자 1개 확보
			op1=evalPop();				//pop해서 나머지 피연산자 1개 확보
			switch(getToken(symbol)){ 
				case plus:
				evalPush(op1+op2); //더하기 진행해서 결과 push
				break;
				case minus:
				evalPush(op1-op2); //더하기 진행해서 결과 push
				break;
				case times:
				evalPush(op1*op2); //곱하기 진행해서 결과 push
				break;
				case divide:
				evalPush(op1/op2); //나누기 진행해서 결과 push
				break;
				default:
				break;
			}
		}
	}
	/* 최종으로 남아있는 연산결과를 pop해 evalResult 전역 변수에 할당 */
	evalResult=evalPop();
}

