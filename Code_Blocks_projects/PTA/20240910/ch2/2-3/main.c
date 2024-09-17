/*
2-3（二选一B） 两个有序序列的中位数
Score 25
Author DS课程组
Organization 浙江大学

已知有两个等长的非降序序列S1, S2, 设计函数求S1与S2并集的中位数。有序序列A_0​,A_1​,⋯,A_(N−1)​的中位数指A_((N−1)/2​)的值,即第⌊(N+1)/2⌋个数（A_0​为第1个数）。
输入格式:

输入分三行。第一行给出序列的公共长度N（0<N≤100000），随后每行输入一个序列的信息，即N个非降序排列的整数。数字用空格间隔。
输出格式:

在一行中输出两个输入序列的并集序列的中位数。
输入样例1:

5
1 3 5 7 9
2 3 4 5 6

输出样例1:

4

输入样例2:

6
-100 -10 1 1 1 1
-50 0 2 3 4 5

输出样例2:

1

Code Size Limit
16 KB
Time Limit
200 ms
Memory Limit
64 MB
Stack size limit
8192 KB
*/

/*
【编程题 2-3 两个有序序列的中位数 补充说明】

题目中“求S1与S2并集的中位数”的表述不够准确，应理解为“求S1与S2的归并序列的中位数”，即不需要也不应剔除掉S1与S2中的重复元素。

补充样例如下图：

2-3 两个有序序列的中位数 补充说明.png (./0eec24f4-4099-4b19-b02e-0b9ab536fa7e.png)
*/

#include <stdio.h>
#include <stdlib.h>

typedef int ele_type;
typedef int idx_type;

typedef struct SeqList_
{
    ele_type *Arr;
    idx_type n_max,n;
} SeqList;

typedef enum SeqList_return_type_ {OK,Null} SeqList_return_type;

SeqList *SeqList_Init(idx_type n_max)
{
    SeqList *const seqlist=malloc(sizeof(SeqList));
    seqlist->n_max=n_max,seqlist->n=0;
    seqlist->Arr=malloc(n_max*sizeof(ele_type));
    return seqlist;
}

SeqList *SeqList_Del(SeqList *const seqlist)
{
    if(seqlist)
    {
        seqlist->n_max=0,seqlist->n=0;
        free(seqlist->Arr);
        seqlist->Arr=NULL;
        free(seqlist);
    }
    return seqlist;
}

SeqList_return_type SeqList_ReadArr(SeqList *const seqlist)
{
    if(seqlist)
    {
        for(idx_type i=0; i<(seqlist->n_max); ++i)
        {
            scanf("%d",(seqlist->Arr)+i);
            ++(seqlist->n);
            char tmp=(char)(getchar());
            if(tmp=='\n')
                return OK;
        }
        return OK;
    }
    else
        return Null;
}

const ele_type* SeqList_Get_2_list_Mid(const SeqList *const A,const SeqList *const B)
{
    if(A&&B)
    {
        const ele_type *p=(A->Arr),*q=(B->Arr),*res=NULL;
        idx_type cnt=((A->n)+(B->n)+1)/2;
        while(cnt--)
            if(*p>*q)
                res=q++;
            else
                res=p++;
        return res;
    }
    else  if(A||B)
    {
        const SeqList *seqlist=(A?A:B);
        const ele_type *p=seqlist->Arr,*q=p;
        while(q<((seqlist->Arr)+(seqlist->n)))
            ++p,q+=2;
        return p;
    }
    else
        return NULL;
}

int main()
{
    idx_type N=0;
    scanf("%d",&N);
    SeqList *const A=SeqList_Init(N),*const B=SeqList_Init(N);
    SeqList_ReadArr(A),SeqList_ReadArr(B);
    printf("%d\n",*SeqList_Get_2_list_Mid(A,B));
    SeqList_Del(A),SeqList_Del(B);
    return 0;
}
