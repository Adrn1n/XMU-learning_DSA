/*
4-5（拓展） 接话茬
Score 25
Author 陈浩川
Organization 厦门大学

小CC最喜欢的就是接话茬，别人说一句，小CC就会接着他的话尾巴继续说下去，然后告诉他这是“顶针”修辞手法，活活将人气死。小XX也喜欢接话茬，每天都要与小CC比较技艺。然而无论是谁，都会被他们活活气死，因此两人总是难决胜负。后来小CC和小XX一起上了厦门大学，学习了校选课《接话茬数学原理与杠精的自我修养》，他们决定对两人的接话茬水平进行定量评估。

他们约定比赛规则如下，随机找一个倒霉的路人，路人说一句话，他们一起来接，他们接的话的前缀可以作为路人说的话后缀的长度就是那句话的水平。比如，别人说“abbbaabbc”，小CC接了一句“abbcefagd”，他所说的话的前缀“abbc”正是路人所说的话的后缀，长度为4，那么小CC的水平就是4；如果小XX说的是“xbbcadf”，无法构成路人所说的话的后缀，因此水平只有0。

现在，他们的比赛正式开始，由你来写一个程序充当裁判。
输入格式:

共三行，每行是一句话，长度均不超过10^6。

第一行是路人说的话。第二行是小CC说的话。第三行是小XX说的话。
输出格式:

仅一行，输出小CC和小XX接的话的水平，以空格分割，行末没有多余空格，以换行结束。
输入样例:

abbaabbc
abbc
xbb

输出样例:

4 0

Code Size Limit
16 KB
Time Limit
50 ms
Memory Limit
64 MB
Stack size limit
8192 KB
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_N_Arr 150000

typedef int idxT;

idxT KMP_getNext(const char **const Next,const char *const str)
{
    idxT cnt=0;
    if(Next&&str&&(*str))
    {
        for(const char *p=str; *p; ++p)
            if(p==str)
                *Next=NULL,++cnt;
            else
            {
                const idxT idx=(idxT)(p-str);
                const char *ptr=Next[idx-1];
                while(ptr&&(*ptr!=*(p-1)))
                    ptr=Next[ptr-str];
                if(ptr)
                    ++ptr;
                else
                    ptr=str;
                Next[idx]=ptr,++cnt;
            }
    }
    return cnt;
}

idxT str_MaxOvrlp(const char *const A,const char *const B,const char *const B_end)
{
    idxT max=0;
    if(A&&(*A)&&B&&(*B)&&(B<B_end))
    {
        const idxT len_B=(idxT)(B_end-B);
        const char *Next[len_B+1],*ptr=NULL;
        KMP_getNext(Next,B);
        for(ptr=Next[len_B-1]; ptr&&(*ptr!=*(B_end-1));)
            ptr=Next[ptr-B];
        if(ptr)
            ++ptr;
        Next[len_B]=ptr;
        for(const char *p=A,*q=B;; ++p)
            if(*p&&(*q)&&(*p==*q))
                ++q;
            else
            {
                if(*p)
                {
                    q=Next[q-B];
                    while(q&&(*q!=*p))
                        q=Next[q-B];
                    if(q)
                        ++q;
                    else
                        q=B;
                }
                else
                {
                    max=(idxT)(q-B);
                    break;
                }
            }
    }
    return max;
}

int main()
{
    char S[MAX_N_Arr]= {0},CC[MAX_N_Arr]= {0},XX[MAX_N_Arr]= {0},*CC_end=CC,*XX_end=XX;
    scanf("%s%s%s",S,CC,XX);
    for(; *CC_end&&(CC_end-CC<MAX_N_Arr); ++CC_end);
    for(; *XX_end&&(XX_end-XX<MAX_N_Arr); ++XX_end);
    printf("%d %d\n",str_MaxOvrlp(S,CC,CC_end),str_MaxOvrlp(S,XX,XX_end));
    return 0;
}
