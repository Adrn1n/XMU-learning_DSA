/*
4-1（拓展，基础） 字符串的连接
Score 15
Author C课程组
Organization 浙江大学

本题要求实现一个函数，将两个字符串连接起来。
函数接口定义：

char *str_cat( char *s, char *t );

函数str_cat应将字符串t复制到字符串s的末端，并且返回字符串s的首地址。
裁判测试程序样例：

#include <stdio.h>

#include <string.h>


#define MAXS 10


char *str_cat( char *s, char *t );


int main()

{

    char *p;

    char str1[MAXS+MAXS] = {'\0'}, str2[MAXS] = {'\0'};



    scanf("%s%s", str1, str2);

    p = str_cat(str1, str2);

    printf("%s\n%s\n", p, str1);



    return 0;

}


/* 你的代码将被嵌在这里 */
/*

输入样例：

abc
def

输出样例：

abcdef
abcdef

Code Size Limit
16 KB
Time Limit
400 ms
Memory Limit
64 MB
*/

#include <stdio.h>
#include <string.h>

#define MAXS 10

char *str_cat( char *s, char *t );

int main()
{
    char *p;
    char str1[MAXS+MAXS] = {'\0'}, str2[MAXS] = {'\0'};

    scanf("%s%s", str1, str2);
    p = str_cat(str1, str2);
    printf("%s\n%s\n", p, str1);

    return 0;
}

/* 你的代码将被嵌在这里 */
char *str_cat(char *s,char *t)
{
    char flag=0;
    for(char *p=s,*q=t; p-s<2*MAXS; ++p)
        if(flag)
            *p=*q++;
        else if(!(*p))
            *p=*q++,flag=1;
    return s;
}
