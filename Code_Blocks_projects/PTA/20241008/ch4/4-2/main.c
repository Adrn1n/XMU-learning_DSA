/*
4-2 字符串分割拼接
Score 20
Author 陈浩川
Organization 厦门大学

很多人抱怨C中的字符串太过难用，其接口太过老旧。例如，字符串的分割(strtok)、链接(strcat)。这一次，我们自己动手实现更现代接口split和join。

函数split接受分隔符c，可以将字符串以字符p为分割成若干个数组，例如"abbc"，如果以'b'进行split，会变成数组["a", "", "c"]，而以'c'划分则会变成["abb", ""]。

函数join接受连接字符串s将一个字符串数组中的元素，两两相连，构成一个新的字符串，例如["I",  "U"]如果用字符串" love "链接，会得到"I love U"；而["abc"]中只有一个元素，因此无论用什么连接，始终得到"abc"本身。

注意：不允许使用编程语言内置的字符串操作。如C中的strtok、strcat，Java、Python中的split、join等。
输入格式:

输入包含两行。

第一行为原始字符串，长度不超过10^3，不需要读入最后的换行。这一行的输入可能包含有空格、制表符。

第二行依次为分割字符p和连接字符串s。可以假设，p不是一个空格、制表符或者换行。在p以及一个空格后的全部字符（可能包含空格、制表符，不包括换行）均属于连接字符串s。
输出格式:

第一行输出使用p分割后的字符串数组，字符串使用双引号包围，两两之间以逗号和空格分隔，数组前后需要有左方括号和右方括号，以换行结束。
第二行输出使用p分割后再使用s链接的字符串，以换行结束。
输入样例:

abbc
b  x y

输出样例:

["a", "", "c"]
a x y  x y c

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

#define MAX_N_Arr 100000
#define DELIM_c (-1)

typedef int idxT;

char *split(char *const str,const char delim)
{
    if(str)
        for(char *p=str; *p; ++p)
            if(*p==delim)
                *p=DELIM_c;
    return str;
}

char *join(char *const str,const char *const s,const idxT max_n,const char delim)
{
    if(str&&s&&(max_n>1))
    {
        char Tmp[max_n];
        for(char *p=str,*q=Tmp; (p-str<max_n)&&(q-Tmp<max_n); ++p)
            if(*p==delim)
                for(const char *ptr=s; *ptr; ++q,++ptr)
                    if((q-Tmp)<(max_n-1))
                        *q=*ptr;
                    else
                    {
                        *q=0;
                        break;
                    }
            else
            {
                if((q-Tmp)<(max_n-1))
                    *q++=*p;
                else
                {
                    *q=0;
                    break;
                }
                if(!(*p))
                    break;
            }
        for(char *p=str,*q=Tmp; (p-str<max_n)&&(q-Tmp<max_n); ++p,++q)
            if(!(*p=*q))
                break;
    }
    return str;
}

idxT Print_split_str(const char *const str,const char delim)
{
    idxT cnt=0;
    char flag=1;
    printf("[");
    for(const char *p=str; p; ++p)
        if(*p)
        {
            if(flag)
                printf("\""),flag=0,++cnt;
            if(*p!=delim)
                printf("%c",*p);
            else
                printf("\", "),flag=1;
        }
        else
        {
            if(p!=str)
            {
                printf("\"");
                if(flag)
                    printf("\""),++cnt;
            }
            break;
        }
    printf("]");
    return cnt;
}

int main()
{
    char Org[MAX_N_Arr]= {0},p=0,S[MAX_N_Arr]= {0};
    scanf("%[^\n]",Org),getchar();
    scanf("%c",&p),getchar();
    scanf("%[^\n]",S),getchar();
    split(Org,p);
    Print_split_str(Org,DELIM_c),printf("\n");
    join(Org,S,MAX_N_Arr,DELIM_c);
    printf("%s\n",Org);
    return 0;
}
