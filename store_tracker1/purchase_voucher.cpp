#include "purchase_voucher.h"
#include "ui_purchase_voucher.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QtMath>
#include <QTableWidget>
purchase_voucher::purchase_voucher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::purchase_voucher)
{
    ui->setupUi(this);
    this->setWindowTitle("Purchase Voucher");
    QPalette palette;
    QPixmap backgroundImage(":/blue.jpg");
    palette.setBrush(QPalette::Window, backgroundImage);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
    ui->table->setColumnCount(9);
    ui->table->setRowCount(1);
    ui->table->setHorizontalHeaderLabels(QStringList()<<"Product"<<"HSN Code"<<"Quantity"<<"Price"<<"CGST"<<"CGST Rate"<<"SGST"<<"SGST Rate"<<"Total");
    QString date1=QDate::currentDate().toString("dd/MM/yyyy");
    ui->date->setText(date1);
    QSettings settings("store_tracker","database");
    dbname=settings.value("dbname",QString("store_tracker")).toString();
    qDebug()<<dbname;
    database=QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(QString("F:/database/%1.db").arg(dbname));
    if(database.open()){
        QSqlQuery qry;
        qry.exec("select Voucher_No from purchase_voucher order by Voucher_No desc LIMIT 1");
        if(qry.next()){
            int id_number=qry.value(0).toInt();
            id_number++;
            ui->no->setText(QString::number(id_number));
        }
        else{
            ui->no->setText("1");
        }
    }
    m=new Messagebox();
    connect(m,SIGNAL(message1(int)),this,SLOT(callMessage(int)));

}

purchase_voucher::~purchase_voucher()
{
    delete ui;
}

void purchase_voucher::callMessage(int num)
{
    qDebug()<<num;
    QSettings settings("store_tracker","database");
    dbname=settings.value("dbname",QString("store_tracker")).toString();
    qDebug()<<dbname;
    database=QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(QString("F:/database/%1.db").arg(dbname));
    ui->table->removeRow(0);

    if(database.open()) {
        qDebug() << "Database connection established";
        QSqlQuery qry;
        qry.prepare("select Voucher_No,Date,Company_Name,Product_Name,HSN_Code,Quantity,Price,CGST,CGST_Rate,SGST,SGST_Rate,Total from purchase_voucher where Voucher_No=:num");
        qry.bindValue(":num", num);
        if(qry.exec()){

            qDebug() << "Query executed successfully";
            int i = 0;
            while(qry.next()){
                ui->table->removeRow(i);
                ui->table->insertRow(i);
                qDebug() << qry.value(3).toString();

                ui->no->setText(qry.value(0).toString());
                ui->date->setText(qry.value(1).toString());
                ui->company->setText(qry.value(2).toString());

                QTableWidgetItem *i1 = new QTableWidgetItem(qry.value(3).toString());
                ui->table->setItem(i, 0, i1);

                QTableWidgetItem *i2 = new QTableWidgetItem(qry.value(4).toString());
                ui->table->setItem(i, 1, i2);

                QTableWidgetItem *i3 = new QTableWidgetItem(qry.value(5).toString());
                ui->table->setItem(i, 2, i3);

                QTableWidgetItem *i4 = new QTableWidgetItem(qry.value(6).toString());
                ui->table->setItem(i, 3, i4);

                QTableWidgetItem *i5 = new QTableWidgetItem(qry.value(7).toString());
                ui->table->setItem(i, 4, i5);

                QTableWidgetItem *i6 = new QTableWidgetItem(qry.value(8).toString());
                ui->table->setItem(i, 5, i6);

                QTableWidgetItem *i7 = new QTableWidgetItem(qry.value(9).toString());
                ui->table->setItem(i, 6, i7);

                QTableWidgetItem *i8 = new QTableWidgetItem(qry.value(10).toString());
                ui->table->setItem(i, 7, i8);

                QTableWidgetItem *i9 = new QTableWidgetItem(qry.value(11).toString());
                ui->table->setItem(i, 8, i9);
                qDebug() << "Inserted row " << i;
                ++i;
                ui->table->removeRow(i);
                ui->table->insertRow(i);
                qDebug() << "Inserted row " << i;


            }
            QMessageBox::information(this, "Success", "Query executed successfully");
        }
        else{
            QMessageBox::critical(this, "Error", "Not Inserted");
        }
    }
    else {
        qDebug() << "Database connection failed";
        QMessageBox::critical(this, "Error", "Database connection failed");
    }
    database.close();
}

