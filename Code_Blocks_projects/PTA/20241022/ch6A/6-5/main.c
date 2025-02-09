/*
6-5（拓展） Tree Traversals Again
Score 25
Author 陈越
Organization 浙江大学

An inorder binary tree traversal can be implemented in a non-recursive way with a stack.  For example, suppose that when a 6-node binary tree (with the keys numbered from 1 to 6) is traversed, the stack operations are: push(1); push(2); push(3); pop(); pop(); push(4); pop(); pop(); push(5); push(6); pop(); pop().  Then a unique binary tree (shown in Figure 1) can be generated from this sequence of operations.  Your task is to give the postorder traversal sequence of this tree.

Figure 1 (./30.jpg)
Input Specification:

Each input file contains one test case.  For each case, the first line contains a positive integer N (≤30) which is the total number of nodes in a tree (and hence the nodes are numbered from 1 to N).  Then 2N lines follow, each describes a stack operation in the format: "Push X" where X is the index of the node being pushed onto the stack; or "Pop" meaning to pop one node from the stack.
Output Specification:

For each test case, print the postorder traversal sequence of the corresponding tree in one line.  A solution is guaranteed to exist.  All the numbers must be separated by exactly one space, and there must be no extra space at the end of the line.
Sample Input:

6
Push 1
Push 2
Push 3
Pop
Pop
Push 4
Pop
Pop
Push 5
Push 6
Pop
Pop

Sample Output:

3 4 2 6 5 1

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
#include <string.h>

#define N_MAX 30
#define INPUT_MAX 5

typedef short idxT;
typedef short valT;

typedef struct binTreNode_
{
    valT val;
    struct binTreNode_ *l_chil,*r_chil,*par;
} binTreNode;

idxT binTre_preOrdinOrdBuldTre(binTreNode *const T,const valT *const preOrdTre,const idxT n,const idxT *const preOrd2inOrd)
{
    idxT cnt=-1;
    if(T&&preOrdTre&&preOrd2inOrd&&(n>0))
    {
        char Vis[n],flag=1;
        for(char *p=Vis; p-Vis<n; ++p)
            *p=0;
        for(const idxT *p=preOrd2inOrd; p-preOrd2inOrd<n; ++p)
            if((*p<0)||(*p>=n)||Vis[*p])
            {
                flag=0;
                break;
            }
            else
                Vis[*p]=1;
        if(flag)
        {
            for(binTreNode *p=T; p-T<n; ++p)
                p->val=-1,p->par=p->l_chil=p->r_chil=NULL;
            T->val=*preOrdTre,T->par=T,cnt=1;
            const idxT *ptr_idx=preOrd2inOrd;
            for(idxT i=1; i<n; ++i,++cnt)
                if((ptr_idx>=preOrd2inOrd)&&(ptr_idx<preOrd2inOrd+n))
                {
                    T[i].val=preOrdTre[i];
                    idxT j=(idxT)(i-1);
                    if(*ptr_idx==j)
                    {
                        for(T[j].l_chil=NULL;; j=(idxT)(T[j].par-T))
                            if((ptr_idx>=preOrd2inOrd)&&(ptr_idx<preOrd2inOrd+n))
                            {
                                if(*ptr_idx==j)
                                {
                                    if(*++ptr_idx>j)
                                        break;
                                    else
                                        T[j].r_chil=NULL;
                                }
                            }
                            else
                                return -1;
                        T[j].r_chil=T+i,T[i].par=T+j;
                    }
                    else
                        T[j].l_chil=T+i,T[i].par=T+j;
                }
                else
                    return -1;
        }
    }
    return cnt;
}

int main()
{
    idxT N=0;
    char flag=1;
    scanf("%hd",&N),getchar();
    if((N>0)&&(N<=N_MAX))
    {
        valT A[N],*ptr_A=A;
        idxT preOrd2inOrd[N],Stack[N],*ptr_idx=preOrd2inOrd,*stack_top=Stack;
        for(idxT i=0,cnt=0; i<2*N; ++i)
        {
            char I[INPUT_MAX+1]= {0};
            fgets(I,INPUT_MAX+1,stdin);
            if(!strcmp(I,"Push "))
                if((stack_top>=Stack)&&(ptr_A<(A+N)))
                    scanf("%hd",ptr_A++),*stack_top++=cnt++,getchar();
                else
                {
                    flag=0;
                    break;
                }
            else if(!strncmp(I,"Pop",3))
                if((stack_top>Stack)&&(ptr_A<=(A+N))&&(ptr_idx>=preOrd2inOrd)&&(ptr_idx<(preOrd2inOrd+N)))
                    --stack_top,*ptr_idx++=*stack_top;
                else
                {
                    flag=0;
                    break;
                }
            else
            {
                flag=0;
                break;
            }
        }
        if(flag)
        {
            binTreNode T[N],*ptr_T=T;
            if(binTre_preOrdinOrdBuldTre(T,A,N,preOrd2inOrd)==N)
            {
                for(stack_top=Stack; stack_top-Stack<N; ++stack_top)
                    *stack_top=0;
                while(ptr_T)
                {
                    idxT idx=(idxT)(ptr_T-T);
                    if((!Stack[idx])&&(ptr_T->l_chil))
                        ptr_T=ptr_T->l_chil,Stack[idx]=1;
                    else if((Stack[idx]!=2)&&(ptr_T->r_chil))
                        ptr_T=ptr_T->r_chil,Stack[idx]=2;
                    else
                    {
                        printf("%hd",ptr_T->val);
                        if(ptr_T==T)
                        {
                            printf("\n");
                            break;
                        }
                        else
                        {
                            printf(" ");
                            ptr_T=ptr_T->par;
                        }
                    }
                }
                flag=0;
            }
        }
        else
            flag=1;
    }
    if(flag)
        printf("ERROR\n");
    return 0;
}
