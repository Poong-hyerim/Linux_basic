#include <stdio.h>
//struct로 구조체 선언 - student1
struct student1 {
char lastName;
int studentId;
char grade;
};
//typedef로 구조체 선언 - student2
typedef struct {
char lastName;
int studentId;
char grade;
} student2;

int main()
{
    printf("[----- [풍혜림] [2019020028] -----]\n");
    /*struct로 생성한 구조체의 경우(여기서 student1)는 사용시 앞에 'struct'를 붙인 'struct student1'형태로 사용 가능!*/
    struct student1 st1 = {'A', 100, 'A'};         //student1형 st1변수={lastName:'A', studentId:100, grade:'A'}
    printf("st1.lastName = %c\n", st1.lastName);   //st1.lastName : A
    printf("st1.studentId = %d\n", st1.studentId); //st1.studentId : 100
    printf("st1.grade = %c\n", st1.grade);         //st1.grade : A
    
    /*typedef으로 생성한 구조체(여기서 student2)는 사용시 앞에 'struct'를 붙이지 않고 바로 'student2'로 사용 가능!*/
    student2 st2 = {'B', 200, 'B'};                //student2형 st2변수={lastName:'B', studentId:200, grade:'B'}}
    printf("\nst2.lastName = %c\n", st2.lastName); //st2.lastName : B
    printf("st2.studentId = %d\n", st2.studentId); //st2.studentId : 200
    printf("st2.grade = %c\n", st2.grade);         //st2.grade : B

    student2 st3;                                  //student2형 st3변수 선언
    st3 = st2;                                     //st3에 st2를 구조 치환(st3에 st2 복사 가능)
    printf("\nst3.lastName = %c\n", st3.lastName); //st3.lastName : B
    printf("st3.studentId = %d\n", st3.studentId); //st3.studentId : 200
    printf("st3.grade = %c\n", st3.grade);         //st3.grade : B
    
    /* equality test */
    /*
    전체구조에 대한 동등성을 검사하는 'st3==st2'는 실행할 수 없음! 개별로 일치하는지만 판별 가능!
    if(st3 == st2)
    printf("equal\n");
    else
    printf("not equal\n"); 
    */
    return 0;
}