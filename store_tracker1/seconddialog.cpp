#include "seconddialog.h"
#include "ui_seconddialog.h"
#include <QMessageBox>
#include <QStandardItemModel>
SecondDialog::SecondDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecondDialog)
{
    ui->setupUi(this);
    QPalette palette;
    QPixmap backgroundImage(":/blue.jpg");
    palette.setBrush(QPalette::Window, backgroundImage);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
    this->setWindowTitle("User Management");
}

SecondDialog::~SecondDialog()
{
    delete ui;
}

void SecondDialog::on_pushButton_clicked()
{
    QSettings settings("store_tracker","database");
    dbname=settings.value("dbname",QString("store_tracker")).toString();
    qDebug()<<dbname;
    database=QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(QString("F:/database/%1.db").arg(dbname));

    if(database.open()){
        int sum=0;
        QSqlQuery qry;
        qry.prepare("create table add_users""(username varchar(20)primary key,""password varchar(20),""email varchar(30),""phone_no varchar(15))");
        qry.exec();

        QString username=ui->uname->text();
        QRegularExpression unameRegex("[A-Za-z\\s]+");
        QRegularExpressionMatch unameMatch = unameRegex.match(username);
        if(unameMatch.hasMatch()){
            sum=sum+1;
        }
        else{
            QMessageBox::information(this,"Error","Please enter the correct User Name");
        }
        QString password=ui->pass->text();
        QRegularExpression passRegex("[A-Za-z0-9\\s]+");
        QRegularExpressionMatch passMatch = passRegex.match(password);
        if(passMatch.hasMatch()){
            sum=sum+1;
        }
        else{
            QMessageBox::information(this,"Error","Please enter the correct Password([A-Za-z0-9\\s])");
        }
        QString email=ui->id->text();
        QRegularExpression eRegex("[A-Za-z0-9._@]+");
        QRegularExpressionMatch eMatch = eRegex.match(email);
        if(eMatch.hasMatch()){
            sum=sum+1;
        }
        else{
            QMessageBox::information(this,"Error","Please enter the correct Email([A-Za-z0-9._@])");
        }
        QString phone_no=ui->no->text();
        QRegularExpression pnoRegex("[0-9]{10}");
        QRegularExpressionMatch pnoMatch = pnoRegex.match(phone_no);
        if(pnoMatch.hasMatch()){
            sum=sum+1;
        }
        else{
            QMessageBox::information(this,"Error","Please enter the correct Phone number");
        }
        if(username!="" && password!="" && email!="" && phone_no!="" && sum==4){
            qry.prepare("INSERT INTO add_users (username, password, email, phone_no)" "VALUES (:username, :password, :email, :phone_no)");

            qry.bindValue(":username",username);
            qry.bindValue(":password",password);
            qry.bindValue(":email",email);
            qry.bindValue(":phone_no",phone_no);


            if(qry.exec()){
                QMessageBox::information(this,"Inserted","Data Inserted Successfully");
                ui->uname->setText("");
                ui->pass->setText("");
                ui->id->setText("");
                ui->no->setText("");
            }
            else{
                QMessageBox::information(this,"Not Inserted","Data is not inserted");
            }
        }
        else{
            QMessageBox::information(this,"Not Connected","Database is not connected");
        }
    }
    database.close();
    QSqlDatabase::removeDatabase(QString("%1.db").arg(dbname));
}


void SecondDialog::on_view_clicked()
{
    QSettings settings("store_tracker","database");
    dbname=settings.value("dbname",QString("store_tracker")).toString();
    qDebug()<<dbname;
    database=QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(QString("F:/database/%1.db").arg(dbname));
    if(database.open()){
        QSqlQueryModel *model=new QSqlQueryModel();
        QSqlQuery qry;
        qry.prepare("select username, password, email, phone_no from add_users");
        qry.exec();
        model->setQuery(qry);
        ui->table->setModel(model);
        qDebug()<<(model->rowCount());
    }
    database.close();

}


void SecondDialog::on_delete_2_clicked()
{
    QSettings settings("store_tracker","database");
    dbname=settings.value("dbname",QString("store_tracker")).toString();
    qDebug()<<dbname;
    database=QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(QString("F:/database/%1.db").arg(dbname));
    if(database.open()){
        QModelIndex index=ui->table->currentIndex();
        qDebug()<<index;
        if (!index.isValid()) {
            // No row is selected
            qDebug() << "No row is selected";
            return;
        }
        QVariant id = ui->table->model()->data(ui->table->model()->index(index.row(), 0));
        QString user = id.toString();
        QSqlQuery query;
        query.prepare("DELETE FROM add_users WHERE username =:user");
        query.bindValue(":user",user);
        query.exec();
        QSqlQueryModel *model = new QSqlQueryModel();
        query.prepare("select * from add_users");
        query.exec();
        model->setQuery(query);
        ui->table->setModel(model);

    }
    database.close();
}