void purchase_voucher::on_table_cellChanged(int row, int column)
{

    int c=0;
    QSettings settings("store_tracker","database");
    dbname=settings.value("dbname",QString("store_tracker")).toString();
    qDebug()<<dbname;
    database=QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(QString("F:/database/%1.db").arg(dbname));
    if(column==0){
        if(database.open()){
            QString product=(ui->table->item(row,column)->text()).toUpper();
            QSqlQuery qry;
            qry.exec("select Product_Name,HSN_Code,Unit,CGST,SGST from purchaseinfo");
            while(qry.next()){
                if(product==qry.value(0).toString()){
                    unit=qry.value(2).toInt();
                    QTableWidgetItem *i1 = new QTableWidgetItem(qry.value(1).toString());
                    ui->table->setItem(row,1,i1);
                    QTableWidgetItem *i2 = new QTableWidgetItem(qry.value(3).toString());
                    ui->table->setItem(row,4,i2);
                    QTableWidgetItem *i3 = new QTableWidgetItem(qry.value(4).toString());
                    ui->table->setItem(row,6,i3);
                    c++;
                }
            }
            if(c==0){
                p=new purchase();
                p->show();
            }
        }
        database.close();
    }

//    if(column==2){
//        if(database.open()){
//            qDebug()<<id_no;
//            int quantity=ui->table->item(row,column)->text().toInt();
//            unit+=quantity;
//            QSqlQuery qry1;
//            qry1.prepare("update purchaseinfo set Unit=:unit where Id=:id_no");
//            qry1.bindValue(":unit",unit);
//            qry1.bindValue(":id_no",id_no);
//            qry1.exec();
//        }
//        database.close();
//    }
    if(column==3){

        int price=ui->table->item(row,column)->text().toInt();
        int quantity=ui->table->item(row,column-1)->text().toInt();
        double sum=price*quantity;
        QString cgst=ui->table->item(row,4)->text();
        double tax = 0.0;

        if(cgst=="2.5%"){
            tax=2.5;
        }
        else if(cgst=="6%"){
            tax=6;
        }
        else if(cgst=="8%"){
            tax=8;
        }
        else if(cgst=="12%"){
            tax=12;
        }
        double crate=(tax/100)*sum;
        double srate=(tax/100)*sum;
        sum+=crate;
        sum+=srate;
        QTableWidgetItem *i1 = new QTableWidgetItem(QString::number(crate));
        ui->table->setItem(row,5,i1);
        QTableWidgetItem *i2 = new QTableWidgetItem(QString::number(srate));
        ui->table->setItem(row,7,i2);
        QTableWidgetItem *i3 = new QTableWidgetItem(QString::number(sum));
        ui->table->setItem(row,8,i3);
        total+=sum;
        ui->total->setText(QString::number(total));
        if(row<count){
            total=0.0;
            ui->total->setText(QString::number(total));
        }
        count++;
    }
    int lastColumn = ui->table->columnCount() - 1;
    if (column == lastColumn && row < ui->table->rowCount() - 1)
    {
        // Move to the next row if the last cell is edited
        ui->table->setCurrentCell(row + 1, 0);
    }
    else if (column == lastColumn && row == ui->table->rowCount() - 1)
    {
        // Add a new row and move to the first cell of the new row
        ui->table->insertRow(ui->table->rowCount());
        ui->table->setCurrentCell(row + 1, 0);
    }
}









void purchase_voucher::on_create_clicked()
{
    emit call();
}





void purchase_voucher::on_company_editingFinished()
{
    int c=0;
    QSettings settings("store_tracker","database");
    dbname=settings.value("dbname",QString("store_tracker")).toString();
    qDebug()<<dbname;
    database=QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(QString("F:/database/%1.db").arg(dbname));
    if(database.open()){
        QSqlQuery qry;
        qry.exec("select Username from purchase_companyinfo");
        QString cname=ui->company->text();
        while(qry.next()){
            if(cname.toUpper()==qry.value(0))
            {
                c++;
            }
        }
        if(c==0){
            QMessageBox::information(this,"Message","The company doesn't exist so fill a company details using create button");
        }
    }
    database.close();
}


