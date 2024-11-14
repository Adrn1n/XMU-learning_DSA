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

typedef struct oList_Node_
{
    void *data;
    struct oList_Node_ *next1,*next2;
} oList_Node;

typedef struct oList_Head_
{
    oList_Node **head1,**head2;
} oList_Head;

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

typedef struct oL_sMat_
{
    sMat_Head mat;
    oList_Head oList;
} oL_sMat;

oList_Node *oList_insrt(oList_Node *const node,oList_Node *const pre1,oList_Node *const pre2,oList_Node **const ptr1,oList_Node **const ptr2)
{
    if(node&&ptr1&&ptr2)
    {
        if(*ptr1)
            if(pre1)
                node->next1=pre1->next1,pre1->next1=node;
            else
                node->next1=*ptr1,*ptr1=node;
        else
        {
            if(pre1)
                return NULL;
            else
                node->next1=NULL,*ptr1=node;
        }
        if(*ptr2)
            if(pre2)
                node->next2=pre2->next2,pre2->next2=node;
            else
                node->next2=*ptr2,*ptr2=node;
        else
        {
            if(pre2)
                return NULL;
            else
                node->next2=NULL,*ptr2=node;
        }
    }
    return node;
}

oList_Node *oList_rm(oList_Node *const pre1,oList_Node *const pre2,oList_Node **const ptr1,oList_Node **const ptr2)
{
    oList_Node *node=NULL;
    if(ptr1&&ptr2&&(*ptr1)&&(*ptr2))
    {
        if(pre1)
        {
            node=pre1->next1;
            if(node)
                pre1->next1=node->next1;
        }
        else
        {
            node=*ptr1;
            *ptr1=node->next1;
        }
        if(node)
        {
            if(pre2)
                if(node==pre2->next2)
                    pre2->next2=node->next2;
                else
                    node=NULL;
            else
            {
                if(node==*ptr2)
                    *ptr2=node->next2;
                else
                    node=NULL;
            }
        }
        if(node)
            free(node->data),free(node);
    }
    return node;
}

oL_sMat *oLsMat_init(const idxT m,const idxT n)
{
    oL_sMat *matrx=NULL;
    if((m>0)&&(n>0))
    {
        matrx=malloc(sizeof(oL_sMat));
        if(matrx)
        {
            (matrx->mat).cnt=0,(matrx->mat).m=m,(matrx->mat).n=n,(matrx->oList).head1=malloc(m*sizeof(oList_Node *)),(matrx->oList).head2=malloc(n*sizeof(oList_Node *));
            if(((matrx->oList).head1)&&((matrx->oList).head2))
            {
                for(oList_Node **p=(matrx->oList).head1; p-((matrx->oList).head1)<m; ++p)
                    *p=NULL;
                for(oList_Node **p=(matrx->oList).head2; p-((matrx->oList).head2)<n; ++p)
                    *p=NULL;
            }
            else
                free((matrx->oList).head1),free((matrx->oList).head2),free(matrx),matrx=NULL;
        }
    }
    return matrx;
}

cntT oLsMat_del(oL_sMat *const Matrx)
{
    if(Matrx)
    {
        cntT cnt=0;
        const idxT n=(Matrx->mat).m;
        for(oList_Node **p=(Matrx->oList).head1; p-((Matrx->oList).head1)<n; ++p)
            for(oList_Node *q=*p; q;)
            {
                oList_Node *tmp=q;
                q=q->next1;
                free(tmp->data),free(tmp),++cnt;
            }
        free((Matrx->oList).head1),free((Matrx->oList).head2);
        if(cnt==((Matrx->mat).cnt))
        {
            oL_sMat empt= {0};
            *Matrx=empt;
            return cnt;
        }
    }
    return -1;
}

cntT oLsMat_rPrint(const oL_sMat *const Matrx)
{
    if(Matrx)
    {
        cntT cnt=0;
        const idxT n=(Matrx->mat).m;
        printf("%d\n",(Matrx->mat).cnt);
        for(const oList_Node **p=(const oList_Node **)((Matrx->oList).head1); p-(const oList_Node **)((Matrx->oList).head1)<n; ++p)
            for(const oList_Node *q=*p; q; q=q->next1)
                printf("%d %d %d\n",((sMat_Data *)(q->data))->i-1,((sMat_Data *)(q->data))->j-1,((sMat_Data *)(q->data))->val),++cnt;
        if(cnt==((Matrx->mat).cnt))
            return cnt;
    }
    return -1;
}

oList_Node *oLsMat_getPreNode(oL_sMat *const Matrx,const idxT i,const idxT j,const char direc,char ifEq)
{
    oList_Node *pre=NULL;
    if(Matrx&&(i>0)&&(j>0)&&(i<=((Matrx->mat).m))&&(j<=((Matrx->mat).n)))
    {
        if(ifEq)
            ifEq=1;
        switch(direc)
        {
        case 0:
            pre=*((Matrx->oList).head1+i-1);
            for(oList_Node *p=pre; p&&((((sMat_Data *)(p->data))->j)<(j+ifEq)); p=p->next1)
                pre=p;
            if(pre&&((((sMat_Data *)(pre->data))->j)>=(j+ifEq)))
                pre=NULL;
            break;
        case 1:
            pre=*((Matrx->oList).head2+j-1);
            for(oList_Node *p=pre; p&&((((sMat_Data *)(p->data))->i)<(i+ifEq)); p=p->next2)
                pre=p;
            if(pre&&((((sMat_Data *)(pre->data))->i)>=(i+ifEq)))
                pre=NULL;
            break;
        default:
            break;
        }
    }
    return pre;
}

