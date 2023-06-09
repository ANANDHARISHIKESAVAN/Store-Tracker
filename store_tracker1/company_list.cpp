#include "company_list.h"
#include "ui_company_list.h"

company_list::company_list(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::company_list)
{

    ui->setupUi(this);
    this->setWindowTitle("Company List");
    QPalette palette;
    QPixmap backgroundImage(":/blue.jpg");
    palette.setBrush(QPalette::Window, backgroundImage);
    this->setAutoFillBackground(true);
    this->setPalette(palette);

}

company_list::~company_list()
{
    delete ui;
}

void company_list::on_show_clicked()
{
    QSettings settings("store_tracker","database");
    dbname=settings.value("dbname",QString("store_tracker")).toString();
    qDebug()<<dbname;
    database=QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(QString("F:/database/%1.db").arg(dbname));
    if(database.open()){
        model=new QSqlQueryModel();
        QSqlQuery qry;
        qry.prepare("select Username,Address,State,Pincode,GSTInfo from purchase_companyinfo");
        qry.exec();
        model->setQuery(qry);
        ui->company_table->setModel(model);
        qDebug()<<(model->rowCount());
    }
    database.close();
}

