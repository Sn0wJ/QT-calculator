#ifndef CCLTRWIN_H
#define CCLTRWIN_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class ccltrWin; }
QT_END_NAMESPACE

class ccltrWin : public QWidget
{
    Q_OBJECT

private slots:  //define slot func.
    void buttonClicked();


public:
    ccltrWin(QWidget *parent = nullptr);
    ~ccltrWin();

private:
    Ui::ccltrWin *ui;
    QLineEdit *InOutEdit;//显示框
    QString input; //输入框

};
#endif // CCLTRWIN_H
