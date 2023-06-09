#include "sales.h"
#include "ui_sales.h"
#include <QSettings>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
Sales::Sales(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sales)
{
    ui->setupUi(this);
    QPalette palette;
    QPixmap backgroundImage(":/blue.jpg");
    palette.setBrush(QPalette::Window, backgroundImage);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
    this->setWindowTitle("Sales Form");
    ui->Regular->setChecked(true);
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
    ui->gst->addItems(QStringList()<<"5%"<<"12%"<<"16%"<<"24%");
}

Sales::~Sales()
{
    delete ui;
}

void Sales::on_save_clicked()
{
      int count=0;
      int sum=0;
      QSettings settings("store_tracker","database");
      dbname=settings.value("dbname",QString("store_tracker")).toString();
      database=QSqlDatabase::addDatabase("QSQLITE");
      database.setDatabaseName(QString("F:/database/%1.db").arg(dbname));
      if(database.open()){
          QSqlQuery qry;
          qry.exec("create table sales""(Id integer primary key autoincrement,""Customer_Type varchar(20),""Name varchar(30),""Address varchar(30),""State varchar(15),""Pincode integer(6),""GST_Info varchar(20),""Product_Name varchar(35),""HSN_Code integer,""Unit integer,""GST varchar(10),""CGST varchar(10),""SGST varchar(10))");
          QString Customer_Type;
          if(ui->customer->isChecked()){
              Customer_Type="Customer";
          }
          if(ui->Regular->isChecked()){
              Customer_Type="Regular";
          }
          QString Name=ui->uname->text();
          QRegularExpression nameRegex("[A-Za-z\\s]+");
          QRegularExpressionMatch nameMatch = nameRegex.match(Name);
          if(nameMatch.hasMatch()){
              sum=sum+1;
          }
          else{
              QMessageBox::information(this,"Error","Please enter the correct Name");
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
          QString GST_Info=ui->gstinfo->text();
          QRegularExpression gstRegex("[A-Z0-9]{15}");
          QRegularExpressionMatch gstMatch = gstRegex.match(GST_Info);
          if(gstMatch.hasMatch()){
              sum=sum+1;
          }
          else{
              QMessageBox::information(this,"Error","Please enter the correct GST Number");
          }
          QString Product_Name=ui->pname->text().toUpper();
          QRegularExpression pnameRegex("[A-Z\\s]+");
          QRegularExpressionMatch pnameMatch = pnameRegex.match(Product_Name);
          if(pnameMatch.hasMatch()){
              sum=sum+1;
          }
          else{
              QMessageBox::information(this,"Error","Please enter the correct Product Name");
          }
          QString HSN_Code=ui->hsn->text();
          QRegularExpression hsnRegex("[0-9]{8}");
          QRegularExpressionMatch hsnMatch = hsnRegex.match(HSN_Code);
          if(hsnMatch.hasMatch()){
              sum=sum+1;
          }
          else{
              QMessageBox::information(this,"Error","Please enter the correct HSN Code");
          }
          QString Unit=ui->unit->text();
          QString GST=ui->gst->currentText();
          QString CGST=ui->cgst->text();
          QString SGST=ui->sgst->text();
          if(Customer_Type!="" && Name!="" && Address!="" && State!="" && Pincode!="" && GST_Info!="" && Product_Name!="" && HSN_Code!="" && Unit!="" && GST!="" && CGST!="" && SGST!="" && sum==6){
              qry.prepare("select Product_Name,HSN_Code,Unit from purchaseinfo");
              qry.exec();
              while(qry.next()){
                  if(Product_Name==qry.value(0).toString() && HSN_Code==qry.value(1).toString() && Unit.toInt()<=qry.value(2).toInt()){
                      int un=qry.value(2).toInt()-Unit.toInt();
                      QSqlQuery qry1;
                      qry1.prepare("update purchaseinfo set Unit=:un where Product_Name=:Product_Name");
                      qry1.bindValue(":un",un);
                      qry1.bindValue(":Product_Name",Product_Name);
                      qry1.exec();
                      qDebug()<<Product_Name;
                      qDebug()<<HSN_Code;
                      qDebug()<<Unit;
                      qDebug()<<count;
                      count++;
                      qDebug()<<count;
                  }
              }
              if(count==1){
                  qry.prepare("Insert into sales(Customer_Type,Name,Address,State,Pincode,GST_Info,Product_Name,HSN_Code,Unit,GST,CGST,SGST)""values(:Customer_Type,:Name,:Address,:State,:Pincode,:GST_Info,:Product_Name,:HSN_Code,:Unit,:GST,:CGST,:SGST)");
                  qry.bindValue(":Customer_Type",Customer_Type);
                  qry.bindValue(":Name",Name);
                  qry.bindValue(":Address",Address);
                  qry.bindValue(":State",State);
                  qry.bindValue(":Pincode",Pincode);
                  qry.bindValue(":GST_Info",GST_Info);
                  qry.bindValue(":Product_Name",Product_Name);
                  qry.bindValue(":HSN_Code",HSN_Code);
                  qry.bindValue(":Unit",Unit);
                  qry.bindValue(":GST",GST);
                  qry.bindValue(":CGST",CGST);
                  qry.bindValue(":SGST",SGST);
                  if(qry.exec()){
                      QMessageBox::information(this,"SUCCESS","Inserted Successfully");
                  }
                  else{
                      QMessageBox::information(this,"Error","Failed to insert");
                  }
              }
             else{
                  QMessageBox::information(this,"Error","We don't have enough stock");
              }
          }
          else{
              QMessageBox::information(this,"Error","Please fill all the fields");
          }
      }
      else{
          qDebug()<<"Connection is not established";
      }
      database.close();

}


void Sales::on_gst_currentTextChanged(const QString &arg1)
{
    QString gst=arg1;
    int t = 0;
    if(gst=="5%"){
        t=5;
    }
    else if(gst=="12%"){
        t=12;
    }
    else if(gst=="16%"){
        t=16;
    }
    else if(gst=="24%"){
        t=24;
    }
    float c=t/2.0;
    float s=t/2.0;
    ui->cgst->setText(QString::number(c)+"%");
    ui->sgst->setText(QString::number(s)+"%");
}


void Sales::on_customer_clicked()
{
    ui->gstinfo->setText("000000000000000");
    ui->gstinfo->setEnabled(false);
    ui->gst->clear();
    ui->gst->addItem("0%");
    ui->gst->setEnabled(false);
    ui->cgst->setText("0%");
    ui->cgst->setEnabled(false);
    ui->sgst->setText("0%");
    ui->sgst->setEnabled(false);
}


void Sales::on_Regular_clicked()
{
    ui->gstinfo->setEnabled(true);
    ui->gstinfo->setText("");
    ui->gst->clear();
    ui->gst->addItems(QStringList()<<"5%"<<"12%"<<"16%"<<"24%");
    ui->gst->setEnabled(true);
    ui->cgst->setEnabled(true);
    ui->sgst->setEnabled(true);

}

