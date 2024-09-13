/*
1-6（四选二） 最长连续递增子序列
Score 20
Author DS课程组
Organization 浙江大学
给定一个顺序存储的线性表，请设计一个算法查找该线性表中最长的连续递增子序列。例如，(1,9,2,5,7,3,4,6,8,0)中最长的递增子序列为(3,4,6,8)。

输入格式:
输入第1行给出正整数n（≤10^5）；第2行给出n个整数，其间以空格分隔。

输出格式:
在一行中输出第一次出现的最长连续递增子序列，数字之间用空格分隔，序列结尾不能有多余空格。

输入样例：
15
1 9 2 5 7 3 4 6 8 0 11 15 17 17 10
输出样例：
3 4 6 8
Code Size Limit
16 KB
Java (javac)
Time Limit
800 ms
Memory Limit
64 MB
Other Compilers
Time Limit
400 ms
Memory Limit
64 MB
Stack size limit
8192 KB
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct LL_Node
{
    long long val;
    struct LL_Node *next;
} ll_node;

ll_node *ll_node_push_back(const long long val,ll_node **const head,ll_node **const tail)
{
    ll_node *cur=malloc(sizeof(ll_node));
    cur->val=val,cur->next=NULL;
    if(*tail)
        (*tail)->next=cur;
    *tail=cur;
    if(!(*head))
        *head=cur;
    return cur;
}

char ll_node_pop_front(ll_node **const head)
{
    if(head)
    {
        ll_node *tmp=(*head)->next;
        (*head)->val=0,(*head)->next=NULL;
        free((ll_node *)(*head));
        *head=tmp;
        return 0;
    }
    else
        return 1;
}

char ll_node_delete(ll_node *head)
{
    while(ll_node_pop_front(&head));
    return 0;
}

char ll_node_Judge_len(int *const l_1,const ll_node **const Front_1,const ll_node **const Back_1,const int l_2,const ll_node *const Front_2,const ll_node *const Back_2)
{
    if(l_2>*l_1)
    {
        *Front_1=Front_2,*Back_1=Back_2;
        *l_1=l_2;
        return 1;
    }
    else
        return 0;
}

int ll_node_Find_max_incrs_subseq(const ll_node **const Front,const ll_node **const Back)
{
    int l=0,l_tmp=0;
    if(*Front)
    {
        l=l_tmp=1;
        const ll_node *p=*Front,*tmp1=*Front,*tmp2=*Front;
        while(p->next)
        {
            if(((p->next)->val)>(p->val))
                tmp2=p->next,++l_tmp;
            else
            {
                ll_node_Judge_len(&l,Front,Back,l_tmp,tmp1,tmp2);
                tmp1=p->next,tmp2=tmp1,l_tmp=1;
            }
            p=p->next;
        }
        ll_node_Judge_len(&l,Front,Back,l_tmp,tmp1,tmp2);
    }
    return l;
}

int main()
{
    int n=0,l=0;
    scanf("%d",&n);
    ll_node *Head=NULL,*Tail=NULL,*Front=NULL,*Back=NULL;
    for(int i=0; i<n; ++i)
    {
        long long val;
        scanf("%lld",&val);
        ll_node_push_back(val,&Head,&Tail);
    }
    Front=Back=Head;
    l=ll_node_Find_max_incrs_subseq((const ll_node **)(&Front),(const ll_node **)(&Back));
    if(l)
    {
        const ll_node *p=Front;
        for(int i=0; i<l-1; ++i)
        {
            printf("%lld ",p->val);
            p=p->next;
        }
        if(p==Back)
            printf("%lld",p->val);
        else
            printf("ERROR!");
    }
    ll_node_delete(Head);
    printf("\n");
    return 0;
}
