#include "ccltrwin.h"
#include "ui_ccltrwin.h"
#include "oper.h"

#include<QPushButton>
#include<QLineEdit>
#include<QString>
#include<string>
using namespace std;
#include<string.h>

ccltrWin::ccltrWin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ccltrWin)//connect函数们
{
    ui->setupUi(this);
        connect(ui->zeroButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));//信号0与槽函数
        connect(ui->oneButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));//信号1与槽函数
        connect(ui->twoButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));//信号2与槽函数
        connect(ui->threeButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));//信号3与槽函数
        connect(ui->fourButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));//信号4与槽函数
        connect(ui->fiveButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));//信号5与槽函数
        connect(ui->sixButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));//信号6与槽函数
        connect(ui->sevenButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));//信号7与槽函数
        connect(ui->eightButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));//信号8与槽函数
        connect(ui->nineButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));//信号9与槽函数
        connect(ui->dotButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));//信号.与槽函数

        connect(ui->addButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));//信号+与槽函数
        connect(ui->subButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));//信号-与槽函数
        connect(ui->multButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));//信号*与槽函数
        connect(ui->divButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));//信号/与槽函数

        connect(ui->powButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));//信号^与槽函数
        connect(ui->rootButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));//信号root与槽函数

        connect(ui->bkspButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));//信号backspace与槽函数
        connect(ui->allclearButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));//信号C与槽函数
        connect(ui->equalButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));//信号=与槽函数

        connect(ui->lbrButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));//信号(与槽函数
        connect(ui->rbrButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));//信号)与槽函数

        connect(ui->sinButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));//信号sin与槽函数
        connect(ui->cosButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));//信号cos与槽函数
        connect(ui->expButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));//信号e^与槽函数
        connect(ui->lnButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));//信号ln与槽函数
}

ccltrWin::~ccltrWin()
{
    delete ui;
}

void ccltrWin::buttonClicked()
{
    InOutEdit = ui->InOutEdit;
    input = InOutEdit->text();//输入框
    QPushButton *tb = qobject_cast<QPushButton *>(sender());//把信号的发送者转换成pushbutton类型
    QString text = tb->text();//text:获取或设置文本框的文本内容

    char in=* (text.toLatin1().data());//用该函数取text的第一个字符地址并解引用 ;

   switch (in) //不同按键的显示与输入
   {
           case '<':   //bkspButton
       {
           text = input.left(input.length()-1); //减去一字符
           InOutEdit->setText(text);
       }
           break;

           case 'A':   //allclearButton
       {
           input="";
           InOutEdit->setText(input);
       }
           break;

           case '=':
        {
           string str=input.toStdString();//QString转化为String
           const char *S=str.c_str();//整个输入框的字符串
           char OPS[50];//中缀表达式
           int len;//后缀表达式的长度
           double result;//计算结果
           QString change;
           bool flag1 = true;
           bool flag2 = true;
           flag1=check(input,flag1);
           if (flag1==false)
           {
           InOutEdit->setText("error");
           }
           else
           {
                transfer(S,OPS,len);
                calculate(OPS,len,result,flag2);
                if(flag2 == false)
                {
                    InOutEdit->clear();
                    InOutEdit->setText("divisor can't be 0");
                }
                       else
                {
                    change=QString::number(result,10,6);//将计算结果转换为字符串
                    InOutEdit->setText(change);
                }
            }
        }
            break;

           default ://numbers.,+-*/^,sin cos,（）
           InOutEdit->setText(input+=text);
   }
}
