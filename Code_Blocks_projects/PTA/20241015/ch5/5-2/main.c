/*
5-2 稀疏矩阵加法
Score 20
Author 陈浩川
Organization 厦门大学

给定两个矩阵A和B，求其和矩阵C=A+B。
输入格式:

第一行包含两个数Row和Col，分别表示矩阵的行数和列数，A和B的维度是一致的。

第二行只有一个数N1​，表示接下来要输入的A中的非零元素的个数。

接下来是N1​行，每一行都是i j A[i,j]  这样的形式，表示的A中第i行第j列的元素A[i,j]，为了与大多数编程语言保持一致，它们都是从零开始的，也就是说下标的有效范围是[0,Row−1]×[0,Col−1]。

在N1​行之后，是一个数N2​，表示矩阵B中非零元素的数量，此后N2​行描述B中的非零元素，它们与此前描述A中非零元素的形式一致。

矩阵元素的输入均遵循行主序。这里的所有的输入均可用int类型正确表示，可以假设输入均是合法的。
输出格式:

第一行输出和矩阵C=A+B中的绝对值大于0.1的元素个数N3​，此后是N3​行，按照行主序输出其中的非零元素，依次是行、列的下标和对应的元素。
输入样例:

2 2
1
1 1 1
1
0 0 1

输出样例:

2
0 0 1
1 1 1

Code Size Limit
16 KB
Time Limit
400 ms
Memory Limit
10 MB
Stack size limit
8192 KB
*/

#include <stdio.h>
#include <stdlib.h>

typedef int valT;
typedef int idxT;
typedef int cntT;

typedef struct LkList_Node_
{
    void *data;
    struct LkList_Node_ *next;
} LkList_Node;

typedef struct sMat_Data_
{
    idxT i,j;
    valT val;
} sMat_Data;

typedef struct sMat_Head_
{
    idxT m,n;
    cntT cnt;
} sMat_Head;

LkList_Node *LkList_insert(const void *const data,LkList_Node *const pre)
{
    LkList_Node *node=NULL;
    if(pre)
    {
        node=malloc(sizeof(LkList_Node));
        if(node)
            node->data=(void *)data,node->next=pre->next,pre->next=node;
    }
    return node;
}

LkList_Node *LkList_rm(LkList_Node *const pre)
{
    LkList_Node *node=NULL;
    if(pre)
        node=pre->next,pre->next=node->next,free(node->data),free(node);
    return node;
}

cntT LkList_del(LkList_Node **const LkList_ptr)
{
    cntT cnt=0;
    if(LkList_ptr)
    {
        LkList_Node *node=*LkList_ptr;
        while(node)
        {
            LkList_Node *tmp=node;
            node=node->next;
            free(tmp->data),free(tmp);
        }
    }
    return cnt;
}

LkList_Node *LLsMat_init(const idxT m,const idxT n)
{
    LkList_Node *mat=NULL;
    if((m>0)&&(n>0))
    {
        mat=malloc(sizeof(LkList_Node));
        if(mat)
        {
            sMat_Head *data=malloc(sizeof(sMat_Head));
            if(data)
                data->m=m,data->n=n,data->cnt=0,mat->data=data,mat->next=NULL;
            else
                free(mat),mat=NULL;
        }
    }
    return mat;
}

LkList_Node *LLsMat_insrt(LkList_Node *const mat,const sMat_Data *const data)
{
    if(mat&&((data->i)>0)&&((data->j)>0)&&((data->i)<=(((const sMat_Head *const)(mat->data))->m))&&((data->j)<=(((const sMat_Head *const)(mat->data))->n)))
    {
        LkList_Node *p=mat;
        for(LkList_Node *q=NULL; (q=p->next)&&((((const sMat_Data *const)(q->data))->i)<=(data->i)); p=p->next)
            if((((const sMat_Data *const)(q->data))->i)==(data->i))
            {
                if((((const sMat_Data *const)(q->data))->j)>(data->j))
                    break;
                else if((((const sMat_Data *const)(q->data))->j)==(data->j))
                {
                    free(q->data),q->data=(void *)data;
                    return q;
                }
            }
        if((p=LkList_insert(data,p)))
            ++(((sMat_Head *const)(mat->data))->cnt);
        return p;
    }
    return mat;
}

LkList_Node *LLsMat_NDrm(LkList_Node *const mat,LkList_Node *const pre)
{
    LkList_Node *node=NULL;
    if(mat&&pre)
        node=pre->next,pre->next=node->next,free(node->data),free(node),--(((sMat_Head *const)(mat->data))->cnt);
    return node;
}

