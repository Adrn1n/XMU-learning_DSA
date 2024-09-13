/*
1-7B（二选一） 减一运算B
Score 10
Author 郑旭玲
Organization 厦门大学

给定一个由正整数组成的非空数组，也就是一个正整数N(1≤N<10^1000)的各位数字，其中最高位数字存放在数组的首位， 且每个数组元素只存储一位数字。

请求出N-1对应的新数组并输出。

假设除了整数 0 之外，数组的首元素不会是零。
输入格式:

输入在一行中给出正整数N的各位数字，用空格隔开
输出格式:

输出N-1的各位数字，用空格隔开
输入样例：

2 8 6 6

输出样例：

2 8 6 5

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

typedef struct C_Node
{
    char val;
    struct C_Node *next;
} c_node;

c_node *c_node_push_back(const char val,c_node **const head,c_node **const tail)
{
    c_node *cur=malloc(sizeof(c_node));
    cur->val=val,cur->next=NULL;
    if(*tail)
        (*tail)->next=cur;
    *tail=cur;
    if(!(*head))
        *head=cur;
    return cur;
}

char c_node_pop_front(c_node **const head)
{
    if(*head)
    {
        c_node *tmp=(*head)->next;
        (*head)->val=0,(*head)->next=NULL;
        free(*head);
        *head=tmp;
        return 1;
    }
    else
        return 0;
}

char c_node_delete(c_node *head)
{
    while(c_node_pop_front(&head));
    return 0;
}

char c_node_Flip(c_node **const head,c_node **const tail)
{
    c_node *p=*head,*q,*tmp;
    if(p)
    {
        q=p->next;
        while(q)
        {
            tmp=q->next;
            q->next=p;
            p=q,q=tmp;
        }
        *tail=*head,(*tail)->next=NULL,*head=p;
    }
    return 0;
}

char Cal_tureVal(const char val,char *const CF)
{
    char res=(char)(val+(*CF));
    if(res<'0')
    {
        res+=10;
        *CF=-1;
    }
    else if(res>'9')
    {
        res-=10;
        *CF=1;
    }
    else
        *CF=0;
    return res;
}

long long Push_rest(c_node **const Res_head,c_node **const Res_tail,const c_node *rest,char *const CF)
{
    long long cnt=0;
    while(rest&&((rest->val)!='-'))
    {
        c_node_push_back(Cal_tureVal(rest->val,CF),Res_head,Res_tail);
        rest=rest->next,++cnt;
    }
    return cnt;
}

c_node *c_node_as_n_Subtract(c_node **Res_head,c_node **Res_tail,const c_node *a_head,const c_node *a_tail,const c_node *b_head,const c_node *b_tail);

c_node *c_node_as_n_Plus(c_node **const Res_head,c_node **const Res_tail,const c_node *const a_head,const c_node *const a_tail,const c_node *const b_head,const c_node *const b_tail)
{
    const c_node *p=a_head,*q=b_head;
    char sign=0,CF=0;
    if(a_head&&b_head)
    {
        if(((a_head->val)!='-')&&((b_head->val)!='-'))
            sign=1;
        else if(((a_head->val)=='-')&&((b_head->val)=='-'))
            sign=-1;
        else
        {
            if((a_head->val)=='-')
                c_node_as_n_Subtract(Res_head,Res_tail,b_head,b_tail,a_head->next,a_tail);
            else
                c_node_as_n_Subtract(Res_head,Res_tail,a_head,a_tail,b_head->next,b_tail);
        }
        if(sign)
        {
            c_node_Flip((c_node **)&a_head,(c_node **)&a_tail),c_node_Flip((c_node **)&b_head,(c_node **)&b_tail);
            p=a_head,q=b_head;
            while(p&&((p->val!='-'))&&q&&(q->val!='-'))
            {
                c_node_push_back(Cal_tureVal((char)((p->val)+(q->val)-'0'),&CF),Res_head,Res_tail);
                p=p->next,q=q->next;
            }
            Push_rest(Res_head,Res_tail,p,&CF);
            Push_rest(Res_head,Res_tail,q,&CF);
            if(CF>0)
                c_node_push_back((char)('0'+CF),Res_head,Res_tail);
            if((sign<0)&&((*Res_head)->val>'0'))
                c_node_push_back('-',Res_head,Res_tail);
            c_node_Flip((c_node **)&a_head,(c_node **)&a_tail),c_node_Flip((c_node **)&b_head,(c_node **)&b_tail);
            c_node_Flip(Res_head,Res_tail);
        }
    }
    else
    {
        Push_rest(Res_head,Res_tail,p,&CF);
        Push_rest(Res_head,Res_tail,q,&CF);
    }
    return *Res_head;
}

c_node *c_node_as_n_Subtract(c_node **const Res_head,c_node **const Res_tail,const c_node *const a_head,const c_node *const a_tail,const c_node *const b_head,const c_node *const b_tail)
{
    const c_node *p=a_head,*q=b_head;
    char sign=0,CF=0;
    if(a_head&&b_head)
    {
        if(((a_head->val)!='-')&&((b_head->val)!='-'))
        {
            while(p&&((p->val)!='-')&&q&&((q->val)!='-'))
            {
                if(!sign)
                {
                    if((p->val)>(q->val))
                        sign=1;
                    else if((p->val)<(q->val))
                        sign=-1;
                }
                p=p->next,q=q->next;
            }
            if(p&&((p->val)!='-'))
                sign=1;
            else if(q&&((q->val)!='-'))
            {
                sign=-1;
                c_node_as_n_Subtract(Res_head,Res_tail,b_head,b_tail,a_head,a_tail);
            }
            else if(sign<0)
                c_node_as_n_Subtract(Res_head,Res_tail,b_head,b_tail,a_head,a_tail);
            else if(!sign)
            {
                *Res_head=*Res_tail=malloc(sizeof(c_node));
                (*Res_head)->val='0',(*Res_head)->next=NULL;
                return *Res_head;
            }
        }
        else if(((a_head->val)=='-')&&((b_head->val)=='-'))
        {
            sign=-1;
            c_node_as_n_Subtract(Res_head,Res_tail,b_head->next,b_tail,a_head->next,a_tail);
        }
        else
        {
            if((a_head->val)!='-')
                c_node_as_n_Plus(Res_head,Res_tail,a_head,a_tail,b_head->next,b_tail);
            else
            {
                c_node b_sign;
                b_sign.val='-',b_sign.next=(c_node *)b_head;
                c_node_as_n_Plus(Res_head,Res_tail,a_head,a_tail,&b_sign,b_tail);
            }
        }
        if(sign>0)
        {
            c_node_Flip((c_node **)&a_head,(c_node **)&a_tail),c_node_Flip((c_node **)&b_head,(c_node **)&b_tail);
            p=a_head,q=b_head;
            while(p&&((p->val)!='-')&&q&&((q->val)!='-'))
            {
                c_node_push_back(Cal_tureVal((char)((p->val)-(q->val)+'0'),&CF),Res_head,Res_tail);
                p=p->next,q=q->next;
            }
            Push_rest(Res_head,Res_tail,p,&CF);
            if(q&&((q->val)!='-'))
                return NULL;
            c_node_Flip((c_node **)&a_head,(c_node **)&a_tail),c_node_Flip((c_node **)&b_head,(c_node **)&b_tail);
            c_node_Flip(Res_head,Res_tail);
        }
    }
    else
    {
        Push_rest(Res_head,Res_tail,p,&CF);
        if(Push_rest(Res_head,Res_tail,q,&CF))
            sign=-1;
    }
    if(sign)
    {
        if(sign<0)
        {
            if((*Res_tail)->val=='-')
                c_node_pop_front(Res_head);
            else
            {
                c_node *tmp=malloc(sizeof(c_node));
                tmp->val='-',tmp->next=*Res_head;
                *Res_head=tmp;
            }
        }
        c_node *tmp=NULL;
        p=*Res_head;
        if((*Res_head)->val=='-')
            tmp=*Res_head,p=p->next;
        while(p&&((p->val)=='0'))
            c_node_pop_front((c_node **)&p);
        if(tmp)
            tmp->next=(c_node *)p;
        else
            *Res_head=(c_node *)p;
    }
    return *Res_head;
}

long long c_node_PrintAll(const c_node *p)
{
    long long cnt=0;
    while(p)
    {
        printf("%c",p->val);
        p=p->next,++cnt;
    }
    return cnt;
}

int main()
{
    c_node *a_head=NULL,*a_tail=NULL,*b_head=NULL,*b_tail=NULL,*Res_head=NULL,*Res_tail=NULL;
    char digits=0;
    while(((digits=(char)(getchar()))!='\n')&&(digits!=EOF))
        if(digits!=' ')
            c_node_push_back(digits,&a_head,&a_tail);
    while(((digits=(char)(getchar()))!='\n')&&(digits!=EOF))
        if(digits!=' ')
            c_node_push_back(digits,&b_head,&b_tail);
    c_node_as_n_Plus(&Res_head,&Res_tail,a_head,a_tail,b_head,b_tail);
    c_node_PrintAll(Res_head);
    c_node_delete(Res_head);
    Res_head=NULL,Res_tail=NULL;
    printf("\n");
    c_node_as_n_Subtract(&Res_head,&Res_tail,a_head,a_tail,b_head,b_tail);
    c_node_PrintAll(Res_head);
    c_node_delete(Res_head);
    printf("\n");
    c_node_delete(a_head),c_node_delete(b_head);
    return 0;
}
