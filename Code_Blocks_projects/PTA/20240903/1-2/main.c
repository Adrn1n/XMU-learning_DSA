/*
1-2 多项式求和
Score 10
Author 陈浩川
Organization 厦门大学
编写算法求一元多项式的值P_n(x)=Sum(i=0,n,a_i x^i)的值P_n(x_0)。

注意：不要使用内置的求幂函数，例如C中的pow()、Python中的**等

输入格式:
第一行为一个整数n和一个浮点数x_0。其中0≤n≤30,000，表示多项式次数；x_0 为多项式中的变量x的取值。
第二行为空格分割的n+1个浮点数，由高到低表示多项式中项的系数。

可以假设输入总是合法的。

输出格式:
输出多项式的求值结果，保留三位小数，以换行结尾。

输入样例:
例如：

3 1.0
1 2 3 4
对应多项式为P(x)=x^3+2x^2+3x+4，自变量取值为x=1.0。

输出样例:
输出为

10.000
Code Size Limit
100 KB
Time Limit
400 ms
Memory Limit
64 MB
Stack size limit
8192 KB
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    short n=0,flag=0;
    double x_0=0;
    scanf("%hd%lf",&n,&x_0);
    double A[n+1];
    long double X[n],res=0;
    for(double *p=A; p-A<=n; ++p)
        scanf("%lf",p);
    for(short i=1; i<=n; ++i)
    {
        long double a=x_0;
        if(flag)
        {
            a=X[i-2]/x_0;
            X[i-1]=a;
        }
        else if(A[i-1])
        {
            for(short j=(short)(n-i); j; --j)
                a*=x_0;
            X[i-1]=a;
            flag=1;
        }
        res+=A[i-1]*a;
    }
    printf("%.3lf\n",(double)(res+A[n]));
    return 0;
}
