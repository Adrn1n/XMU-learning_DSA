/*
2-12（二选一A） 删除单链表偶数节点
Score 20
Author C课程组
Organization 浙江大学

本题要求实现两个函数，分别将读入的数据存储为单链表、将链表中偶数值的结点删除。链表结点定义如下：

struct ListNode {
    int data;
    struct ListNode *next;
};

函数接口定义：

struct ListNode *createlist();

struct ListNode *deleteeven( struct ListNode *head );

函数createlist从标准输入读入一系列正整数，按照读入顺序建立单链表。当读到−1时表示输入结束，函数应返回指向单链表头结点的指针。

函数deleteeven将单链表head中偶数值的结点删除，返回结果链表的头指针。
裁判测试程序样例：

#include <stdio.h>

#include <stdlib.h>


struct ListNode {

    int data;

    struct ListNode *next;

};


struct ListNode *createlist();

struct ListNode *deleteeven( struct ListNode *head );

void printlist( struct ListNode *head )

{

     struct ListNode *p = head;

     while (p) {

           printf("%d ", p->data);

           p = p->next;

     }

     printf("\n");

}


int main()

{

    struct ListNode *head;


    head = createlist();

    head = deleteeven(head);

    printlist(head);


    return 0;

}


/* 你的代码将被嵌在这里 */
/*

输入样例：

1 2 2 3 4 5 6 7 -1

输出样例：

1 3 5 7

Code Size Limit
16 KB
Time Limit
400 ms
Memory Limit
64 MB
*/

#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
    int data;
    struct ListNode *next;
};

struct ListNode *createlist();
struct ListNode *deleteeven( struct ListNode *head );
void printlist( struct ListNode *head )
{
    struct ListNode *p = head;
    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    struct ListNode *head;

    head = createlist();
    head = deleteeven(head);
    printlist(head);

    return 0;
}

/* 你的代码将被嵌在这里 */
struct ListNode *createlist()
{
    struct ListNode *head=NULL,*p=head;
    int data=0;
    while(scanf("%d",&data),data!=-1)
    {
        struct ListNode *node=malloc(sizeof(struct ListNode));
        node->data=data,node->next=NULL;
        if(p)
            p=p->next=node;
        else
            head=p=node;
    }
    return head;
}
struct ListNode *deleteeven( struct ListNode *head )
{
    while(head&&(!((head->data)%2)))
    {
        struct ListNode *tmp=head;
        head=head->next;
        free(tmp);
    }
    if(head)
    {
        for(struct ListNode *p=head,*q=p->next; q; q=p->next)
            if(!((q->data)%2))
            {
                struct ListNode *tmp=q;
                p->next=q->next;
                free(tmp);
            }
            else
                p=q;
    }
    return head;
}
