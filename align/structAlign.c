#include <stdio.h> 
#pragma pack(8)
typedef union 
{
    /* data */
    char a[10]; // 10 vs 8 or 4 
    double b; 
} myunion;


// moudle = 8 or 4 
typedef struct 
{
    short s;    //4  
    int i;      //8 
    double d;   //16 -> 
    char c;     //16 + 8 结构体的最终大小 最宽基本类型/对齐模数的整数倍
} A;

typedef struct 
{
    char c;     // 整数倍，具体是几倍，看后面的成员大小
    short s; 
    int i; 
    double d; 
}B;

typedef struct 
{
    short s; // 最宽基本成员
    char c;  // 1与对齐模数之间取较小值1. 
}C; // 最宽基本成员的整数倍 -> 2 * 2 = 4 


struct packed_struct {
  unsigned int f1:1;
  unsigned int f2:1;
  unsigned int f3:1;
  unsigned int f4:1;
  unsigned int type:4;
  unsigned int my_int:9;
} pack;

int main()
{


    printf("%lu\n", sizeof(myunion));
    printf("%lu\n", sizeof(A));
    printf("%lu\n", sizeof(B));
   
    A a; 
    printf("%p\n", &a.s); 
    printf("%p\n", &a.i); 
    printf("%p\n", &a.d); 
    printf("%p\n", &a.c); 

    B b; 
    printf("%p\n", &b.c); 
    printf("%p\n", &b.s); 
    printf("%p\n", &b.i); 
    printf("%p\n", &b.d); 

    printf("\n%lu\n", sizeof(C));


    printf("%lu\n", sizeof(pack));
    return 0; 
}