/*
2-13（二选一B） 两个有序链表序列的交集
Score 25
Author DS课程组
Organization 浙江大学

已知两个非降序链表序列S1与S2，设计函数构造出S1与S2的交集新链表S3。
输入格式:

输入分两行，分别在每行给出由若干个正整数构成的非降序序列，用−1表示序列的结尾（−1不属于这个序列）。数字用空格间隔。
输出格式:

在一行中输出两个输入序列的交集序列，数字间用空格分开，结尾不能有多余空格；若新链表为空，输出NULL。
输入样例:

1 2 5 -1
2 4 5 8 10 -1

输出样例:

2 5

Code Size Limit
16 KB
Java (javac)
Time Limit
1000 ms
Memory Limit
128 MB
Other Compilers
Time Limit
1000 ms
Memory Limit
64 MB
Stack size limit
8192 KB
*/

#include <stdio.h>
#include <stdlib.h>

typedef long long data_type;
typedef long long idx_type;

typedef struct Node_
{
    data_type val;
    struct Node_ *next;
} Node;

Node *LinkedList_Pushback(Node **const head,Node **const tail,const data_type *val)
{
    Node *p=malloc(sizeof(Node));
    p->val=*val,p->next=NULL;
    if((*head)&&(*tail))
        (*tail)->next=p,*tail=p;
    else if((*head)||(*tail))
        return NULL;
    else
        *head=*tail=p;
    return p;
}

Node *LinkedList_Popfront(Node **const head)
{
    if(*head)
    {
        Node *p=*head;
        *head=(*head)->next;
        free(p);
    }
    return *head;
}

char LinkedList_Del(Node *head)
{
    while(LinkedList_Popfront(&head));
    return 1;
}

Node *LinkedList_GetIntersection(const Node *head_1,const Node *head_2)
{
    Node *head_res=NULL,*tail_res=head_res;
    while(head_1&&head_2)
        if((head_1->val)<(head_2->val))
            head_1=head_1->next;
        else if((head_1->val)>(head_2->val))
            head_2=head_2->next;
        else
            LinkedList_Pushback(&head_res,&tail_res,&(head_1->val)),head_1=head_1->next,head_2=head_2->next;
    return head_res;
}

Node *LinkedList_Read()
{
    Node *head=NULL,*tail=head;
    data_type val=0;
    while(scanf("%lld",&val),val!=-1)
        LinkedList_Pushback(&head,&tail,&val);
    return head;
}

idx_type LinkedList_Print(const Node *head)
{
    idx_type cnt=0;
    if(head)
    {
        while(head->next)
            printf("%lld ",head->val),head=head->next,++cnt;
        printf("%lld",head->val);
    }
    return cnt;
}

int main()
{
    Node *S1=LinkedList_Read(),*S2=LinkedList_Read();
    if(!LinkedList_Print(LinkedList_GetIntersection(S1,S2)))
        printf("NULL");
    printf("\n");
    LinkedList_Del(S1),LinkedList_Del(S2);
    return 0;
}
