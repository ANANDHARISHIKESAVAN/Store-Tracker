#ifndef LOGIN_H
#define LOGIN_H


#include <QWidget>
#include <widget.h>
#include <user.h>
#include <QMessageBox>
#include <QDebug>
#include <QFileInfo>
#include <QFile>
#include <QSettings>
namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_pushButton_clicked();

private:
    Ui::login *ui;
    QString dbname;
    Widget *w = new Widget();
    user *u=new user();
    QSqlDatabase database;
};

#endif // LOGIN_H
