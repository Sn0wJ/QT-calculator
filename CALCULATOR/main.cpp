#include "ccltrwin.h"
#include "oper.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ccltrWin w;
    w.show();
    return a.exec();
    //事实上不需要修改
}
