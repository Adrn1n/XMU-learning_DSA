/*
6-2（二选一） 列出叶结点
Score 25
Author 陈越
Organization 浙江大学
对于给定的二叉树，本题要求你按从上到下、从左到右的顺序输出其所有叶结点。

输入格式：
首先第一行给出一个正整数 n（≤10），为树中结点总数。树中的结点从 0 到 n−1 编号。随后 n 行，每行给出一个对应结点左右孩子的编号。如果某个孩子不存在，则在对应位置给出 "-"。编号间以 1 个空格分隔。

输出格式：
在一行中按规定顺序输出叶结点的编号。编号间以 1 个空格分隔，行首尾不得有多余空格。

输入样例：
8
1 -
- -
0 -
2 7
- -
- -
5 -
4 6
输出样例：
4 1 5
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

#define N_MAX 10

typedef short idxT;
typedef char valT;

typedef struct binTreNode_
{
    idxT idx;
    valT val,lc_v,rc_v;
} binTreNode;

typedef struct queNode_
{
    void *data;
    struct queNode_ *next;
} queNode;

typedef struct queHD_
{
    queNode *tail;
} queHD;

queNode *que_init()
{
    queNode *que=malloc(sizeof(queNode));
    if(que)
    {
        queHD *hd=malloc(sizeof(queHD));
        if(hd)
            hd->tail=que,que->data=hd,que->next=NULL;
        else
            free(que),que=NULL;
    }
    return que;
}

queNode *que_push(const void *const data,queNode *const que)
{
    queNode *node=NULL;
    if(que)
    {
        node=malloc(sizeof(queNode));
        if(node)
            node->data=(void *)data,node->next=NULL,(((queHD *)(que->data))->tail)->next=node,((queHD *)(que->data))->tail=node;
    }
    return node;
}

queNode *que_pop(queNode *const que)
{
    queNode *node=que;
    if(que)
        if((node=que->next))
        {
            que->next=node->next,free(node->data),free(node);
            if(!(que->next))
                ((queHD *)(que->data))->tail=que;
        }
    return node;
}

char que_isEmpty(queNode *const*const que_ptr)
{
    if(que_ptr&&(*que_ptr))
        return (char)((((queHD *)((*que_ptr)->data))->tail)==*que_ptr);
    else
        return -1;
}

idxT que_del(queNode **const que_ptr)
{
    idxT cnt=0;
    if(que_ptr&&(*que_ptr))
    {
        while(!que_isEmpty(que_ptr))
            que_pop(*que_ptr),++cnt;
        free((*que_ptr)->data),free(*que_ptr);
        *que_ptr=NULL;
    }
    return cnt;
}

void *que_getTop(queNode *const que)
{
    void *data=NULL;
    if(que&&(!que_isEmpty(&que)))
        data=(que->next)->data;
    return data;
}

idxT binTre_asignIdx(binTreNode *const T,const idxT n)
{
    idxT cnt=0;
    if(T&&(n>0))
    {
        char Exist[n];
        for(char *p=Exist; p-Exist<n; *p++=1);
        for(binTreNode *p=T; p-T<n; ++p)
        {
            if((p->lc_v)!='-')
            {
                idxT lc_Vofst=(idxT)((p->lc_v)-'0');
                if((lc_Vofst>=0)&&(lc_Vofst<n)&&Exist[lc_Vofst])
                    Exist[lc_Vofst]=0;
                else
                    return cnt;
            }
            if((p->rc_v)!='-')
            {
                idxT rc_Vofst=(idxT)((p->rc_v)-'0');
                if((rc_Vofst>=0)&&(rc_Vofst<n)&&Exist[rc_Vofst])
                    Exist[rc_Vofst]=0;
                else
                    return cnt;
            }
        }
        binTreNode **ptr=malloc(sizeof(binTreNode *)),**tmp=NULL;
        if(ptr)
        {
            for(char *p=Exist; p-Exist<n; ++p)
                if(*p)
                {
                    *ptr=T+(p-Exist);
                    break;
                }
            if(*ptr)
            {
                queNode *que=que_init();
                if(que&&(que_push(ptr,que)))
                    while(!que_isEmpty(&que))
                    {
                        ptr=que_getTop(que),(*ptr)->idx=++cnt;
                        if((*ptr)->lc_v!='-')
                        {
                            tmp=malloc(sizeof(binTreNode *));
                            if(tmp)
                            {
                                *tmp=T+(((*ptr)->lc_v)-'0');
                                if(!que_push(tmp,que))
                                    return 0;
                            }
                            else
                                return 0;
                        }
                        if((*ptr)->rc_v!='-')
                        {
                            tmp=malloc(sizeof(binTreNode *));
                            if(tmp)
                            {
                                *tmp=T+(((*ptr)->rc_v)-'0');
                                if(!que_push(tmp,que))
                                    return 0;
                            }
                            else
                                return 0;
                        }
                        que_pop(que);
                    }
                que_del(&que);
            }
        }
    }
    return cnt;
}

int binTre_minusIdx(const void *a,const void *b)
{
    return (int)((((binTreNode *)a)->idx)-(((binTreNode *)b)->idx));
}

int main()
{
    idxT n=0;
    scanf("%hd",&n);
    if((n>0)&&(n<=N_MAX))
    {
        binTreNode T[n];
        for(binTreNode *p=T; p-T<n; ++p)
            p->val=(valT)(p-T+'0'),getchar(),scanf("%c %c",&(p->lc_v),&(p->rc_v));
        if(binTre_asignIdx(T,n)==n)
        {
            qsort(T,n,sizeof(binTreNode),binTre_minusIdx);
            char flag=0;
            for(binTreNode *p=T; p-T<n; ++p)
                if((p->lc_v=='-')&&(p->rc_v=='-'))
                {
                    if(flag)
                        printf(" ");
                    else
                        flag=1;
                    printf("%c",p->val);
                }
        }
        else
            printf("ERROR\n");
    }
    return 0;
}
