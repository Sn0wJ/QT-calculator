#include "ui_ccltrwin.h"
#include<stdlib.h>
#include<math.h>
#include<QChar>
#include<QString>
#include<QStack>
#include<string>
using namespace std;


bool isNum(char ch)//正数判断
{
    if((ch>='0' && ch<='9')||ch=='.')return true;
    else return false;
}
bool isOp(char ch)//四则运算符判断
{
    if(ch=='+'||ch=='-'||ch=='*'||ch=='/')return true;
    else return false;

}
int level(char ch)//优先级判断函数
{
    switch(ch)
    {
        case 's':
        case 'c':
        case 'l':
        case 'e':
            return 6;
        case '^' :
            return 5;
        case '*' :
        case '/' :
            return 4;
        case '+' :
            return 3;
        case '-' :
            return 3;
        case ')':   //这个优先级为什么是这样我也不知道，反正加了这两行就能跑了
            return 2;
    }
}
void transfer(char const*s,char OPS[],int &len)//中缀转后缀
{
    QStack<char> OPE;//符号栈
        unsigned int i=0;
        int j=0;
        unsigned int length = strlen(s);
        for (i = 0; i < length; i++)
        {
            switch (s[i])
            {
            //普通双目
                case '+':
                case '*':
                case '/':
                case '^':
                    if(OPE.isEmpty())//栈为空
                    OPE.push(s[i]);
                    else if (level(OPE.top())>level(s[i]))//弹出比当前运算符优先级高和相等的运算符，依次加入后缀表达式
                    {
                        OPS[j++] = OPE.pop();
                        i--;
                    }
                    else
                        OPE.push(s[i]);
                break;

            //-号因为也有可能是单目所以比较特殊
                case '-':
                    if(i!=0 && '('!=s[i-1])//正数
                {
                 if(OPE.isEmpty())//栈为空
                      OPE.push(s[i]);
                  else if (OPE.top() == '*' || OPE.top() == '/'|| OPE.top() == '%' || OPE.top()=='^')//弹出比'-'运算符优先级高和相等的运算符，依次加入后缀表达式
                 {
                   OPS[j++] = OPE.pop();
                   i--;
                 }
                  else
                    OPE.push(s[i]);
                }
                    else//负数
                {
                    while (isNum(s[i])|| ('-'==s[i]&&(s[i-1]<'0'||s[i-1]>'9')))
                    {
                        OPS[j++] = s[i];
                        if('-'==s[i])
                          OPS[j++]='@';
                        i++;
                    }
                    i--;
                    OPS[j++] = '#';  //数字中的间隔符
                }
                break;

            //括号
                case '(':
                    OPE.push(s[i]);
                break;
                case')':
                    while (OPE.top() != '(')//依次把栈中的运算符加入后缀表达式并将其出栈
                    {
                        OPS[j++] = OPE.pop();
                    }
                    OPE.pop();//从栈中弹出'('
                break;
            //3个字的单目
            case 's':
            case 'c':
            case 'e':
                OPE.push(s[i]);
                i+=2;
            break;
            //ln
            case 'l':
                OPE.push(s[i]);
                i++;
                break;
            //sqrt
            case 'r':
                OPE.push(s[i]);
                i++;
                break;
          //数字
                default:
                {
                    while (isNum(s[i]))
                    {
                        OPS[j++] = s[i];
                        i++;//是数字就直接读下一位
                    }
                    i--;
                    OPS[j++] = '#';  //数字中的间隔符
                }
            }
        }
        while (!OPE.isEmpty())//遍历结束，弹出所有
        {
            OPS[j++] = OPE.pop();
        }
        len = j;
}
void calculate(char B[], int len, double &result,bool &flag)//用后缀表达式计算结果//flag 用于除数不为零的判断
{
    int i;
    double a,b,c;//用于计算
    QStack<double> SZ;//算出结果压入该栈
    for (i = 0; i < len; i++)
    {
        switch (B[i])
        {

           case'+':
           {
            a = SZ.pop();
            b = SZ.pop();
            c = b + a;
            SZ.push(c);
            }
               break;
           case'^':
            {
            a = SZ.pop();
            b = SZ.pop();
            c = pow(b,a);
            SZ.push(c);
            }
               break;
           case'-':
           {
            if('@'!=B[i+1])
            {
            a = SZ.pop();
            b = SZ.pop();
            c = b - a;
            SZ.push(c);
            }
            else
            {
                int jx = 0;
                double dx;
                char *stx = new char[10];
                while (B[i] != '#')
                {
                   if('@'!=B[i])
                    stx[jx++] = B[i];
                    i++;

                }
                dx = atof(stx);//把字符串转换成浮点数
                SZ.push(dx);
                delete[] stx;
            }
           }
               break;
           case'*':
           {
            a = SZ.pop();
            b = SZ.pop();
            c = b*a;
            SZ.push(c);
           }
               break;
           case'/':
           {
              a = SZ.pop();
              b = SZ.pop();
              if (a == 0)
              {
                  flag = false;
                  return;
              }
              c = b / a;
              SZ.push(c);
           }
               break;
            case 's':
            {
                a=SZ.pop();
                c=sin(a);
                SZ.push(c);
            }
                break;
            case 'c':
            {
                a=SZ.pop();
                c=cos(a);
                SZ.push(c);
            }
                break;
            case 'e':
        {
            a=SZ.pop();
            c=exp(a);
            SZ.push(c);
        }
                break;
            case 'l':
        {
            a=SZ.pop();
            c=log(a);
            SZ.push(c);
        }
                break;
           default://数字处理
               int j = 0;
               double d;
               char *st = new char[10];
               while (B[i] != '#')
               {
                   st[j++] = B[i];
                   i++;
               }
               d = atof(st);//把字符串转换成浮点数
               SZ.push(d);
               delete[] st;
               break;
        }
    }
    result=SZ.top();
}
bool check(QString qstr, bool flag)
{
    const char *ch=qstr.toStdString().data();
    int lbrcnt=0;
    int rbrcnt=0;
    for(int i=0;i<strlen(ch);i++)
    {
        switch (ch[i])
        {
        case '.':
        {
            if(i==0) //小数点前面不能为空
                flag=false;
            else if (isNum(ch[i-1])==false)//小数点前面必须为数字
                flag=false;
        }
            break;
        case '+':
        case '-':
        {
            if(i==0)//+-前面不能为空
                flag=false;
            else if (ch[i-1]=='+'||ch[i-1]=='-'||(isOp(ch[i-1])==true && isOp(ch[i-2])==true))//并且前面不能连续有两次加减乘除
                flag=false;
        }
            break;
        case 's':
        case 'c':
        case 'e':
        case 'l':
        case '*':
        case '/'://乘除号,sin,cos,ln,exp前面不能为:空,左括号,小数点,加减乘除,除数非零在
        {
            if(i==0)
                flag=false;
            else if(ch[i-1]=='('||ch[i-1]=='.'||isOp(ch[i-1])==true)
                flag=false;
        }
            break;
        case '('://左括号前面不能为:右括号,数字,小数点,并且前面不能连续有两次加减乘除
        {
            lbrcnt++;
            if(ch[i-1]==')'||ch[i-1]=='.'||isNum(ch[i-1]==true)||((isOp(ch[i-1])==true && isOp(ch[i-2])==true)))
               flag=false;
        }
            break;
        case ')'://右括号前面不能为:空,加减乘除,小数点,左括号
        {
            if(i==0)
                flag=false;
            else if(isNum(ch[i-1]==true)||ch[i-1]=='.'||ch[i-1]=='(')
                flag=false;
            rbrcnt++;
        }
            break;
        case '^'://^前面不能为:小数点,并且前面不能连续有两次加减乘除
        {
            if(i==0)
                flag=false;
            else if(ch[i-1]=='.'||((isOp(ch[i-1])==true && isOp(ch[i-2])==true)))
                flag=false;
        }
            break;
        }
    }
    if (lbrcnt>rbrcnt)
        flag=false;
    return flag;
}
