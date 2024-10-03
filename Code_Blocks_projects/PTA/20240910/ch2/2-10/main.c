/*
2-10（拓展） 多项式A除以B
Score 25
Author 陈越
Organization 浙江大学

这仍然是一道关于A/B的题，只不过A和B都换成了多项式。你需要计算两个多项式相除的商Q和余R，其中R的阶数必须小于B的阶数。
输入格式：

输入分两行，每行给出一个非零多项式，先给出A，再给出B。每行的格式如下：

N e[1] c[1] ... e[N] c[N]

其中N是该多项式非零项的个数，e[i]是第i个非零项的指数，c[i]是第i个非零项的系数。各项按照指数递减的顺序给出，保证所有指数是各不相同的非负整数，所有系数是非零整数，所有整数在整型范围内。
输出格式：

分两行先后输出商和余，输出格式与输入格式相同，输出的系数保留小数点后1位。同行数字间以1个空格分隔，行首尾不得有多余空格。注意：零多项式是一个特殊多项式，对应输出为0 0 0.0。但非零多项式不能输出零系数（包括舍入后为0.0）的项。在样例中，余多项式其实有常数项-1/27，但因其舍入后为0.0，故不输出。
输入样例：

4 4 1 2 -3 1 -1 0 -1
3 2 3 1 -2 0 1

输出样例：

3 2 0.3 1 0.2 0 -1.0
1 1 -3.1

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
#include <math.h>

#define EPSILON 5e-2

typedef double coef_type;
typedef int expon_type;
typedef int idx_type;

typedef struct Node_ Node;

typedef struct HeadData_type_
{
    Node *tail;
    idx_type n;
} HeadData_type;

typedef struct PolynomData_type_
{
    expon_type expon;
    coef_type coef;
} PolynomData_type;

typedef union data_type_
{
    PolynomData_type polynom_data;
    HeadData_type head_data;
} data_type;

struct Node_
{
    data_type data;
    Node *next;
};

Node *LinkedList_Init()
{
    Node *head=malloc(sizeof(Node));
    ((head->data).head_data).n=0,((head->data).head_data).tail=head,head->next=NULL;
    return head;
}

Node *LinkedList_Insert(Node *const head,Node *const pre,const data_type *const data)
{
    if(head&&pre)
    {
        Node *node=malloc(sizeof(Node));
        node->data=*data,node->next=pre->next,pre->next=node,++((head->data).head_data).n;
        if(((head->data).head_data).tail==pre)
            ((head->data).head_data).tail=node;
    }
    return head;
}

Node *LinkedList_rmNode(Node *const head,Node *const pre,Node *const node)
{
    if(head&&(((head->data).head_data).n>0)&&((((head->data).head_data).tail)!=head)&&(pre)&&(node)&&((pre->next)==node))
    {
        pre->next=node->next,--((head->data).head_data).n;
        if(((head->data).head_data).tail==node)
            ((head->data).head_data).tail=pre;
        free(node);
    }
    return head;
}

Node *LinkedList_Del(Node *head)
{
    while(head)
    {
        Node *tmp=head;
        head=head->next;
        free(tmp);
    }
    return head;
}

Node *LinkedList_Copy(Node **const dst,const Node *src)
{
    if(!(*dst))
    {
        Node *p=NULL;
        for(; src; src=src->next)
        {
            Node *q=malloc(sizeof(Node));
            q->data=src->data,q->next=NULL;
            if(p)
                p->next=q;
            else
                *dst=q;
            p=q;
        }
        (((*dst)->data).head_data).tail=p;
    }
    return *dst;
}

char LinkedList_swap(Node *const head,Node *const pre_1,Node *const node_1,Node *const pre_2,Node *const node_2)
{
    char flag=0;
    if((pre_1)&&(node_1)&&(pre_2)&&(node_2)&&(pre_1->next==node_1)&&(pre_2->next==node_2))
    {
        pre_1->next=node_1->next,node_1->next=node_2->next;
        if(node_1==pre_2)
            node_2->next=node_1;
        else
            node_2->next=pre_1->next,pre_1->next=node_2,pre_2->next=node_1;
        if(((head->data).head_data).tail==node_1)
            ((head->data).head_data).tail=node_2;
        else if(((head->data).head_data).tail==node_2)
            ((head->data).head_data).tail=node_1;
        flag=1;
    }
    return flag;
}

Node *LinkedList_asPolynom_Arrange(Node *const head)
{
    if(head)
    {
        if((head->next)&&(((head->data).head_data).n))
        {
            char flag=0;
            do
            {
                flag=0;
                for(Node *ptr=head,*p=ptr->next,*q=p->next; q;)
                {
                    if(((q->data).polynom_data).expon>((p->data).polynom_data).expon)
                    {
                        if(!LinkedList_swap(head,ptr,p,p,q))
                            return NULL;
                        ptr=q;
                        flag=1;
                    }
                    else
                        ptr=p,p=q;
                    q=p->next;
                }
            }
            while(flag);
        }
        else if((head->next)||(((head->data).head_data).n))
            return NULL;
        return head;
    }
    else
        return NULL;
}

idx_type LinkedList_asPolynom_Collect(Node *const head)
{
    if(head)
    {
        idx_type cnt=0;
        for(Node *ptr_1=head,*p=head->next; p;)
        {
            if(p->next)
                for(Node *ptr_2=p,*q=ptr_2->next; q;)
                {
                    if(((p->data).polynom_data).expon==((q->data).polynom_data).expon)
                    {
                        ((p->data).polynom_data).coef+=((q->data).polynom_data).coef;
                        LinkedList_rmNode(head,ptr_2,q);
                        ++cnt;
                    }
                    else
                        ptr_2=q;
                    q=ptr_2->next;
                }
            if(fabs(((p->data).polynom_data).coef)<EPSILON)
                LinkedList_rmNode(head,ptr_1,p);
            else
                ptr_1=p;
            p=ptr_1->next;
        }
        return cnt;
    }
    return -1;
}

Node *LinkedList_asPolynom_Simplify(Node *const head)
{
    if((head)&&(LinkedList_asPolynom_Collect(head)>=0)&&(LinkedList_asPolynom_Arrange(head)))
        return head;
    else
        return NULL;
}

Node *LinkedList_asPolynom_nTimes(const coef_type a,Node *const head)
{
    LinkedList_asPolynom_Simplify(head);
    for(Node *p=head->next; p; p=p->next)
        ((p->data).polynom_data).coef*=a;
    return head;
}

Node *LinkedList_asPolynom_xTimes(const expon_type n,Node *const head)
{
    LinkedList_asPolynom_Simplify(head);
    for(Node *p=head->next; p; p=p->next)
        ((p->data).polynom_data).expon+=n;
    return head;
}

Node *LinkedList_asPolynom_Minus(Node *const head_a,Node *const head_b)
{
    if((LinkedList_asPolynom_Simplify(head_a))&&(LinkedList_asPolynom_Simplify(head_b)))
    {
        Node *p=head_a->next,*q=head_b->next;
        while(p&&q)
            if(((p->data).polynom_data).expon<((q->data).polynom_data).expon)
            {
                ((q->data).polynom_data).coef=-((q->data).polynom_data).coef;
                LinkedList_Insert(head_a,p,&(q->data));
                ((q->data).polynom_data).coef=-((q->data).polynom_data).coef;
                q=q->next;
            }
            else if(((p->data).polynom_data).expon>((q->data).polynom_data).expon)
                p=p->next;
            else
            {
                ((p->data).polynom_data).coef-=((q->data).polynom_data).coef;
                p=p->next,q=q->next;
            }
        while(q)
        {
            ((q->data).polynom_data).coef=-((q->data).polynom_data).coef;
            LinkedList_Insert(head_a,((head_a->data).head_data).tail,&(q->data));
            ((q->data).polynom_data).coef=-((q->data).polynom_data).coef;
            q=q->next;
        }
        LinkedList_asPolynom_Simplify(head_a);
    }
    return head_a;
}

char LinkedList_asPolynom_Divide(Node *const head_a,Node *const head_b,Node **const head_q,Node **const head_r)
{
    char flag=0;
    if((head_a)&&(head_b))
        if((LinkedList_asPolynom_Simplify(head_a))&&(LinkedList_asPolynom_Simplify(head_b)))
            if((head_b->next)&&(((head_b->data).head_data).n))
            {
                *head_q=LinkedList_Init(),*head_r=head_a;
                while((head_a->next)&&(((head_a->data).head_data).n)&&((((head_a->next)->data).polynom_data).expon>=(((head_b->next)->data).polynom_data).expon))
                {
                    data_type data= {.polynom_data={(((head_a->next)->data).polynom_data).expon-(((head_b->next)->data).polynom_data).expon,(((head_a->next)->data).polynom_data).coef/(((head_b->next)->data).polynom_data).coef}};
                    LinkedList_Insert(*head_q,(((*head_q)->data).head_data).tail,&data);
                    Node *tmp=NULL;
                    LinkedList_Copy(&tmp,head_b);
                    tmp=LinkedList_asPolynom_nTimes((data.polynom_data).coef,tmp);
                    tmp=LinkedList_asPolynom_xTimes((data.polynom_data).expon,tmp);
                    LinkedList_asPolynom_Minus(head_a,tmp);
                    LinkedList_Del(tmp);
                }
                if((((head_a->next)&&(((head_a->data).head_data).n))||(!(head_a->next)&&(!(((head_a->data).head_data).n))))&&(LinkedList_asPolynom_Simplify(*head_q)))
                    flag=1;
                return flag;
            }
    return flag;
}

idx_type LinkedList_asPolynom_Read(Node *const head,idx_type n)
{
    idx_type cnt=0;
    while(n--)
    {
        data_type data;
        scanf("%d%lf",&((data.polynom_data).expon),&((data.polynom_data)).coef);
        LinkedList_Insert(head,((head->data).head_data).tail,&data);
        ++cnt;
    }
    return cnt;
}

char Print_data(const data_type *const data)
{
    printf("%d %.1lf",(data->polynom_data).expon,(data->polynom_data).coef);
    return 0;
}

idx_type LinkedList_asPolynom_Print(const Node *head)
{
    if(head)
    {
        idx_type cnt=0;
        printf("%d",((head->data).head_data).n);
        while((head=head->next))
        {
            printf(" ");
            if(!Print_data(&(head->data)))
                ++cnt;
            else
                return -1;
        }
        return cnt;
    }
    else
        return -1;
}

int main()
{
    Node *Head_A=LinkedList_Init(),*Head_B=LinkedList_Init(),*Head_q=NULL,*Head_r=NULL;
    idx_type n_A=0,n_B=0;
    char flag=0;
    scanf("%d",&n_A);
    if(LinkedList_asPolynom_Read(Head_A,n_A)==n_A)
        flag=1;
    scanf("%d",&n_B);
    if((LinkedList_asPolynom_Read(Head_B,n_B)==n_B)&&flag)
        flag=1;
    else
        flag=0;
    if(flag)
    {
        flag=LinkedList_asPolynom_Divide(Head_A,Head_B,&Head_q,&Head_r);
        if(flag)
        {
            if(!(n_A=LinkedList_asPolynom_Print(Head_q)))
                printf(" 0 0.0");
            else if(n_A<0)
                flag=0;
            printf("\n");
            if(!(n_B=LinkedList_asPolynom_Print(Head_r)))
                printf(" 0 0.0");
            else if(n_B<0)
                flag=0;
        }
    }
    if(!flag)
        printf("\nERROR");
    printf("\n");
    LinkedList_Del(Head_A);
    LinkedList_Del(Head_B);
    LinkedList_Del(Head_q);
    return 0;
}
