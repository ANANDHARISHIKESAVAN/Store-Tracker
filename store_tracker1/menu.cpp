#include "menu.h"
#include "ui_menu.h"
#include "seconddialog.h"
#include "company_info.h"
#include<QLabel>

menu::menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
    QPalette palette;
    QPixmap backgroundImage(":/blue.jpg");
    palette.setBrush(QPalette::Window, backgroundImage);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
    this->setWindowTitle("Company Main Window");
      QStatusBar *sb=new QStatusBar(this);
      setStatusBar(sb);
      QString date=QDate::currentDate().toString();
      QLabel *message=new QLabel(date,this);
      message->setAlignment(Qt::AlignRight);
      sb->addPermanentWidget(message);
       p=new purchase();
       comp=new company_info();
       comp1=new company_info();
       s=new Sales();
       product=new Prtoducts();
       list=new company_list();
       voucher=new purchase_voucher();
       connect(voucher,SIGNAL(call()),this,SLOT(uiChange()),Qt::DirectConnection);
       connect(this,SIGNAL(setUi()),comp1,SLOT(uiChange()));
       connect(voucher,SIGNAL(call1()),this,SLOT(uiChange1()));
}

menu::~menu()
{
    delete ui;
}



void menu::uiChange()
{
    qDebug()<<"Iam Ironamn";
    comp1->show();
    emit setUi();
}

void menu::uiChange1()
{
    p->show();
}

void menu::edited()
{
   ui->actionComapny_Details->setVisible(false);
}





void menu::on_actionUser_Management_triggered()
{
    SecondDialog seconddialog;
    seconddialog.setModal(true);
    seconddialog.exec();
}




void menu::on_pushButton_clicked()
{

  voucher->show();
}


void menu::on_sales_clicked()
{
    s->show();
}


void menu::on_actionProducts_triggered()
{
    product->show();
}


void menu::on_actionCompany_triggered()
{
    list->show();
}


void menu::on_actionComapny_Details_triggered()
{
    comp->show();
}


void menu::on_products_clicked()
{
    p->show();
}

