#include "company_info.h"
#include "ui_company_info.h"
#include "purchase.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
company_info::company_info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::company_info)
{
    ui->setupUi(this);
    QPalette palette;
    QPixmap backgroundImage(":/blue.jpg");
    palette.setBrush(QPalette::Window, backgroundImage);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
    this->setWindowTitle("Company Details");
    int i;
    for(i=2000;i<=QDate::currentDate().year();i++){
        ui->from->addItem(QString::number(i));
    }
    ui->state->addItems(QStringList() << "Andhra Pradesh"<<"Arunachal Pradesh"
                        <<"Assam"
                        <<"Bihar"
                        <<"Chhattisgarh"
                        <<"Goa"
                        <<"Gujarat	Gandhinagar"
                        <<"Haryana	Chandigarh"
                        <<"Himachal Pradesh"
                        <<"Jharkhand"
                        <<"Karnataka"
                        <<"Kerala"
                        <<"Madhya Pradesh"
                        <<"Maharashtra"
                        <<"Manipur"
                        <<"Meghalaya"
                        <<"Mizoram"
                        <<"Nagaland"
                        <<"Odisha"
                        <<"Punjab"
                        <<"Rajasthan"
                        <<"Sikkim"
                        <<"Tamil Nadu"
                        <<"Telangana"
                        <<"Tripura	Agartala"
                        <<"Uttar Pradesh"
                        <<"Uttarakhand"
                        <<"West Bengal");


}

company_info::~company_info()
{
    delete ui;
}


void company_info::uiChange()
{
   qDebug()<<"hiiii";
   ui->to->setVisible(false);
   ui->from->setVisible(false);
   ui->label_7->setVisible(false);
   ui->label_8->setVisible(false);
   ui->label_9->setVisible(false);
   ui->label_10->setVisible(false);
   this->setWindowTitle("Purchase Company Details");
}

