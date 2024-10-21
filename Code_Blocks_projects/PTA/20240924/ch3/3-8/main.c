/*
3-8（二选一B组） 堆栈模拟队列
Score 25
Author DS课程组
Organization 浙江大学

设已知有两个堆栈S1和S2，请用这两个堆栈模拟出一个队列Q。

所谓用堆栈模拟队列，实际上就是通过调用堆栈的下列操作函数:

    int IsFull(Stack S)：判断堆栈S是否已满，返回1或0；
    int IsEmpty (Stack S )：判断堆栈S是否为空，返回1或0；
    void Push(Stack S, ElementType item )：将元素item压入堆栈S；
    ElementType Pop(Stack S )：删除并返回S的栈顶元素。

实现队列的操作，即入队void AddQ(ElementType item)和出队ElementType DeleteQ()。
输入格式:

输入首先给出两个正整数N1和N2，表示堆栈S1和S2的最大容量。随后给出一系列的队列操作：A  item表示将item入列（这里假设item为整型数字）；D表示出队操作；T表示输入结束。
输出格式:

对输入中的每个D操作，输出相应出队的数字，或者错误信息ERROR:Empty。如果入队操作无法执行，也需要输出ERROR:Full。每个输出占1行。
输入样例:

3 2
A 1 A 2 A 3 A 4 A 5 D A 6 D A 7 D A 8 D D D D T

输出样例:

ERROR:Full
1
ERROR:Full
2
3
4
7
8
ERROR:Empty

Code Size Limit
16 KB
Time Limit
400 ms
Memory Limit
64 MB
Stack size limit
8192 KB
*/

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef int idxT;

typedef struct Node_stack_
{
    ElementType *A,*top;
    idxT n;
} Node_stack;

typedef Node_stack *Stack;

typedef struct Queue_stack_
{
    Stack stack_in,stack_out;
} Queue_stack;

Queue_stack Q;

int IsFull(Stack S)
{
    if(S&&(S->A))
    {
        ElementType *A=S->A,*top=S->top;
        idxT n=S->n;
        if((!top)||((top>=A)&&(top<A+n)))
            if(top==A+n-1)
                return 1;
            else
                return 0;
        else
            return 1;
    }
    else
        return 1;
}

int IsEmpty (Stack S )
{
    if(S&&(S->A))
    {
        ElementType *A=S->A,*top=S->top;
        idxT n=S->n;
        if((!top)||((top>=A)&&(top<A+n)))
            if(top)
                return 0;
            else
                return 1;
        else
            return 1;
    }
    else
        return 1;
}

void Push(Stack S, ElementType item )
{
    if(S&&(S->A))
        if(!IsFull(S))
        {
            if(S->top)
                *++(S->top)=item;
            else
                *(S->top=S->A)=item;
        }
}

ElementType Pop(Stack S )
{
    ElementType data;
    if(S&&(S->A))
        if(!IsEmpty(S))
        {
            data=*(S->top);
            if((S->top)>(S->A))
                --(S->top);
            else
                S->top=NULL;
        }
    return data;
}

void AddQ(ElementType item)
{
    char flag=-1;
    if((Q.stack_in)&&(Q.stack_out)&&((Q.stack_in)->A)&&((Q.stack_out)->A))
    {
        if(IsFull(Q.stack_in))
            if(IsEmpty(Q.stack_out))
            {
                while((!IsEmpty(Q.stack_in))&&(!IsFull(Q.stack_out)))
                    Push(Q.stack_out,Pop(Q.stack_in));
                if(IsEmpty(Q.stack_in))
                    flag=2;
            }
            else
                flag=0;
        else
            flag=1;
    }
    if(flag>0)
        Push(Q.stack_in,item);
    else
    {
        printf("ERROR");
        if(!flag)
            printf(":Full");
        printf("\n");
    }
}

ElementType DeleteQ()
{
    ElementType data;
    char flag=-1;
    if((Q.stack_in)&&(Q.stack_out)&&((Q.stack_in)->A)&&((Q.stack_out)->A))
    {
        if(IsEmpty(Q.stack_out))
            if(IsEmpty(Q.stack_in))
                flag=0;
            else
            {
                while((((Q.stack_in)->top)>((Q.stack_in)->A))&&(!IsFull(Q.stack_out)))
                    Push(Q.stack_out,Pop(Q.stack_in));
                if(((Q.stack_in)->top)==((Q.stack_in)->A))
                {
                    data=Pop(Q.stack_in);
                    while((!IsEmpty(Q.stack_out))&&(!IsFull(Q.stack_in)))
                        Push(Q.stack_in,Pop(Q.stack_out));
                    if(IsEmpty(Q.stack_out))
                        flag=2;
                }
            }
        else
            data=Pop(Q.stack_out),flag=1;
    }
    if(flag>0)
        printf("%d",data);
    if(flag<=0)
    {
        printf("ERROR");
        if(!flag)
            printf(":Empty");
    }
    printf("\n");
    return data;
}

char modi_queue(char op)
{
    switch(op)
    {
    case 'A':
    {
        ElementType data;
        scanf("%d",&data);
        AddQ(data);
        break;
    }
    case 'D':
        DeleteQ();
        break;
    default:
        printf("ERROR\n");
        return -1;
    }
    return 0;
}

int main()
{
    Q.stack_in=malloc(sizeof(Node_stack)),Q.stack_out=malloc(sizeof(Node_stack));
    ((Q.stack_in)->top)=((Q.stack_out)->top)=NULL;
    idxT n_1=0,n_2=0;
    scanf("%d%d",&n_1,&n_2);
    ((Q.stack_in)->n)=(n_1>n_2)?n_2:n_1,((Q.stack_out)->n)=(n_1>n_2)?n_1:n_2;
    ((Q.stack_in)->A)=malloc(((Q.stack_in)->n)*sizeof(ElementType)),((Q.stack_out)->A)=malloc(((Q.stack_out)->n)*sizeof(ElementType));
    char op=0;
    while((op=(char)getchar())!=EOF)
    {
        op=(char)getchar();
        if(op=='T')
            break;
        else
            modi_queue(op);
    }
    free((Q.stack_in)->A),free((Q.stack_out)->A);
    free(Q.stack_in),free(Q.stack_out);
    return 0;
}
