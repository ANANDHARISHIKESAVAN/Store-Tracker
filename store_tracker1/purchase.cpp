#include "purchase.h"
#include "qdebug.h"
#include "ui_purchase.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
purchase::purchase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::purchase)
{
    ui->setupUi(this);
    QPalette palette;
    QPixmap backgroundImage(":/blue.jpg");
    palette.setBrush(QPalette::Window, backgroundImage);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
    ui->tax->addItems(QStringList()<<"5%"<<"12%"<<"16%"<<"24%");
    this->setWindowTitle("Product Form");
}

purchase::~purchase()
{
    delete ui;
}


void purchase::on_back_clicked()
{
    this->close();

}


void purchase::on_cancel_clicked()
{
    this->close();
}


void purchase::on_tax_currentTextChanged(const QString &arg1)
{
    QString tax=ui->tax->currentText();
    int t = 0;
    if(tax=="5%"){
        t=5;
    }
    else if(tax=="12%"){
        t=12;
    }
    else if(tax=="16%"){
        t=16;
    }
    else if(tax=="24%"){
        t=24;
    }
    float c=t/2.0;
    float s=t/2.0;
    ui->cgst->setText(QString::number(c)+"%");
    ui->sgst->setText(QString::number(s)+"%");
}
void purchase::setData(QString s){
    dbname=s;
    qDebug()<<dbname;
    QSettings settings("store_tracker","database");
    QString dbname1=settings.value("dbname",QString("store_tracker")).toString();
    if(dbname!=dbname1){
        settings.setValue("dbname",dbname);
    }

}