void purchase_voucher::on_save_clicked()
{
    int rcount=0;
    int numRows = ui->table->rowCount();
    int numCols = ui->table->columnCount();
    QSettings settings("store_tracker","database");
    dbname=settings.value("dbname",QString("store_tracker")).toString();
    qDebug()<<dbname;
    database=QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(QString("F:/database/%1.db").arg(dbname));
    if(database.open()){
        QSqlQuery qry1;
        qry1.exec("create table purchase_voucher""(Id integer primary key autoincrement,""Voucher_No integer(10),""Date varchar(20),""Company_Name varchar(50),""Product_Name varchar(50),""HSN_Code integer(10),""Quantity integer(20),""Price integer(20),""CGST varchar(20),""CGST_Rate integer(20),""SGST varchar(20),""SGST_Rate integer(20),""Total integer(20),""Grand_Total integer(20))");
        for (int row = 0; row < numRows-1; row++) {
            for (int col = 0; col < numCols; col++) {

                     int Voucher_No=ui->no->text().toInt();
                     QString Date=ui->date->text();
                     QString Company_Name=(ui->company->text()).toUpper();
                     QString Product_Name=(ui->table->item(row,col)->text()).toUpper();
                     col++;
                     int HSN_Code=(ui->table->item(row,col)->text()).toInt();
                     col++;
                     int Quantity=(ui->table->item(row,col)->text()).toInt();
                     qry1.prepare("Select Unit from purchaseinfo where Product_Name=:Product_Name");
                     qry1.bindValue(":Product_Name",Product_Name);
                     qry1.exec();
                     int units=qry1.value(0).toInt();
                     units+=Quantity;
                     qry1.prepare("update purchaseinfo set Unit=:units where Product_Name=:Product_Name");
                     qry1.bindValue(":units",units);
                     qry1.bindValue(":Product_Name",Product_Name);
                     qry1.exec();
                     col++;
                     int Price=(ui->table->item(row,col)->text()).toInt();
                     col++;
                     QString CGST=ui->table->item(row,col)->text();
                     col++;
                     int CGST_Rate=(ui->table->item(row,col)->text()).toInt();
                     col++;
                     QString SGST=ui->table->item(row,col)->text();
                     col++;
                     int SGST_Rate=(ui->table->item(row,col)->text()).toInt();
                     col++;
                     int Total=(ui->table->item(row,col)->text()).toInt();
                     int Grand_Total=(ui->total->text()).toInt();
                     qDebug()<<Voucher_No<<Date<<Company_Name<<Product_Name<<HSN_Code<<Quantity<<Price<<CGST<<CGST_Rate<<SGST<<SGST_Rate<<Total<<Grand_Total;

                     if(Voucher_No!=0 && Date!="" && Company_Name!="" && Product_Name!="" && HSN_Code!=0 && Quantity!=0 && Price!=0 && CGST!="" && CGST_Rate!=0 && SGST!="" && SGST_Rate!=0 && Total!=0 && Grand_Total!=0){
                         qry1.prepare("insert into purchase_voucher(Voucher_No,Date,Company_Name,Product_Name,HSN_Code,Quantity,Price,CGST,CGST_Rate,SGST,SGST_Rate,Total,Grand_Total)""Values(:Voucher_No,:Date,:Company_Name,:Product_Name,:HSN_Code,:Quantity,:Price,:CGST,:CGST_Rate,:SGST,:SGST_Rate,:Total,:Grand_Total)");
                         qry1.bindValue(":Voucher_No",Voucher_No);
                         qry1.bindValue(":Date",Date);
                         qry1.bindValue(":Company_Name",Company_Name);
                         qry1.bindValue(":Product_Name",Product_Name);
                         qry1.bindValue(":HSN_Code",HSN_Code);
                         qry1.bindValue(":Quantity",Quantity);
                         qry1.bindValue(":Price",Price);
                         qry1.bindValue(":CGST",CGST);
                         qry1.bindValue(":CGST_Rate",CGST_Rate);
                         qry1.bindValue(":SGST",SGST);
                         qry1.bindValue(":SGST_Rate",SGST_Rate);
                         qry1.bindValue(":Total",Total);
                         qry1.bindValue(":Grand_Total",Grand_Total);
                         if(qry1.exec()){
                             qDebug()<<Voucher_No<<Date<<Company_Name<<Product_Name<<HSN_Code<<Quantity<<Price<<CGST<<CGST_Rate<<SGST<<SGST_Rate<<Total<<Grand_Total;
                             rcount++;
                             qDebug()<<rcount;
                         }
                     }
            }
        }
        qDebug()<<rcount<<numRows;
        if(rcount==numRows-1){
            qDebug()<<rcount<<numRows;
            QMessageBox::information(this,"Success","The row is inserted successfully");
            database.close();
            dbname=settings.value("dbname",QString("store_tracker")).toString();
            qDebug()<<dbname;
            database=QSqlDatabase::addDatabase("QSQLITE");
            database.setDatabaseName(QString("F:/database/%1.db").arg(dbname));
            if(database.open()){
                QSqlQuery qry;
                qry.exec("select Voucher_No from purchase_voucher order by Voucher_No desc LIMIT 1");
                if(qry.next()){
                    int id_number=qry.value(0).toInt();
                    id_number++;
                    ui->no->setText(QString::number(id_number));
                }
                else{
                    ui->no->setText("1");
                }
                ui->company->setText("");
                ui->table->clearContents();
                ui->table->setRowCount(1);
            }
        }
        else{
            QMessageBox::information(this,"Failed","The row is failed to get inserted");

        }
    }
    else{
        QMessageBox::information(this,"Failed","Database is not opened");

    }

}


void purchase_voucher::on_alter_clicked()
{
    m->show();
}

