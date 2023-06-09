#include "user.h"
#include "qdebug.h"
#include "ui_user.h"
#include<QSettings>
user::user(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::user)
{
    ui->setupUi(this);
    QPalette palette;
    QPixmap backgroundImage(":/blue.jpg");
    palette.setBrush(QPalette::Window, backgroundImage);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
    this->setWindowTitle("User Login");
    connect(this,SIGNAL(edit()),m,SLOT(edited()));
}

user::~user()
{
    delete ui;
}

void user::on_pushButton_clicked()
{

    QSettings settings("store_tracker","database");
    dbname=settings.value("dbname",QString("store_tracker")).toString();
    qDebug()<<dbname;
    database=QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(QString("F:/database/%1.db").arg(dbname));
    int count=0;
    int sum=0;

   if(database.open()){
       QString username=ui->username->text();
       QRegularExpression unameRegex("[A-Za-z\\s]+");
       QRegularExpressionMatch unameMatch = unameRegex.match(username);
       if(unameMatch.hasMatch()){
           sum=sum+1;
       }
       else{
           QMessageBox::information(this,"Error","Please enter the correct User Name");
       }
       QString password=ui->password->text();
       QRegularExpression passRegex("[A-Za-z0-9\\s]+");
       QRegularExpressionMatch passMatch = passRegex.match(password);
       if(passMatch.hasMatch()){
           sum=sum+1;
       }
       else{
           QMessageBox::information(this,"Error","Please enter the correct Password([A-Za-z0-9\\s])");
       }

       QSqlQuery gry;
       if(gry.exec("Select username,password from add_users where username='"+username+"'AND password='"+password+"'")){
           while(gry.next()){
//               QMessageBox::information(this,"login","success");
               count++;
           }
       }
       if(count==1 && sum==2)
       {
           QMessageBox::information(this,"login","success");
           this->close();
           m->show();
           emit edit();
       }
       else{
           QMessageBox::information(this,"login","failed");
       }
   }
   QSqlDatabase::removeDatabase("store_tracker.db");
}


void user::on_commandLinkButton_clicked()
{
    w->show();

}

