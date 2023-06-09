#include "prtoducts.h"
#include "ui_prtoducts.h"
#include <QSettings>

Prtoducts::Prtoducts(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Prtoducts)
{
    ui->setupUi(this);
    QPalette palette;
    QPixmap backgroundImage(":/blue.jpg");
    palette.setBrush(QPalette::Window, backgroundImage);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
    this->setWindowTitle("Purchase Products List");
}

Prtoducts::~Prtoducts()
{
    delete ui;
}

void Prtoducts::on_show_clicked()
{
    QSettings settings("store_tracker","database");
    dbname=settings.value("dbname",QString("store_tracker")).toString();
    qDebug()<<dbname;
    database=QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(QString("F:/database/%1.db").arg(dbname));
    if(database.open()){
        model=new QSqlQueryModel();
        QSqlQuery qry;
        qry.prepare("select Product_Type,Product_Name,HSN_Code,Unit,Tax,CGST,SGST from purchaseinfo");
        qry.exec();
        model->setQuery(qry);
        ui->product_table->setModel(model);
        qDebug()<<(model->rowCount());
    }
    database.close();
}

