/*
2-8（三选一） 重排链表
Score 25
Author 陈越
Organization 浙江大学

给定一个单链表 L1​→L2​→⋯→Ln−1​→Ln​，请编写程序将链表重新排列为 Ln​→L1​→Ln−1​→L2​→⋯。例如：给定L为1→2→3→4→5→6，则输出应该为6→1→5→2→4→3。
输入格式：

每个输入包含1个测试用例。每个测试用例第1行给出第1个结点的地址和结点总个数，即正整数N (≤10^5)。结点的地址是5位非负整数，NULL地址用−1表示。

接下来有N行，每行格式为：

Address Data Next

其中Address是结点地址；Data是该结点保存的数据，为不超过10^5的正整数；Next是下一结点的地址。题目保证给出的链表上至少有两个结点。
输出格式：

对每个测试用例，顺序输出重排后的结果链表，其上每个结点占一行，格式与输入相同。
输入样例：

00100 6
00000 4 99999
00100 1 12309
68237 6 -1
33218 3 00000
99999 5 68237
12309 2 33218

输出样例：

68237 6 00100
00100 1 99999
99999 5 12309
12309 2 00000
00000 4 33218
33218 3 -1

Code Size Limit
16 KB
Time Limit
500 ms
Memory Limit
64 MB
Stack size limit
8192 KB
*/

#include <stdio.h>
#include <stdlib.h>

#define NaN_VAL (-1)
#define MAX_N 100000
#define ERROR_add (-1)

typedef int val_type;
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
            p->val=NaN_VAL,p->next=(add_type)(p-list);
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
        if((p->val)==NaN_VAL)
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
            if(((p-list)<=max_n)&&((p->val)!=NaN_VAL))
            {
                printf("%05d %d ",(add_type)(p-list-1),p->val);
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

add_type sLinkedList_Flip_from(Node *const list,const add_type max_n,add_type *const head,Node *const pre_start)
{
    if(list&&(*head>=0)&&(*head<max_n)&&((list[*head+1].val)!=NaN_VAL)&&(pre_start>=list)&&((pre_start-list)<max_n))
    {
        add_type cnt=0;
        for(Node *p=(pre_start>list)?(list+1+(pre_start->next)):(list+1+(*head)),*q=list+1+(p->next); q>list; ++cnt)
            if((p>list)&&((p-list)<=max_n)&&((p->val)!=NaN_VAL)&&((q-list)<=max_n)&&((q->val)!=NaN_VAL))
            {
                add_type tmp=q->next;
                q->next=(add_type)(p-list-1);
                if(((pre_start>list)&&(p==(list+1+(pre_start->next))))||(pre_start==list))
                    p->next=-1,++cnt;
                p=q,q=list+1+tmp;
                if(q==list)
                    if(pre_start>list)
                        pre_start->next=(add_type)(p-list-1);
                    else
                        *head=(add_type)(p-list-1);
                else if(q<list)
                    return ERROR_add;
            }
            else
                return ERROR_add;
        return cnt;
    }
    return ERROR_add;
}

add_type sLinkedList_Rearrange(Node *const list,const add_type max_n,add_type *const head)
{
    if(list&&(*head>=0)&&(*head<max_n)&&((list[*head+1]).val!=NaN_VAL))
    {
        Node *ptr=list+1+(*head);
        for(const Node *p=list+1+(ptr->next); p>list; ptr=list+1+(ptr->next))
            if((ptr>list)&&((ptr-list)<=max_n)&&((ptr->val)!=NaN_VAL)&&((p-list)<=max_n)&&((p->val)!=NaN_VAL))
            {
                if((p=list+1+(p->next))>list)
                {
                    if((p=list+1+(p->next))>list)
                        continue;
                }
                else if(p<list)
                    return ERROR_add;
                break;
            }
            else
                return ERROR_add;
        add_type cnt=0;
        if(((ptr->next)==-1)&&(ptr==list+1+(*head)))
            return cnt;
        else if(sLinkedList_Flip_from(list,max_n,head,ptr)>=0)
        {
            for(Node *p=NULL; p!=ptr; ++cnt)
                if((!p)||((p>list)&&((p-list)<=max_n)&&((p->val)!=NaN_VAL)))
                {
                    add_type tmp=ptr->next;
                    ptr->next=list[1+tmp].next;
                    if(p)
                    {
                        list[1+tmp].next=p->next;
                        p->next=tmp;
                        p=list+1+list[1+tmp].next;
                    }
                    else
                    {
                        list[1+tmp].next=(*head);
                        p=list+1+(*head);
                        *head=tmp;
                    }
                }
                else
                    return ERROR_add;
            return cnt;
        }
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
        scanf("%d%d%d",&add,&val,&next);
        sLinkedList_Write(List,MAX_N,add,val,next);
    }
    if(sLinkedList_Rearrange(List,MAX_N,&head)>=0)
        sLinkedList_Print(List,MAX_N,head);
    else
        printf("ERROR!\n");
    sLinkedList_Del(List,MAX_N);
    return 0;
}
