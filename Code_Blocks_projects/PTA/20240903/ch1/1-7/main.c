/*
1-7（二选一） 减一运算
Score 20
Author 郑旭玲
Organization 厦门大学

给定一个由正整数组成的非空数组，也就是一个大于0的自然数N的各位数字，其中最高位数字存放在数组的首位， 且每个数组元素只存储一位数字。

本题要求实现一个函数，在N的基础上减一，返回一个新的数组。

假设除了整数 0 之外，数组的首元素不会是零。
函数接口定义：

int* MinusOne(int *digits, int digitsSize, int *returnSize)

其中 ，digits是用户传入的数组，即N的各位数字，digitsSize 是该数组的大小，即N的位数；函数返回N-1后对应的新数组，*returnSize 是该数组的大小。

注意：返回的数组必须是通过动态分配内存建立的，且由主程序负责释放。
裁判测试程序样例：

#include <stdio.h>

#include <stdlib.h>


int *GetDigits(int *digitsSize);  /* 由裁判实现，略去不表 */

/*
int* MinusOne(int *digits, int digitsSize, int *returnSize);


int main()

{

    int *digits, *returnDigits, digitsSize, returnSize,i;


    digits = GetDigits(&digitsSize);

    returnDigits=MinusOne(digits, digitsSize, &returnSize);

    for (i=0;i<returnSize;i++)

        {

        printf("%d ", returnDigits[i]);

    }

        printf("\n");

    free(digits);

    free(returnDigits);


    return 0;

}


int *GetDigits(int *digitsSize)

{

    int *res,i;

    char s[2001];


    if (fgets(s,2001,stdin))

    {

    }

    res=(int *)malloc(1000*sizeof(int));

    *digitsSize=0;

    for (i=0;s[i];i++)

    {

        if (s[i]>='0' && s[i]<='9')

        {

            res[(*digitsSize)++]=s[i]-'0';

        }

    }

    return res;

}


/* 你的代码将被嵌在这里 */

/*
输入样例：

2 0 1 9

输出样例：

2 0 1 8

Code Size Limit
16 KB
Time Limit
400 ms
Memory Limit
10 MB
*/

#include <stdio.h>
#include <stdlib.h>

int *GetDigits(int *digitsSize);  /* 由裁判实现，略去不表 */
int* MinusOne(int *digits, int digitsSize, int *returnSize);

int main()
{
    int *digits, *returnDigits, digitsSize, returnSize,i;

    digits = GetDigits(&digitsSize);
    returnDigits=MinusOne(digits, digitsSize, &returnSize);
    for (i=0; i<returnSize; i++)
    {
        printf("%d ", returnDigits[i]);
    }
    printf("\n");
    free(digits);
    free(returnDigits);

    return 0;
}

int *GetDigits(int *digitsSize)
{
    int *res,i;
    char s[2001];

    if (fgets(s,2001,stdin))
    {
    }
    res=(int *)malloc(1000*sizeof(int));
    *digitsSize=0;
    for (i=0; s[i]; i++)
    {
        if (s[i]>='0' && s[i]<='9')
        {
            res[(*digitsSize)++]=s[i]-'0';
        }
    }
    return res;
}

/* 你的代码将被嵌在这里 */
int* MinusOne(int *digits, int digitsSize, int *returnSize)
{
    if(digits&&digitsSize)
    {
        int *Res=NULL,*ptr=NULL;
        char CF=-1;
        for(int *p=digits+digitsSize-1; p>digits; --p)
            if(*p)
            {
                CF=0;
                break;
            }
        if(CF&&(*digits<2))
            if(digitsSize==1)
            {
                *returnSize=1;
                Res=malloc(sizeof(int));
                *Res=0;
                return Res;
            }
            else
                *returnSize=digitsSize-1;
        else
            *returnSize=digitsSize;
        Res=malloc((*returnSize)*sizeof(int)),ptr=Res+(*returnSize-1);
        CF=-1;
        int *p=digits+digitsSize-1;
        for(int i=0; i<(*returnSize); ++i)
        {
            int val=(*p--)+CF;
            if(val<0)
            {
                val+=10;
                CF=-1;
            }
            else
                CF=0;
            (*ptr--)=val;
        }
        return Res;
    }
    else
        return NULL;
}