void purchase::on_add_clicked()
{
    int sum=0;
    QSettings settings("store_tracker","database");
    dbname=settings.value("dbname",QString("store_tracker")).toString();
    int id = settings.value("id",int(0)).toInt();
    database=QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(QString("F:/database/%1.db").arg(dbname));
    if(database.open()){
        QSqlQuery qry1;
        qry1.exec("create table purchaseinfo""(Product_Type varchar(30),""Product_Name varchar(30) primary key,""HSN_Code integer,""Unit integer,""Tax varchar(10),""CGST varchar(10),""SGST varchar(10))");
        QString Product_Type;
        if(ui->goods->isChecked()){
            Product_Type="Goods";
        }
        if(ui->service->isChecked()){
            Product_Type="Service";
        }
        QString Product_Name=ui->name->text().toUpper();
        QRegularExpression nameRegex("[A-Z\\s]+");
        QRegularExpressionMatch nameMatch = nameRegex.match(Product_Name);
        if(nameMatch.hasMatch()){
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
        QString Tax=ui->tax->currentText();
        QString CGST=ui->cgst->text();
        QString SGST=ui->sgst->text();
        if(Product_Type!="" && Product_Name!="" && HSN_Code!="" && Unit!="" && Tax!="" && CGST!="" && SGST!="" && sum==2){
            QSqlQuery qry;
            qry.prepare("Insert into purchaseinfo(Product_Type,Product_Name,HSN_Code,Unit,Tax,CGST,SGST)""VALUES(:Product_Type,:Product_Name,:HSN_Code,:Unit,:Tax,:CGST,:SGST)");
            qry.bindValue(":Product_Type",Product_Type);
            qry.bindValue(":Product_Name",Product_Name);
            qry.bindValue(":HSN_Code",HSN_Code);
            qry.bindValue(":Unit",Unit);
            qry.bindValue(":Tax",Tax);
            qry.bindValue(":CGST",CGST);
            qry.bindValue(":SGST",SGST);
            if(qry.exec()){
                id=id+1;
                settings.setValue("id", id);
                qDebug()<<"success";
                QMessageBox::information(this,"INFO","Purchase Details is saved");
            }
        }
        else{
            QMessageBox::information(this,"Error","Please fill in the all Fields");
        }
    }
    else{
        QMessageBox::information(this,"Error","Database is not working");
    }
    database.close();
    QSqlDatabase::removeDatabase(QString("%1.db").arg(dbname));
}



void purchase::on_alter_clicked()
{
    int sum=0;
    QSettings settings("store_tracker","database");
    dbname=settings.value("dbname",QString("store_tracker")).toString();
    qDebug()<<dbname;
    database=QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(QString("F:/database/%1.db").arg(dbname));
    if(database.open()){
        QString Product_Type;
        if(ui->goods->isChecked()){
            Product_Type="Goods";
        }
        if(ui->service->isChecked()){
            Product_Type="Service";
        }
        QString Product_Name=ui->name->text();
        QRegularExpression nameRegex("[A-Za-z\\s]+");
        QRegularExpressionMatch nameMatch = nameRegex.match(Product_Name);
        if(nameMatch.hasMatch()){
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
        QString Tax=ui->tax->currentText();
        QString CGST=ui->cgst->text();
        QString SGST=ui->sgst->text();
        QSqlQuery qry3;
        QModelIndex index=ui->purchase_table->currentIndex();
        qDebug()<<index;
        if (!index.isValid()) {
            // No row is selected
            qDebug() << "No row is selected";
            return;
        }
        QVariant id = ui->purchase_table->model()->data(ui->purchase_table->model()->index(index.row(), 1));
        QString product = id.toString();
        if(Product_Type!="" && Product_Name!="" && HSN_Code!="" && Unit!="" && Tax!="" && CGST!="" && SGST!="" && sum==2){
            qry3.prepare("update purchaseinfo set Product_Type=:Product_Type,Product_Name=:Product_Name,HSN_Code=:HSN_Code,Unit=:Unit,Tax=:Tax,CGST=:CGST,SGST=:SGST where Product_Name=:product");
            qry3.bindValue(":Product_Type",Product_Type);
            qry3.bindValue(":Product_Name",Product_Name);
            qry3.bindValue(":HSN_Code",HSN_Code);
            qry3.bindValue(":Unit",Unit);
            qry3.bindValue(":Tax",Tax);
            qry3.bindValue(":CGST",CGST);
            qry3.bindValue(":SGST",SGST);
            qry3.bindValue(":product",product);
            if(qry3.exec()){
                QMessageBox::information(this,"Success","Updation Successfull");
            }
            else{
                QMessageBox::information(this,"Error","Updation Failed");
            }
        }
        else{
            QMessageBox::information(this,"Error","Fill in all Fields");
        }

    }
    else{
        QMessageBox::information(this,"Error","Database is Failed");
    }
    database.close();
    QSqlDatabase::removeDatabase(QString("%1.db").arg(dbname));
}





void purchase::on_pushButton_clicked()
{
    QSettings settings("store_tracker","database");
    dbname=settings.value("dbname",QString("store_tracker")).toString();
    qDebug()<<dbname;
    database=QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(QString("F:/database/%1.db").arg(dbname));
    if(database.open()){
        model=new QSqlQueryModel();
        QSqlQuery qry;
        qry.prepare("select * from purchaseinfo");

        qry.exec();
        model->setQuery(qry);
        ui->purchase_table->setModel(model);
        qDebug()<<(model->rowCount());
    }
    database.close();
}


void purchase::on_purchase_table_clicked(const QModelIndex &index)
{
    QSettings settings("store_tracker","database");
    dbname=settings.value("dbname",QString("store_tracker")).toString();
    database=QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(QString("F:/database/%1.db").arg(dbname));
    if(database.open()){
        qDebug()<<index;
        QModelIndex index1=index;
        qDebug()<<index1;
        if (!index.isValid()) {
            // No row is selected
            qDebug() << "No row is selected";
            return;
        }
        QVariant id = ui->purchase_table->model()->data(ui->purchase_table->model()->index(index1.row(), 1));
        QString product = id.toString();
        QSqlQuery query;
        QSqlQuery qry2;
        qry2.prepare("select * from purchaseinfo where Product_Name=:product");
        qry2.bindValue(":product",product);
        if(qry2.exec()){
            qDebug()<<"hiiiiiii";
            while(qry2.next()){
                if(qry2.value(0)=="Goods"){
                    ui->goods->setChecked(true);
                }
                if(qry2.value(0)=="Service"){
                    ui->service->setChecked(true);
                }
                ui->name->setText(qry2.value(1).toString());
                ui->hsn->setText(qry2.value(2).toString());
                ui->unit->setValue(qry2.value(3).toInt());
                ui->tax->setCurrentText(qry2.value(4).toString());
                ui->cgst->setText(qry2.value(5).toString());
                ui->sgst->setText(qry2.value(6).toString());
            }
        }
    }
    database.close();
    QSqlDatabase::removeDatabase(QString("%1.db").arg(dbname));
}

