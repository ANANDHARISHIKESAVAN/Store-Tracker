#ifndef USER_H
#define USER_H
#include <menu.h>
#include "qsqldatabase.h"
#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QFileInfo>
#include <widget.h>
#include <company_info.h>
namespace Ui {
class user;
}

class user : public QWidget
{
    Q_OBJECT

public:
    explicit user(QWidget *parent = nullptr);
    ~user();

signals:
    void edit();

private slots:
    void on_pushButton_clicked();

    void on_commandLinkButton_clicked();

private:
    Ui::user *ui;
    QString dbname;
    QSqlDatabase database;
    menu *m=new menu();
    Widget *w=new Widget();
    company_info *comp=new company_info();

};

#endif // USER_H
