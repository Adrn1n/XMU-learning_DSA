/*
3-4 Pop Sequence
Score 25
Author 陈越
Organization 浙江大学

Given a stack which can keep M numbers at most.  Push N numbers in the order of 1, 2, 3, ..., N and pop randomly.  You are supposed to tell if a given sequence of numbers is a possible pop sequence of the stack.  For example, if M is 5 and N is 7, we can obtain 1, 2, 3, 4, 5, 6, 7 from the stack, but not 3, 2, 1, 7, 5, 6, 4.
Input Specification:

Each input file contains one test case.  For each case, the first line contains 3 numbers (all no more than 1000): M (the maximum capacity of the stack), N (the length of push sequence), and K (the number of pop sequences to be checked).  Then K lines follow, each contains a pop sequence of N numbers.  All the numbers in a line are separated by a space.
Output Specification:

For each pop sequence, print in one line "YES" if it is indeed a possible pop sequence of the stack, or "NO" if not.
Sample Input:

5 7 5
1 2 3 4 5 6 7
3 2 1 7 5 6 4
7 6 5 4 3 2 1
5 6 4 3 7 2 1
1 7 6 5 4 3 2

Sample Output:

YES
NO
NO
YES
NO

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

char isValid_stackPop(const short A[],const short N,const short M)
{
    if((N>0)&&(M>0))
    {
        char isIn[N];
        for(char *p=isIn; p-isIn<N; ++p)
            *p=0;
        for(const short *p=A; p-A<N; ++p)
            if((*p>0)&&(*p<=N)&&(!isIn[*p-1]))
            {
                isIn[*p-1]=1;
                if(*p-(p-A)<=M)
                {
                    if(p-A<N-2)
                        for(const short *q=p+1; q-A<N-1; ++q)
                            if(*q<*p)
                                for(const short *r=q+1; r-A<N; ++r)
                                    if((*r<*p)&&(*r>*q))
                                        return 0;
                }
                else
                    return 0;
            }
            else
                return -1;
        return 1;
    }
    else
        return -1;
}

int main()
{
    short M=0,N=0,K=0;
    scanf("%hd%hd%hd",&M,&N,&K);
    while(K--)
    {
        short A[N];
        for(short *p=A; p-A<N; ++p)
            scanf("%hd",p);
        if(isValid_stackPop(A,N,M)>0)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
