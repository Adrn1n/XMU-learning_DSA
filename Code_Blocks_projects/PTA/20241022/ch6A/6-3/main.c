/*
6-3（二选一） 树的同构
Score 25
Author 陈越
Organization 浙江大学
给定两棵树  T_1 和 T_2。如果 T_1 可以通过若干次左右孩子互换就变成 T_2，则我们称两棵树是“同构”的。例如图1给出的两棵树就是同构的，因为我们把其中一棵树的结点A、B、G的左右孩子互换后，就得到另外一棵树。而图2就不是同构的。

fig1.jpg (./0c8bbacf-d64e-4c6d-8d4e-1249e33fb0b1.jpg)
图1

(./29(.jpg))
图2
现给定两棵树，请你判断它们是否是同构的。

输入格式:
输入给出2棵二叉树的信息。对于每棵树，首先在一行中给出一个非负整数 n (≤10)，即该树的结点数（此时假设结点从 0 到 n−1 编号）；随后 n 行，第 i 行对应编号第 i 个结点，给出该结点中存储的 1 个英文大写字母、其左孩子结点的编号、右孩子结点的编号。如果孩子结点为空，则在相应位置上给出 “-”。给出的数据间用一个空格分隔。注意：题目保证每个结点中存储的字母是不同的。

输出格式:
如果两棵树是同构的，输出“Yes”，否则输出“No”。

输入样例1（对应图1）：
8
A 1 2
B 3 4
C 5 -
D - -
E 6 -
G 7 -
F - -
H - -
8
G - 4
B 7 6
F - -
A 5 1
H - -
C 0 -
D - -
E 2 -
输出样例1:
Yes
输入样例2（对应图2）：
8
B 5 7
F - -
A 0 3
C 6 -
H - -
D - -
G 4 -
E 1 -
8
D 6 -
B 5 -
E - -
H - -
C 0 2
G - 3
F - -
A 1 4
输出样例2:
No
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
    valT val;
    idxT lc_idx,rc_idx;
} binTreNode;

idxT binTre_getIn(binTreNode *const T,const idxT n)
{
    idxT cnt=0;
    for(binTreNode *p=T; p-T<n; ++cnt,++p)
    {
        char l=0,r=0;
        scanf("%c %c %c",&(p->val),&l,&r),getchar();
        if(l=='-')
            p->lc_idx=-1;
        else
            p->lc_idx=(short)(l-'0');
        if(r=='-')
            p->rc_idx=-1;
        else
            p->rc_idx=(short)(r-'0');
    }
    return cnt;
}

char binTre_isIsomor(const binTreNode *const T1,const idxT n1,const binTreNode *const T2,const idxT n2)
{
    if(T1&&T2&&(n1>=0)&&(n2>=0))
    {
        if(n1==n2)
            for(const binTreNode *p=T1,*q=T2; p-T1<n1; q=T2,++p)
            {
                for(; q-T2<n2; ++q)
                    if((p->val)==(q->val))
                    {
                        const idxT lc_idx1=p->lc_idx,rc_idx1=p->rc_idx,lc_idx2=q->lc_idx,rc_idx2=q->rc_idx;
                        if((lc_idx1<n1)&&(rc_idx1<n1)&&(lc_idx2<n2)&&(rc_idx2<n2))
                        {
                            if((lc_idx1<0)&&(lc_idx2<0))
                            {
                                if((rc_idx1>=0)&&(rc_idx2>=0))
                                {
                                    if((T1[rc_idx1].val)!=(T2[rc_idx2].val))
                                        return 0;
                                }
                                else if((rc_idx1>=0)||(rc_idx2>=0))
                                    return 0;
                            }
                            else if(lc_idx1<0)
                            {
                                if((rc_idx1<0)||(rc_idx2>=0)||((T1[rc_idx1].val)!=(T2[lc_idx2].val)))
                                    return 0;
                            }
                            else if(lc_idx2<0)
                            {
                                if((rc_idx1>=0)||(rc_idx2<0)||((T1[lc_idx1].val)!=(T2[rc_idx2].val)))
                                    return 0;
                            }
                            else
                            {
                                if((rc_idx1<0)&&(rc_idx2<0))
                                {
                                    if((T1[lc_idx1].val)!=(T2[lc_idx2].val))
                                        return 0;
                                }
                                else if((rc_idx1<0)||(rc_idx2<0))
                                    return 0;
                                else
                                {
                                    if((((T1[lc_idx1].val)!=(T2[lc_idx2].val))||((T1[rc_idx1].val)!=(T2[rc_idx2].val)))&&(((T1[lc_idx1].val)!=(T2[rc_idx2].val))||((T1[rc_idx1].val)!=(T2[lc_idx2].val))))
                                        return 0;
                                }
                            }
                        }
                        else
                            return -1;
                        break;
                    }
                if(q-T2>=n2)
                    return 0;
            }
        else
            return 0;
        return 1;
    }
    return -1;
}

int main()
{
    idxT n1=0,n2=0;
    char flag=1;
    scanf("%hd",&n1),getchar();
    if((n1>=0)&&(n1<=N_MAX))
    {
        binTreNode T1[n1];
        if(binTre_getIn(T1,n1)==n1)
        {
            scanf("%hd",&n2),getchar();
            if((n2>=0)&&(n2<=N_MAX))
            {
                binTreNode T2[n2];
                if(binTre_getIn(T2,n2)==n2)
                {
                    flag=0;
                    if(binTre_isIsomor(T1,n1,T2,n2))
                        printf("Yes\n");
                    else
                        printf("No\n");
                }
            }
        }
    }
    if(flag)
        printf("ERROR\n");
    return 0;
}
