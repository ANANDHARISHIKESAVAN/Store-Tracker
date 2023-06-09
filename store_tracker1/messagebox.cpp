#include "messagebox.h"
#include "qdebug.h"
#include "ui_messagebox.h"

Messagebox::Messagebox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Messagebox)
{
    ui->setupUi(this);
    QPalette palette;
    QPixmap backgroundImage(":/blue.jpg");
    palette.setBrush(QPalette::Window, backgroundImage);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
    this->setWindowTitle("Message Box");
    ui->no1->setEnabled(false);
}

Messagebox::~Messagebox()
{
    delete ui;
}

void Messagebox::on_pushButton_clicked()
{
    int sum=0;
   QString cname=ui->name->text();
   QRegularExpression nameRegex("[A-Za-z\\s]+");
   QRegularExpressionMatch nameMatch = nameRegex.match(cname);
   if(nameMatch.hasMatch()){
       sum=sum+1;
   }
   else{
       QMessageBox::information(this,"Error","Please enter the correct Company name");
   }
   QString date=ui->date->text();
   int number=ui->no1->currentText().toInt();
   if(cname!="" && sum==1 && date!="" && number!=0){
        emit message1(number);
       this->close();
    }
   else{
       QMessageBox::information(this,"Error","Please fill all the values");
   }
}


void Messagebox::on_name_editingFinished()
{
    QString cname=ui->name->text();
    QString date=ui->date->date().toString("dd/MM/yyyy");
    QSettings settings("store_tracker","database");
    dbname=settings.value("dbname",QString("store_tracker")).toString();
    qDebug()<<dbname;
    database=QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(QString("F:/database/%1.db").arg(dbname));
    if(database.open()){
        QSqlQuery qry;
        qry.exec("select Voucher_No,Date,Company_Name from purchase_voucher");
        ui->no1->clear();
        while(qry.next()){
            if(cname.toUpper()==qry.value(2).toString() && date==qry.value(1).toString()){
                if(ui->no1->findText(qry.value(0).toString())==-1){
                     ui->no1->addItem(qry.value(0).toString());
                }
            }
            ui->no1->setEnabled(true);
        }
    }
}



