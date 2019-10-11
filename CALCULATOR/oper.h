#ifndef OPER_H
#define OPER_H
#include <QChar>
#include <QDebug>

bool isNum(char ch);
int level(char ch);
void transfer(char const*s,char OPS[],int &len);
void calculate(char B[],int len,double &result,bool &flag);
bool check(QString qstr,bool flag);

#endif // OPER_H
