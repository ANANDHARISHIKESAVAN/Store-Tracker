#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include "menu.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QPalette palette;
    QPixmap backgroundImage(":/blue.jpg");
    palette.setBrush(QPalette::Window, backgroundImage);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
    this->setWindowTitle("Store Tracker - Admin Login");
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_loginbtn_clicked()
{
    QString username = ui->username->text();
    QString password = ui->password->text();
    if(username=="admin" && password=="admin"){
        this->hide();
        menu *men=new menu;
        men->show();
    }
    else{
        QMessageBox::information(this,"Login", "Please enter correct username and password", QMessageBox::Ok);
    }
}

