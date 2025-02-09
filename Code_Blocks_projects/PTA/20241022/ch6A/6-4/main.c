/*
6-4（拓展） 愿天下有情人都是失散多年的兄妹
Score 25
Author 陈越
Organization 浙江大学

呵呵。大家都知道五服以内不得通婚，即两个人最近的共同祖先如果在五代以内（即本人、父母、祖父母、曾祖父母、高祖父母）则不可通婚。本题就请你帮助一对有情人判断一下，他们究竟是否可以成婚？
输入格式：

输入第一行给出一个正整数N（2 ≤ N ≤10^4），随后N行，每行按以下格式给出一个人的信息：

本人ID 性别 父亲ID 母亲ID

其中ID是5位数字，每人不同；性别M代表男性、F代表女性。如果某人的父亲或母亲已经不可考，则相应的ID位置上标记为-1。

接下来给出一个正整数K，随后K行，每行给出一对有情人的ID，其间以空格分隔。

注意：题目保证两个人是同辈，每人只有一个性别，并且血缘关系网中没有乱伦或隔辈成婚的情况。
输出格式：

对每一对有情人，判断他们的关系是否可以通婚：如果两人是同性，输出Never Mind；如果是异性并且关系出了五服，输出Yes；如果异性关系未出五服，输出No。
输入样例：

24
00001 M 01111 -1
00002 F 02222 03333
00003 M 02222 03333
00004 F 04444 03333
00005 M 04444 05555
00006 F 04444 05555
00007 F 06666 07777
00008 M 06666 07777
00009 M 00001 00002
00010 M 00003 00006
00011 F 00005 00007
00012 F 00008 08888
00013 F 00009 00011
00014 M 00010 09999
00015 M 00010 09999
00016 M 10000 00012
00017 F -1 00012
00018 F 11000 00013
00019 F 11100 00018
00020 F 00015 11110
00021 M 11100 00020
00022 M 00016 -1
00023 M 10012 00017
00024 M 00022 10013
9
00021 00024
00019 00024
00011 00012
00022 00018
00001 00004
00013 00016
00017 00015
00019 00021
00010 00011

输出样例：

Never Mind
Yes
Never Mind
No
Yes
No
Yes
No
No

鸣谢用户 徐校波 修正数据！
Code Size Limit
16 KB
Time Limit
200 ms
Memory Limit
64 MB
Stack size limit
8192 KB
*/

#include <stdio.h>
#include <stdlib.h>

#define N_MAX 10000
#define ID_MAX 99999
#define STEP_MAX 5

typedef int idxT;
typedef char genT;

typedef struct perT_
{
    idxT f_id,m_id;
    genT gender;
} perT;

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

idxT per_mark(const idxT id,idxT *const Vis,const idxT n,const idxT cnt,idxT *const ansrt,idxT *const ansrt_cnt,queNode *const que)
{
    if(Vis&&que&&ansrt&&ansrt_cnt&&(n>0)&&(id>0)&&(id<=n)&&(cnt>0)&&(cnt<=n)&&(*ansrt_cnt>0)&&(*ansrt_cnt<=n))
    {
        if(Vis[id-1]==-1)
        {
            idxT *ptr=malloc(sizeof(idxT));
            if(ptr&&que_push(ptr,que))
                return Vis[(*ptr=id)-1]=cnt;
            else
                return -1;
        }
        else
        {
            Vis[id-1]=(Vis[id-1]>cnt)?Vis[id-1]:cnt;
            if(*ansrt_cnt>Vis[id-1])
                *ansrt=id,*ansrt_cnt=Vis[id-1];
            return Vis[id-1];
        }
    }
    return -1;
}

idxT per_expandParnt(const perT *const A,const idxT *const idPtr,idxT *const Vis,const idxT n,idxT *const ansrt,idxT *const ansrt_cnt,queNode *const que)
{
    if(A&&Vis&&que&&idPtr&&ansrt&&ansrt_cnt&&(n>0)&&(*idPtr>0)&&(*idPtr<=n)&&(*ansrt>=0)&&(*ansrt_cnt<=n))
    {
        idxT cnt=Vis[*idPtr-1]+1,f_id=A[*idPtr-1].f_id,m_id=A[*idPtr-1].m_id;
        if((f_id>0)&&(f_id<=n))
        {
            cnt=per_mark(f_id,Vis,n,cnt,ansrt,ansrt_cnt,que);
            if(cnt<0)
                return -1;
        }
        else if(f_id!=-1)
            return -1;
        if((m_id>0)&&(m_id<=n))
        {
            cnt=per_mark(m_id,Vis,n,Vis[*idPtr-1]+1,ansrt,ansrt_cnt,que);
            if(cnt<0)
                return -1;
        }
        else if(m_id!=-1)
            return -1;
        return cnt;
    }
    return -1;
}

