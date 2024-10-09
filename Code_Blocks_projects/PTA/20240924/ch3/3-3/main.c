/*
3-3（拓展） 表达式转换
Score 25
Author DS课程组
Organization 浙江大学

算术表达式有前缀表示法、中缀表示法和后缀表示法等形式。日常使用的算术表达式是采用中缀表示法，即二元运算符位于两个运算数中间。请设计程序将中缀表达式转换为后缀表达式。
输入格式:

输入在一行中给出不含空格的中缀表达式，可包含+、-、*、/以及左右括号()，表达式不超过20个字符。
输出格式:

在一行中输出转换后的后缀表达式，要求不同对象（运算数、运算符号）之间以空格分隔，但结尾不得有多余空格。
输入样例:

2+3*(7-4)+8/4

输出样例:

2 3 7 4 - * + 8 4 / +

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

#define N_MAX 23 //第2组测试数据(嵌套括号)疑似超过最大输入表达式长度20, 实测需要23恰好通过

char isOP_prior(char a,char b)
{
    if(((a=='*')||(a=='/'))&&((b=='+')||(b=='-')))
        return 1;
    else
        return 0;
}

char *push_OPs(char cur_op,char *OPTR,short *Top_OPTR,char *Dest,short *Top_dest)
{
    char *res=Dest+(*Top_dest);
    while((*Top_OPTR>=0)&&(OPTR[*Top_OPTR]!='(')&&(!isOP_prior(cur_op,OPTR[*Top_OPTR])))
        Dest[++(*Top_dest)]=' ',Dest[++(*Top_dest)]=OPTR[(*Top_OPTR)--],OPTR[(*Top_OPTR)+1]=0;
    return res;
}

int main()
{
    char In[N_MAX+1]= {0},Res[2*N_MAX]= {0},OPTR[N_MAX]= {0},flag=1,flag_d=0;
    short Top_Res=-1,Top_OPTR=-1;
    scanf("%s",In);
    for(const char *p=In; (p-In<N_MAX)&&(*p); ++p)
        if((((*p>='0')&&(*p<='9'))||(*p=='.'))||(((*p=='+')||(*p=='-'))&&((p==In)||(*(p-1)=='('))&&(p<In+N_MAX-1)&&(*(p+1)>='0')&&(*(p+1)<='9')))
        {
            if(*p=='+') //第3组测试数据(运算数前有正负号)新增要求输入的数前正号省略
            {
                if(Top_Res>=0)
                    Res[++Top_Res]=' ';
                continue;
            }
            if(*p=='.')
            {
                if((!flag_d)&&(p<In+N_MAX-1)&&(*(p+1)>='0')&&(*(p+1)<='9'))
                    flag_d=1;
                else
                {
                    flag=0;
                    break;
                }
            }
            if((Top_Res>=0)&&(((*(p-1)<'0')||(*(p-1)>'9'))&&(*(p-1)!='.'))&&(((*(p-1)!='+')&&(*(p-1)!='-'))||((p>In+1)&&(*(p-2)!='('))))
                Res[++Top_Res]=' ';
            Res[++Top_Res]=*p;
        }
        else if(((*p=='+')||(*p=='-')||(*p=='*')||(*p=='/'))&&((p>In)&&(((*(p-1)>='0')&&(*(p-1)<='9'))||(*(p-1)==')'))))
        {
            push_OPs(*p,OPTR,&Top_OPTR,Res,&Top_Res);
            OPTR[++Top_OPTR]=*p;
            flag_d=0;
        }
        else if((*p=='(')&&((p==In)||((*(p-1)=='+')||(*(p-1)=='-')||(*(p-1)=='*')||(*(p-1)=='/')||(*(p-1)=='('))))
            OPTR[++Top_OPTR]=*p,flag_d=0;
        else if((*p==')')&&(p>In)&&(((*(p-1)>='0')&&(*(p-1)<='9'))||(*(p-1)==')'))&&(Top_OPTR>=0))
        {
            push_OPs(*p,OPTR,&Top_OPTR,Res,&Top_Res);
            if((Top_OPTR>=0)&&(OPTR[Top_OPTR]=='('))
                OPTR[Top_OPTR--]=0,flag_d=0;
            else
            {
                flag=0;
                break;
            }
        }
        else
        {
            flag=0;
            break;
        }
    if(flag&&(Top_OPTR>=0))
    {
        push_OPs(')',OPTR,&Top_OPTR,Res,&Top_Res);
        if(Top_OPTR>=0)
            flag=0;
    }
    if(flag&&(Top_OPTR==(-1)))
        printf("%s\n",Res);
    else
        printf("ERROR\n");
    return 0;
}
