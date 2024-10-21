/*
3-7（二选一B组） 银行排队问题之单队列多窗口服务
Score 25
Author DS课程组
Organization 浙江大学

假设银行有K个窗口提供服务，窗口前设一条黄线，所有顾客按到达时间在黄线后排成一条长龙。当有窗口空闲时，下一位顾客即去该窗口处理事务。当有多个窗口可选择时，假设顾客总是选择编号最小的窗口。

本题要求输出前来等待服务的N位顾客的平均等待时间、最长等待时间、最后完成时间，并且统计每个窗口服务了多少名顾客。
输入格式:

输入第1行给出正整数N（≤1000），为顾客总人数；随后N行，每行给出一位顾客的到达时间T和事务处理时间P，并且假设输入数据已经按到达时间先后排好了顺序；最后一行给出正整数K（≤10），为开设的营业窗口数。这里假设每位顾客事务被处理的最长时间为60分钟。
输出格式:

在第一行中输出平均等待时间（输出到小数点后1位）、最长等待时间、最后完成时间，之间用1个空格分隔，行末不能有多余空格。

在第二行中按编号递增顺序输出每个窗口服务了多少名顾客，数字之间用1个空格分隔，行末不能有多余空格。
输入样例：

9
0 20
1 15
1 61
2 10
10 5
10 3
30 18
31 25
31 2
3

输出样例：

6.2 17 61
5 3 1

###感谢浙江财经大学王瑞洲、周甄陶同学修正测试数据！
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

typedef short idxT;
typedef double tmT;

typedef struct cstm_tm_dataT_
{
    tmT arr_t;
    tmT procs_t;
} cstm_tm_dataT;

typedef cstm_tm_dataT wd_tm_dataT;

typedef struct wTmInfo_dataT_
{
    tmT avg;
    tmT max;
    tmT last;
} wTmInfo_dataT;

char fetch_cstm_tm_data(cstm_tm_dataT *const cstm_tm_data)
{
    if(cstm_tm_data)
    {
        scanf("%lf%lf",&(cstm_tm_data->arr_t),&(cstm_tm_data->procs_t));
        return 1;
    }
    else
        return -1;
}

char print_wTmInfo(const wTmInfo_dataT *const info)
{
    if(info)
    {
        printf("%.1lf %.lf %.lf",info->avg,info->max,info->last);
        return 1;
    }
    else
        return -1;
}

char print_wd_servN(const wd_tm_dataT *const Time_wd,const idxT n,const idxT m)
{
    if(Time_wd)
    {
        for(const wd_tm_dataT (*p)[m]=(wd_tm_dataT(*)[m])Time_wd; p-(wd_tm_dataT(*)[m])Time_wd<n; ++p)
        {
            idxT cnt=0;
            for(const wd_tm_dataT *q=*p; q-(*p)<m; ++cnt,++q)
                if((q->arr_t)<0)
                    break;
            printf("%hd",cnt);
            if((p-(wd_tm_dataT(*)[m])Time_wd)<(n-1))
                printf(" ");
        }
        return 1;
    }
    else
        return -1;
}

char fetch_wTmInfo(wTmInfo_dataT *const res,wd_tm_dataT *const Time_wd,const idxT n,cstm_tm_dataT *const Time_cstm,const idxT m)
{
    if(res&&Time_wd&&Time_cstm&&(n>0)&&(m>=0))
    {
        (res->avg)=(res->max)=(res->last)=0;
        wd_tm_dataT *wd_next[n];
        for(wd_tm_dataT **p=wd_next; p-wd_next<n; ++p)
            *p=Time_wd+(p-wd_next)*m;
        for(cstm_tm_dataT *p=Time_cstm; p-Time_cstm<m; ++p)
        {
            if(p->procs_t>60)
                p->procs_t=60;
            wd_tm_dataT **ptr=wd_next;
            tmT Tm=-1;
            for(wd_tm_dataT **q=wd_next; q-wd_next<n; ++q)
                if((*q-Time_wd)==(q-wd_next)*m)
                {
                    (*q)->arr_t=p->arr_t,(*q)->procs_t=p->procs_t,++*q;
                    Tm=0;
                    break;
                }
                else if(((*q-Time_wd)>(q-wd_next)*m)&&((*q-Time_wd)<((q-wd_next+1)*m)))
                {
                    tmT tmp=((*q-1)->arr_t)+((*q-1)->procs_t);
                    if(tmp<=(p->arr_t))
                    {
                        (*q)->arr_t=p->arr_t,(*q)->procs_t=p->procs_t,++*q;
                        Tm=0;
                        break;
                    }
                    else if((Tm<0)||(tmp<Tm))
                        Tm=tmp,ptr=q;
                }
                else
                    return -1;
            if(Tm>0)
            {
                (*ptr)->arr_t=Tm,(*ptr)->procs_t=p->procs_t,++*ptr;
                Tm-=(p->arr_t);
                res->avg+=Tm;
                res->max=((res->max)<Tm)?Tm:(res->max);
            }
            else if(Tm<0)
                return -1;
            Tm+=(p->arr_t+p->procs_t);
            res->last=(Tm>(res->last))?Tm:(res->last);
        }
        (res->avg)/=m;
        return 1;
    }
    return -1;
}

int main()
{
    idxT N=0,K=0;
    scanf("%hd",&N);
    cstm_tm_dataT Time_cstm[N];
    for(cstm_tm_dataT *p=Time_cstm; p-Time_cstm<N; ++p)
        fetch_cstm_tm_data(p);
    scanf("%hd",&K);
    wd_tm_dataT Time_wd[K][N];
    for(wd_tm_dataT (*p)[N]=Time_wd; p-Time_wd<K; ++p)
        for(wd_tm_dataT *q=*p; q-*p<N; ++q)
            q->arr_t=q->procs_t=-1;
    wTmInfo_dataT wTmInfo= {0,0,0};
    if((fetch_wTmInfo(&wTmInfo,*Time_wd,K,Time_cstm,N)==1)&&(print_wTmInfo(&wTmInfo)==1)&&(printf("\n"))&&(print_wd_servN(*Time_wd,K,N)==1))
        printf("\n");
    else
        printf("ERROR\n");
    return 0;
}
