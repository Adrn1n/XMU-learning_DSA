/*
3-6（二选一A组） 输出全排列
Score 20
Author DS课程组
Organization 浙江大学

请编写程序输出前n个正整数的全排列（n<10），并通过9个测试用例（即n从1到9）观察n逐步增大时程序的运行时间。
输入格式:

输入给出正整数n（<10）。
输出格式:

输出1到n的全排列。每种排列占一行，数字间无空格。排列的输出顺序为字典序，即序列a1​,a2​,⋯,an​排在序列b1​,b2​,⋯,bn​之前，如果存在k使得a1​=b1​,⋯,ak​=bk​ 并且 ak+1​<bk+1​。
输入样例：

3

输出样例：

123
132
213
231
312
321

Code Size Limit
16 KB
Time Limit
3500 ms
Memory Limit
64 MB
Stack size limit
8192 KB
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char data_type;
typedef short idx_type;
typedef int cnt_type;
typedef char size_type;

typedef struct Node_
{
    void *data;
    struct Node_ *next;
} Node;

Node *Stack_push(Node **const Top,const void *const data,const size_type size)
{
    if(Top)
    {
        Node *node=malloc(sizeof(Node));
        node->data=malloc(size),memcpy(node->data,data,size),node->next=*Top;
        return (*Top=node);
    }
    else
        return NULL;
}

Node *Stack_pop(Node **const Top)
{
    if(Top)
    {
        if(*Top)
        {
            Node *tmp=*Top;
            *Top=tmp->next;
            free(tmp->data),free(tmp);
        }
        return *Top;
    }
    return NULL;
}

Node *Stack_del(Node **Top)
{
    while(Stack_pop(Top));
    return (*Top=NULL);
}

Node *Stack_flip(Node **Top)
{
    if(Top)
    {
        if((*Top)&&((*Top)->next))
            for(Node *p=*Top,*q=p->next; q;)
            {
                Node *tmp=q->next;
                q->next=p;
                if(p==*Top)
                    p->next=NULL;
                p=q,q=tmp;
                if(!q)
                {
                    *Top=p;
                    break;
                }
            }
        return *Top;
    }
    return NULL;
}

cnt_type print_ans(const Node *Top,const idx_type n)
{
    cnt_type cnt=0;
    while(Top)
    {
        for(data_type *p=Top->data; p-(data_type *)(Top->data)<n; ++p)
            printf("%c",*p+'0');
        Top=Top->next;
        printf("\n");
        ++cnt;
    }
    return cnt;
}

Node *mk_A_n_m(Node **const Res,const idx_type n,const idx_type m)
{
    *Res=NULL;
    data_type Table[m];
    char Used[n];
    for(idx_type i=0; i<n; ++i)
    {
        if(i<m)
            Table[i]=0;
        Used[i]=0;
    }
    idx_type top=0;
    do
        if((top>=0)&&(top<m))
        {
            char flag=1;
            data_type *p=Table+top;
            if((*p>=0)&&(*p<=n))
            {
                if(*p>0)
                {
                    if(Used[*p-1])
                        Used[*p-1]=0;
                    else
                        return NULL;
                }
            }
            else
                return NULL;
            for(++*p; *p<=n; ++*p)
                if(!Used[*p-1])
                {
                    if(top==m-1)
                        Stack_push(Res,Table,(size_type)(n*sizeof(data_type)));
                    else
                    {
                        Used[*p-1]=1;
                        ++top,flag=0;
                        break;
                    }
                }
            if(flag)
                Table[top--]=0;
        }
        else
            return NULL;
    while(top>=0);
    Stack_flip(Res);
    return *Res;
}

int main()
{
    idx_type n=0;
    scanf("%hd",&n);
    Node *Ans=NULL;
    mk_A_n_m(&Ans,n,n);
    if(print_ans(Ans,n)<0)
        printf("ERROR\n");
    Stack_del(&Ans);
    return 0;
}