oL_sMat *oLsMat_insrt(oL_sMat *const Matrx,const sMat_Data *const data)
{
    if(Matrx&&data&&(data->val)&&((Matrx->oList).head1)&&((Matrx->oList).head2)&&((data->i)<=(Matrx->mat).m)&&((data->j)<=(Matrx->mat).n))
    {
        oList_Node *const pre1=oLsMat_getPreNode(Matrx,data->i,data->j,0,1),*const pre2=oLsMat_getPreNode(Matrx,data->i,data->j,1,1);
        if(pre1&&pre2&&(((((sMat_Data *)(pre1->data))->j)>=(data->j))||((((sMat_Data *)(pre2->data))->i)>=(data->i))))
        {
            if(((((sMat_Data *)(pre1->data))->j)==(data->j))&&((((sMat_Data *)(pre2->data))->i)==(data->i)))
            {
                free(pre1->data),pre1->data=(void *)data;
                return Matrx;
            }
        }
        else
        {
            oList_Node *const node=malloc(sizeof(oList_Node));
            if(node)
            {
                node->data=(void *)data;
                if(oList_insrt(node,pre1,pre2,(Matrx->oList).head1+(data->i)-1,(Matrx->oList).head2+(data->j)-1)==node)
                {
                    ++((Matrx->mat).cnt);
                    return Matrx;
                }
            }
        }
    }
    return NULL;
}

oL_sMat *oLsMat_add(oL_sMat *const A,const oL_sMat *const B)
{
    if(A&&B&&(((A->mat).m)==((B->mat).m))&&(((A->mat).n)==((B->mat).n)))
    {
        const idxT n=(A->mat).m;
        for(oList_Node **p1=(A->oList).head1,**p2=(B->oList).head1; (p1-((A->oList).head1)<n)&&(p2-((B->oList).head1)<n); ++p1,++p2)
            for(oList_Node *q1=*p1,*q2=*p2,*pre=q1;;)
                if(q2)
                {
                    const idxT i=((sMat_Data *)(q2->data))->i,j2=((sMat_Data *)(q2->data))->j;
                    if(q1)
                    {
                        const idxT j1=((sMat_Data *)(q1->data))->j;
                        if(j1<j2)
                        {
                            if(pre!=q1)
                                pre=pre->next1;
                            q1=q1->next1;
                            continue;
                        }
                        else if(j1==j2)
                        {
                            ((sMat_Data *)(q1->data))->val+=((sMat_Data *)(q2->data))->val;
                            if(((sMat_Data *)(q1->data))->val)
                            {
                                if(pre!=q1)
                                    pre=pre->next1;
                                q1=q1->next1,q2=q2->next1;
                                continue;
                            }
                            else
                            {
                                oList_Node *pre1=pre,*const pre2=oLsMat_getPreNode(A,i,j2,1,0);
                                if(pre==q1)
                                    pre1=NULL,pre=pre->next1;
                                q1=q1->next1,q2=q2->next1;
                                if(oList_rm(pre1,pre2,p1,((A->oList).head2)+j2-1))
                                {
                                    --((A->mat).cnt);
                                    continue;
                                }
                                return NULL;
                            }
                        }
                    }
                    sMat_Data *const data=malloc(sizeof(sMat_Data));
                    if(data)
                    {
                        data->i=i,data->j=((sMat_Data *)(q2->data))->j,data->val=((sMat_Data *)(q2->data))->val;
                        oList_Node *const node=malloc(sizeof(oList_Node)),*pre1=pre,*const pre2=oLsMat_getPreNode(A,i,j2,1,1);
                        if(!node||(pre2&&((((sMat_Data *)(pre2->data))->i)>=i)))
                            free(data),free(node);
                        else
                        {
                            node->data=data;
                            if(pre==q1)
                                pre1=NULL;
                            if(oList_insrt(node,pre1,pre2,p1,((A->oList).head2)+j2-1)==node)
                            {
                                ++((A->mat).cnt);
                                pre=node;
                                q2=q2->next1;
                                continue;
                            }
                        }
                    }
                    return NULL;
                }
                else
                    break;
        return A;
    }
    return NULL;
}

int main()
{
    idxT Row=0,Col=0;
    cntT N1=0,N2=0;
    scanf("%d%d",&Row,&Col);
    oL_sMat *A=oLsMat_init(Row,Col),*B=oLsMat_init(Row,Col);
    char flag=1;
    if(A&&B)
    {
        scanf("%d",&N1);
        for(cntT cnt=0; cnt<N1; ++cnt)
        {
            if(flag)
            {
                sMat_Data *data=malloc(sizeof(sMat_Data));
                if(data)
                {
                    scanf("%d%d%d",&(data->i),&(data->j),&(data->val));
                    ++(data->i),++(data->j);
                    if(!oLsMat_insrt(A,data))
                        flag=0;
                    continue;
                }
            }
            idxT i=0,j=0;
            valT val=0;
            scanf("%d%d%d",&i,&j,&val);
            flag=0;
        }
        scanf("%d",&N2);
        for(cntT cnt=0; cnt<N2; ++cnt)
        {
            if(flag)
            {
                sMat_Data *data=malloc(sizeof(sMat_Data));
                if(data)
                {
                    scanf("%d%d%d",&(data->i),&(data->j),&(data->val));
                    ++(data->i),++(data->j);
                    if(!oLsMat_insrt(B,data))
                        flag=0;
                    continue;
                }
            }
            idxT i=0,j=0;
            valT val=0;
            scanf("%d%d%d",&i,&j,&val);
            flag=0;
        }
        if(flag&&oLsMat_add(A,B)&&(oLsMat_rPrint(A)>=0))
            flag=0;
    }
    if(flag)
        printf("ERROR\n");
    if(oLsMat_del(A)<0)
        printf("ERROR\n");
    if(oLsMat_del(B)<0)
        printf("ERROR\n");
    free(A),free(B);
    return 0;
}
