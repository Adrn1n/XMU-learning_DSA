/*
3-2 Evaluate Postfix Expression
Score 25
Author 陈越
Organization 浙江大学

Write a program to evaluate a postfix expression.  You only have to handle four kinds of operators: +, -, x, and /.
Format of functions:

ElementType EvalPostfix( char *expr );

where expr points to a string that stores the postfix expression.  It is guaranteed that there is exactly one space between any two operators or operands.
The function EvalPostfix is supposed to return the value of the expression.  If it is not a legal postfix expression, EvalPostfix must return a special value Infinity which is defined by the judge program.
Sample program of judge:

#include <stdio.h>

#include <stdlib.h>


typedef double ElementType;

#define Infinity 1e8

#define Max_Expr 30   /* max size of expression */
/*


ElementType EvalPostfix( char *expr );


int main()

{

    ElementType v;

    char expr[Max_Expr];

    gets(expr);

    v = EvalPostfix( expr );

    if ( v < Infinity )

        printf("%f\n", v);

    else

        printf("ERROR\n");

    return 0;

}


/* Your function will be put here */
/*

Sample Input 1:

11 -2 5.5 * + 23 7 / -

Sample Output 1:

-3.285714

Sample Input 2:

11 -2 5.5 * + 23 0 / -

Sample Output 2:

ERROR

Sample Input 3:

11 -2 5.5 * + 23 7 / - *

Sample Output 3:

ERROR

Special thanks to Sirou Zhu (朱思柔) and Xuling Zheng (郑旭玲) for providing valuable test cases.
Code Size Limit
16 KB
Time Limit
400 ms
Memory Limit
64 MB
*/

#include <stdio.h>
#include <stdlib.h>

typedef double ElementType;
#define Infinity 1e8
#define Max_Expr 30   /* max size of expression */

ElementType EvalPostfix( char *expr );

int main()
{
    ElementType v;
    char expr[Max_Expr];
    gets(expr);
    v = EvalPostfix( expr );
    if ( v < Infinity )
        printf("%f\n", v);
    else
        printf("ERROR\n");
    return 0;
}

/* Your function will be put here */
ElementType EvalPostfix( char *expr )
{
    short Top_OPND=-1;
    ElementType OPND[Max_Expr]= {0};
    while(*expr)
        if(((*expr>='0')&&(*expr<='9'))||(((*expr=='+')||(*expr=='-'))&&((*(expr+1)>='0')&&(*(expr+1)<='9'))))
        {
            ElementType val=0;
            long long d=1;
            char sig=1;
            if(*expr=='-')
                sig=-1,++expr;
            else if(*expr=='+')
                ++expr;
            while(((*expr>='0')&&(*expr<='9'))||(*expr=='.'))
            {
                if(*expr=='.')
                    if(d>1)
                        return Infinity;
                    else
                        d*=10;
                else if(d>1)
                    val+=(*expr-'0')/(double)d,d*=10;
                else
                    val*=10,val+=(*expr-'0');
                ++expr;
            }
            OPND[++Top_OPND]=sig*val;
        }
        else if((*expr=='+')||(*expr=='-')||(*expr=='*')||(*expr=='/'))
            switch(*expr++)
            {
            case '+':
            {
                if(Top_OPND<1)
                    return Infinity;
                else
                    OPND[Top_OPND-1]+=OPND[Top_OPND],--Top_OPND;
                break;
            }
            case '-':
            {
                if(Top_OPND<1)
                    return Infinity;
                else
                    OPND[Top_OPND-1]-=OPND[Top_OPND],--Top_OPND;
                break;
            }
            case '*':
            {
                if(Top_OPND<1)
                    return Infinity;
                else
                    OPND[Top_OPND-1]*=OPND[Top_OPND],--Top_OPND;
                break;
            }
            case '/':
            {
                if((Top_OPND<1)||((OPND[Top_OPND]<1/Infinity)&&(OPND[Top_OPND]>-1/Infinity)))
                    return Infinity;
                else
                    OPND[Top_OPND-1]/=OPND[Top_OPND],--Top_OPND;
                break;
            }
            default:
                return Infinity;
            }
        else if(*expr==' ')
            ++expr;
        else
            return Infinity;
    if(Top_OPND==0)
        return *OPND;
    else
        return Infinity;
}
