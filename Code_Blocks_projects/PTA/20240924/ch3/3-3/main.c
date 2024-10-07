/*
3-3（拓展） 表达式转换
Score 25
Author DS课程组
Organization 浙江大学

算术表达式有前缀表示法、中缀表示法和后缀表示法等形式。日常使用的算术表达式是采用中缀表示法，即二元运算符位于两个运算数中间。请设计程序将中缀表达式转换为后缀表达式。
输入格式:

输入在一行中给出不含空格的中缀表达式，可包含+、-、*、/以及左右括号()，表达式不超过20个字符。
输出格式:

在一行中输出转换后的后缀表达式，要求不同对象（运算数、运算符号）之间以空格分隔，但结尾不得有多余空格。
输入样例:

2+3*(7-4)+8/4

输出样例:

2 3 7 4 - * + 8 4 / +

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

typedef char data_type;
typedef long long idx_type;

typedef struct Node_
{
    data_type data;
    struct Node_ *next;
} Node;

Node *Stack_push(Node **const Top,const data_type *const data)
{
    if(Top)
    {
        Node *node=malloc(sizeof(Node));
        node->data=*data,node->next=*Top;
        return (*Top=node);
    }
    return NULL;
}

Node *Stack_pop(Node **const Top)
{
    if(Top&&(*Top))
    {
        Node *tmp=*Top;
        *Top=tmp->next;
        free(tmp);
    }
    return *Top;
}

Node *Stack_del(Node **Top)
{
    while(Stack_pop(Top));
    return (*Top=NULL);
}

Node *Stack_flip(Node **Top)
{
    if(Top)
    {
        if((*Top)&&((*Top)->next))
            for(Node *p=*Top,*q=p->next; q;)
            {
                Node *tmp=q->next;
                q->next=p;
                if(p==*Top)
                    p->next=NULL;
                p=q,q=tmp;
                if(!q)
                {
                    *Top=p;
                    break;
                }
            }
        return *Top;
    }
    return NULL;
}

idx_type Stack_print(const Node *Top)
{
    idx_type cnt=0;
    while(Top)
        printf("%c",Top->data),Top=Top->next,++cnt;
    return cnt;
}

int main()
{
    Node *Top_in=NULL;
    data_type c=0;
    while((c=getchar())!='\n')
        Stack_push(&Top_in,&c);
    Stack_flip(&Top_in);
    Stack_print(Top_in);
    printf("\n");
    Stack_del(&Top_in);
    return 0;
}
