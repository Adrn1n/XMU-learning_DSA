/*
2-9 一元多项式求导
Score 20
Author DS课程组
Organization 浙江大学

设计函数求一元多项式的导数。
输入格式:

以指数递降方式输入多项式非零项系数和指数（绝对值均为不超过1000的整数）。数字间以空格分隔。
输出格式:

以与输入相同的格式输出导数多项式非零项的系数和指数。数字间以空格分隔，但结尾不能有多余空格。
输入样例:

3 4 -5 2 6 1 -2 0

输出样例:

12 3 -10 1 6 0

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

typedef int coef_type;
typedef short expon_type;
typedef long long idx_type;

typedef struct PolynomNode_
{
    coef_type coef;
    expon_type expon;
} data_type;

typedef struct Node_
{
    data_type data;
    struct Node_ *next;
} Node;

Node *LinkedList_Pushfront(Node **const head,const data_type *const data)
{
    Node *p=malloc(sizeof(Node));
    p->data=*data,p->next=(*head),*head=p;
    return *head;
}

Node *LinkedList_PopFront(Node **const head)
{
    if(*head)
    {
        Node *tmp=*head;
        *head=(*head)->next;
        free(tmp);
    }
    return *head;
}

Node *LinkedList_Del(Node **const head)
{
    while(LinkedList_PopFront(head));
    return *head;
}

char Print_data(const data_type *const data)
{
    printf("%d %hd",data->coef,data->expon);
    return 0;
}

idx_type Print_LinkedList_asPolynom(const Node *head)
{
    idx_type cnt=0;
    while(head)
        if(!Print_data(&(head->data)))
        {
            head=head->next,++cnt;
            if(head)
                printf(" ");
        }
        else
            return -1;
    return cnt;
}

Node *LinkedList_asPolynom_Deriv(const Node *head)
{
    Node *res_head=NULL;
    if(head)
        while(head)
        {
            if((head->data).expon)
            {
                data_type data= {(head->data).coef*(head->data).expon,(expon_type)((head->data).expon-1)};
                LinkedList_Pushfront(&res_head,&data);
            }
            head=head->next;
        }
    return res_head;
}

int main()
{
    data_type data;
    Node *Head=NULL;
    while((scanf("%d%hd",&(data.coef),&(data.expon)))!=EOF)
        LinkedList_Pushfront(&Head,&data);
    Node *Res_head=LinkedList_asPolynom_Deriv(Head);
    idx_type cnt=Print_LinkedList_asPolynom(Res_head);
    if(cnt>0)
        printf("\n");
    else if(!cnt)
        printf("0 0\n");
    else
        printf("ERROR\n");
    LinkedList_Del(&Res_head);
    LinkedList_Del(&Head);
    return 0;
}