cntT LLsMat_print(const LkList_Node *const mat)
{
    cntT cnt=-1;
    if(mat&&((((const sMat_Head *const)(mat->data))->cnt)>=0)&&((((const sMat_Head *const)(mat->data))->m)>0)&&((((const sMat_Head *const)(mat->data))->n)>0))
    {
        printf("%d\n",(((const sMat_Head *const)(mat->data))->cnt)),++cnt;
        for(const LkList_Node *p=mat->next; p; p=p->next)
            printf("%d %d %d\n",(((const sMat_Data *const)(p->data))->i)-1,(((const sMat_Data *const)(p->data))->j)-1,((const sMat_Data *const)(p->data))->val),++cnt;
    }
    if(!mat||(cnt!=(((const sMat_Head *const)(mat->data))->cnt))||((((const sMat_Head *const)(mat->data))->cnt)<0))
        printf("ERROR\n"),cnt=-1;
    return cnt;
}

LkList_Node *LLsMat_add(LkList_Node *const A,const LkList_Node *const B)
{
    if(A&&B&&((((const sMat_Head *const)(A->data))->cnt)>=0)&&((((const sMat_Head *const)(B->data))->cnt)>=0)&&((((const sMat_Head *const)(A->data))->m)>0)&&((((const sMat_Head *const)(A->data))->n)>0)&&((((const sMat_Head *const)(A->data))->m)==(((const sMat_Head *const)(B->data))->m))&&((((const sMat_Head *const)(A->data))->n)==(((const sMat_Head *const)(B->data))->n)))
    {
        LkList_Node *p=A,*tmp=NULL;
        for(const LkList_Node *q=B->next; q; q=q->next)
        {
            char flag=0;
            for(; (tmp=p->next)&&((((const sMat_Data *const)(tmp->data))->i)<=(((const sMat_Data *const)(q->data))->i)); p=p->next)
                if((((const sMat_Data *const)(tmp->data))->i)==(((const sMat_Data *const)(q->data))->i))
                    if((((const sMat_Data *const)(tmp->data))->j)>=(((const sMat_Data *const)(q->data))->j))
                    {
                        if((((const sMat_Data *const)(tmp->data))->j)==(((const sMat_Data *const)(q->data))->j))
                            flag=1;
                        break;
                    }
            if(flag)
            {
                (((sMat_Data *const)(tmp->data))->val)+=(((const sMat_Data *const)(q->data))->val);
                if(((sMat_Data *)(tmp->data))->val)
                    p=tmp;
                else
                {
                    if(!LLsMat_NDrm(A,p))
                        return NULL;
                }
            }
            else
            {
                sMat_Data *data=malloc(sizeof(sMat_Data));
                if(data)
                {
                    data->i=(((const sMat_Data *const)(q->data))->i),data->j=(((const sMat_Data *const)(q->data))->j),data->val=(((const sMat_Data *const)(q->data))->val);
                    if((p=LkList_insert(data,p)))
                    {
                        ++(((sMat_Head *const)(A->data))->cnt);
                        continue;
                    }
                }
                return NULL;
            }
        }
        return A;
    }
    else
        return NULL;
}

int main()
{
    idxT m=0,n=0;
    scanf("%d%d",&m,&n);
    LkList_Node *A=LLsMat_init(m,n),*B=LLsMat_init(m,n);
    char flag=1;
    cntT N=0;
    scanf("%d",&N);
    while(N-->0)
    {
        valT val=0;
        scanf("%d%d%d",&m,&n,&val);
        if(A)
        {
            sMat_Data *data=malloc(sizeof(sMat_Data));
            if(data)
            {
                data->i=m+1,data->j=n+1,data->val=val;
                if(LLsMat_insrt(A,data))
                    continue;
            }
            LkList_del(&A);
        }
    }
    scanf("%d",&N);
    while(N-->0)
    {
        valT val=0;
        scanf("%d%d%d",&m,&n,&val);
        if(B)
        {
            sMat_Data *data=malloc(sizeof(sMat_Data));
            if(data)
            {
                data->i=m+1,data->j=n+1,data->val=val;
                if(LLsMat_insrt(B,data))
                    continue;
            }
            LkList_del(&B);
        }
    }
    if(LLsMat_add(A,B))
        if(LLsMat_print(A)>=0)
            flag=0;
    if(flag)
        printf("ERROR\n");
    return 0;
}
