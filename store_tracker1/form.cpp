#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{
    database=QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("F:/database/store_tracker.db");

    if(database.open()){
        QString username=ui->username->text();
        QString password=ui->password->text();

        QSqlQuery qry;

        if(qry.exec("select username,password from add_users where username='"+username+"' AND password='"+password+"'"))
        {
            while(qry.next()){
                QMessageBox::information(this,"login","Login was successfull");
            }
        }
        else
        {
            QMessageBox::information(this,"logins","Login was failed");
        }
    }
    QSqlDatabase::removeDatabase("store_tracker.db");


}