void company_info::on_save_clicked()
{
  if(ui->from->isVisible()==1){
    int sum=0;
    name=ui->uname->text();
    qDebug()<<name;
    emit setDataSig(name);
    database=QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(QString("F:/database/%1.db").arg(name));
    QSettings settings("store_tracker","database");
    settings.setValue("dbname",name);

    if(database.open()){
        QSqlQuery qry1;
        qry1.exec("create table companyinfo""(Id integer primary key autoincrement,""Username varchar(20),""Address varchar(30),""State varchar(15),""Pincode integer(6),""GSTInfo varchar(15),""Financial_Year_From varchar(20),""Financial_Year_To varchar(20))");
        QString Username=ui->uname->text();
        QRegularExpression nameRegex("[A-Za-z\\s]+");
        QRegularExpressionMatch nameMatch = nameRegex.match(Username);
        if(nameMatch.hasMatch()){
            sum=sum+1;
        }
        else{
            QMessageBox::information(this,"Error","Please enter the correct Username");
        }
        QString Address=ui->address->toPlainText();
        QRegularExpression addressRegex("[A-Za-z0-9\\.\\,\\-]+");
        QRegularExpressionMatch addressMatch = addressRegex.match(Address);
        if(addressMatch.hasMatch()){
            sum=sum+1;
        }
        else{
            QMessageBox::information(this,"Error","Please enter the correct Address");
        }
        QString State=ui->state->currentText();

        QString Pincode=ui->code->text();
        QRegularExpression pinRegex("[0-9]{6}");
        QRegularExpressionMatch pinMatch = pinRegex.match(Pincode);
        if(pinMatch.hasMatch()){
            sum=sum+1;
        }
        else{
            QMessageBox::information(this,"Error","Please enter the correct Pincode");
        }
        QString GSTInfo=ui->gstinfo->text();
        QRegularExpression gstRegex("[A-Z0-9]{15}");
        QRegularExpressionMatch gstMatch = gstRegex.match(GSTInfo);
        if(gstMatch.hasMatch()){
            sum=sum+1;
        }
        else{
            QMessageBox::information(this,"Error","Please enter the correct GST Number");
        }
        QString Financial_Year_From=ui->from->currentText();

        QString Financial_Year_To=ui->to->currentText();
        if(Username!="" && Address!="" && State!="" && Pincode!="" && GSTInfo!="" && Financial_Year_From!="" && Financial_Year_To!="" && sum==4){
            QSqlQuery qry;
            qry.prepare("Insert into companyinfo(Username,Address,State,Pincode,GSTInfo,Financial_Year_From,Financial_Year_To)""VALUES(:Username,:Address,:State,:Pincode,:GSTInfo,:Financial_Year_From,:Financial_Year_To)");
            qry.bindValue(":Username",Username);
            qry.bindValue(":Address",Address);
            qry.bindValue(":State",State);
            qry.bindValue(":Pincode",Pincode);
            qry.bindValue(":GSTInfo",GSTInfo);
            qry.bindValue(":Financial_Year_From","1-Apr-"+Financial_Year_From);
            qry.bindValue(":Financial_Year_To","31-Mar-"+Financial_Year_To);

            if(qry.exec()){
                qDebug()<<"success";
                QMessageBox::information(this,"INFO","Company Details is saved");
            }
        }
        else{
            qDebug()<<"failed";
            QMessageBox::information(this,"INFo","Fill all the fields");

        }
    }
    else{
        qDebug()<<"connectionless";
        QMessageBox::information(this,"INFo","Failed");
    }
    database.close();
    QSqlDatabase::removeDatabase(QString("%1.db").arg(name));
  }
  if(ui->from->isVisible()==0){
      int sum=0;
      qDebug()<<"create";
      QSettings settings("store_tracker","database");
      dbname=settings.value("dbname",QString("store_tracker")).toString();
      database=QSqlDatabase::addDatabase("QSQLITE");
      database.setDatabaseName(QString("F:/database/%1.db").arg(dbname));
      qDebug()<<dbname;
      if(database.open()){
          QSqlQuery qry1;
          qry1.exec("create table purchase_companyinfo""(Username varchar(20) primary key,""Address varchar(30),""State varchar(15),""Pincode integer(6),""GSTInfo varchar(15))");
          QString Username=ui->uname->text().toUpper();
          QRegularExpression nameRegex("[A-Z\\s]+");
          QRegularExpressionMatch nameMatch = nameRegex.match(Username);
          if(nameMatch.hasMatch()){
              sum=sum+1;
          }
          else{
              QMessageBox::information(this,"Error","Please enter the correct Username in Caps");
          }
          QString Address=ui->address->toPlainText();
          QRegularExpression addressRegex("[A-Za-z0-9\\.\\,\\-]+");
          QRegularExpressionMatch addressMatch = addressRegex.match(Address);
          if(addressMatch.hasMatch()){
              sum=sum+1;
          }
          else{
              QMessageBox::information(this,"Error","Please enter the correct Address");
          }
          QString State=ui->state->currentText();

          QString Pincode=ui->code->text();
          QRegularExpression pinRegex("[0-9]{6}");
          QRegularExpressionMatch pinMatch = pinRegex.match(Pincode);
          if(pinMatch.hasMatch()){
              sum=sum+1;
          }
          else{
              QMessageBox::information(this,"Error","Please enter the correct Pincode");
          }
          QString GSTInfo=ui->gstinfo->text();
          QRegularExpression gstRegex("[A-Z0-9]{15}");
          QRegularExpressionMatch gstMatch = gstRegex.match(GSTInfo);
          if(gstMatch.hasMatch()){
              sum=sum+1;
          }
          else{
              QMessageBox::information(this,"Error","Please enter the correct GST Number");
          }
          if(Username!="" && Address!="" && State!="" && Pincode!="" && GSTInfo!="" && sum==4){
              QSqlQuery qry;
              qry.prepare("Insert into purchase_companyinfo(Username,Address,State,Pincode,GSTInfo)""VALUES(:Username,:Address,:State,:Pincode,:GSTInfo)");
              qry.bindValue(":Username",Username);
              qry.bindValue(":Address",Address);
              qry.bindValue(":State",State);
              qry.bindValue(":Pincode",Pincode);
              qry.bindValue(":GSTInfo",GSTInfo);

              if(qry.exec()){
                  qDebug()<<"success";
                  QMessageBox::information(this,"INFO","Purchase Company Details is saved");
              }
          }
          else{
              qDebug()<<"failed";
              QMessageBox::information(this,"INFo","Fill all the fields");

          }
      }
      else{
          qDebug()<<"connectionless";
          QMessageBox::information(this,"INFo","Failed");
      }
      database.close();
      QSqlDatabase::removeDatabase(QString("%1.db").arg(dbname));

  }
}



void company_info::on_from_currentTextChanged(const QString &arg1)
{
    ui->to->clear();
    QString end=QString::number(arg1.toInt()+1);
    ui->to->addItem(end);
}


