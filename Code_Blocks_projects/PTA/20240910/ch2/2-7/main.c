/*
2-7（三选一） 链表去重
Score 25
Author 陈越
Organization 浙江大学

给定一个带整数键值的链表 L，你需要把其中绝对值重复的键值结点删掉。即对每个键值 K，只有第一个绝对值等于 K 的结点被保留。同时，所有被删除的结点须被保存在另一个链表上。例如给定 L 为 21→-15→-15→-7→15，你需要输出去重后的链表 21→-15→-7，还有被删除的链表 -15→15。
输入格式：

输入在第一行给出 L 的第一个结点的地址和一个正整数 N（≤10^5，为结点总数）。一个结点的地址是非负的 5 位整数，空地址 NULL 用 -1 来表示。

随后 N 行，每行按以下格式描述一个结点：

地址 键值 下一个结点

其中地址是该结点的地址，键值是绝对值不超过10^4的整数，下一个结点是下个结点的地址。
输出格式：

首先输出去重后的链表，然后输出被删除的链表。每个结点占一行，按输入的格式输出。
输入样例：

00100 5
99999 -7 87654
23854 -15 00000
87654 15 -1
00000 -15 99999
00100 21 23854

输出样例：

00100 21 23854
23854 -15 99999
99999 -7 -1
00000 -15 87654
87654 15 -1

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

#define INF_VAL 10001
#define MAX_N 100000
#define ERROR_add (-1)

typedef short val_type;
typedef int add_type;

typedef struct Node_
{
    val_type val;
    add_type next;
} Node;

Node *sLinkedList_Init(const add_type max_n,const add_type n,const add_type head)
{
    Node *list=NULL;
    if((head>=0)&&(head<max_n)&&(n>0)&&(n<=max_n))
    {
        list=malloc((max_n+1)*sizeof(Node));
        for(Node *p=list; p-list<=max_n; ++p)
            p->val=INF_VAL,p->next=(add_type)(p-list);
        list[max_n].next=-1,list->val=(val_type)n,list->next=-1;
    }
    return list;
}

Node *sLinkedList_Del(Node *const list,const add_type max_n)
{
    if(list)
    {
        for(Node *p=list; p-list<=max_n; ++p)
            p->val=0,p->next=0;
        free(list);
    }
    return list;
}

Node *sLinkedList_Write(Node *const list,const add_type max_n,const add_type add,const val_type val,const add_type next)
{
    if(list&&(add>=0)&&(add<max_n)&&(next>=-1)&&(next<max_n))
    {
        Node *p=list+1+add;
        if((p->val)==INF_VAL)
        {
            p->val=val,p->next=next;
            return p;
        }
    }
    return NULL;
}

add_type sLinkedList_Print(const Node *const list,const add_type max_n,const add_type head)
{
    if(list&&(head>=0)&&(head<max_n))
    {
        add_type cnt=0;
        for(const Node *p=list+1+head; p>list; p=list+1+(p->next))
            if(((p-list)<=max_n)&&((p->val)!=INF_VAL))
            {
                printf("%05d %hd ",(add_type)(p-list-1),p->val);
                if(p->next>=0)
                    printf("%05d\n",p->next);
                else
                    printf("%d\n",p->next);
                ++cnt;
            }
            else
                return ERROR_add;
        return cnt;
    }
    return ERROR_add;
}

add_type sLinkedList_Print_hid(const Node *const list,const add_type max_n,const add_type n)
{
    if(list&&(n>0)&&(n<=max_n))
    {
        add_type cnt=0;
        for(const Node *p=list+1+(list->next); cnt<n; p=list+1+(p->next))
            if((p>list)&&((p-list)<=max_n)&&((p->val)!=INF_VAL))
            {
                printf("%05d %hd ",(add_type)(p-list-1),p->val);
                if(++cnt<n)
                    printf("%05d\n",p->next);
                else
                    printf("%d\n",p->next);
            }
            else
                return ERROR_add;
        return cnt;
    }
    return ERROR_add;
}

add_type sLinkedList_rmAbsDup(Node *const list,const add_type max_n,const add_type head)
{
    if(list&&(head>=0)&&(head<max_n)&&((list+1+head)->val!=INF_VAL))
    {
        char AbsExist[INF_VAL]= {0};
        AbsExist[abs(list[1+head].val)]=1;
        add_type cnt=0;
        for(Node *p=list+1+head,*q=list+1+(p->next),*ptr=list; q>list; q=list+1+(p->next))
            if((p>list)&&((p->val)!=INF_VAL)&&((q->val)!=INF_VAL))
                if(AbsExist[abs(q->val)])
                {
                    p->next=q->next;
                    q->next=ptr->next,ptr->next=(add_type)(q-list-1),ptr=q;
                    ++cnt;
                }
                else
                {
                    AbsExist[abs(q->val)]=1;
                    p=q;
                }
            else
                return ERROR_add;
        return cnt;
    }
    return ERROR_add;
}

int main()
{
    add_type N=0,head=0,add=0,next=0;
    scanf("%d%d",&head,&N);
    Node *const List=sLinkedList_Init(MAX_N,N,head);
    val_type val;
    for(add_type i=0; i<N; ++i)
    {
        scanf("%d%hd%d",&add,&val,&next);
        sLinkedList_Write(List,MAX_N,add,val,next);
    }
    add=sLinkedList_rmAbsDup(List,MAX_N,head);
    if(add>=0)
    {
        sLinkedList_Print(List,MAX_N,head);
        sLinkedList_Print_hid(List,MAX_N,add);
    }
    else
        printf("ERROR!\n");
    sLinkedList_Del(List,MAX_N);
    return 0;
}