idxT per_comAnsrt(const perT *const A,idxT *const Vis,const idxT n,const idxT id1,const idxT id2,const idxT step_max)
{
    idxT ansrt=-1,cnt=step_max;
    if(A&&Vis&&(n>0)&&(id1>0)&&(id1<=n)&&(id2>0)&&(id2<=n)&&(step_max>0))
    {
        idxT *idPtr1=malloc(sizeof(idxT)),*idPtr2=malloc(sizeof(idxT));
        if(idPtr1&&idPtr2)
        {
            *idPtr1=id1,*idPtr2=id2;
            queNode *que1=que_init(),*que2=que_init();
            if(que1&&que2&&que_push(idPtr1,que1)&&que_push(idPtr2,que2))
            {
                ansrt=0;
                for(idxT *p=Vis; p-Vis<n; ++p)
                    *p=-1;
                Vis[id1-1]=0,Vis[id2-1]=0;
                while((!que_isEmpty(&que1))||(!que_isEmpty(&que2)))
                {
                    if(!que_isEmpty(&que1))
                    {
                        idPtr1=que_getTop(que1);
                        if((Vis[*idPtr1-1]+1)<step_max)
                            if(per_expandParnt(A,idPtr1,Vis,n,&ansrt,&cnt,que1)<0)
                            {
                                que_del(&que1),que_del(&que2);
                                return -1;
                            }
                        que_pop(que1);
                    }
                    if(!que_isEmpty(&que2))
                    {
                        idPtr2=que_getTop(que2);
                        if((Vis[*idPtr2-1]+1)<step_max)
                            if(per_expandParnt(A,idPtr2,Vis,n,&ansrt,&cnt,que2)<0)
                            {
                                que_del(&que1),que_del(&que2);
                                return -1;
                            }
                        que_pop(que2);
                    }
                }
            }
            que_del(&que1),que_del(&que2);
        }
    }
    return ansrt;
}

int main()
{
    idxT N=0;
    char flag=1;
    scanf("%d",&N);
    if((N>0)&&(N<=N_MAX))
    {
        perT A[ID_MAX];
        for(perT *p=A; p-A<ID_MAX; ++p)
            p->gender=0,p->f_id=-1,p->m_id=-1;
        for(idxT i=0; i<N; ++i)
        {
            idxT id=0,f_id=0,m_id=0;
            scanf("%d",&id),getchar(),scanf("%c%d%d",&(A[id-1].gender),&f_id,&m_id),A[id-1].f_id=f_id,A[id-1].m_id=m_id;
            if((f_id>0)&&(f_id<=ID_MAX))
            {
                if(!A[f_id-1].gender)
                    A[f_id-1].gender='M';
                else if(A[f_id-1].gender!='M')
                {
                    flag=0;
                    break;
                }
            }
            else if(f_id!=-1)
            {
                flag=0;
                break;
            }
            if((m_id>0)&&(m_id<=ID_MAX))
            {
                if(!A[m_id-1].gender)
                    A[m_id-1].gender='F';
                else if(A[m_id-1].gender!='F')
                {
                    flag=0;
                    break;
                }
            }
            else if(m_id!=-1)
            {
                flag=0;
                break;
            }
        }
        if(flag)
        {
            long long K=0;
            scanf("%lld",&K);
            if(K>0)
            {
                flag=0;
                idxT F[2*K];
                for(idxT *p=F; p-F<2*K; p+=2)
                    scanf("%d%d",p,p+1);
                for(idxT *p=F; p-F<2*K; p+=2)
                    if((A[*p-1].gender)==(A[*(p+1)-1].gender))
                        printf("Never Mind\n");
                    else
                    {
                        idxT Vis[ID_MAX],ansrt=0;
                        ansrt=per_comAnsrt(A,Vis,ID_MAX,*p,*(p+1),STEP_MAX);
                        if(ansrt>0)
                            printf("No\n");
                        else if(!ansrt)
                            printf("Yes\n");
                        else
                            printf("ERROR\n");
                    }
            }
        }
        else
            flag=1;
    }
    if(flag)
        printf("ERROR\n");
    return 0;
}
