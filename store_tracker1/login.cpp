#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    this->setWindowTitle("Company Login");
    QPalette palette;
    QPixmap backgroundImage(":/blue.jpg");
    palette.setBrush(QPalette::Window, backgroundImage);
    this->setAutoFillBackground(true);
    this->setPalette(palette);

}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    QString file_path=QString("F:/database/%1.db").arg(ui->lineEdit->text());
    if(QFile::exists(file_path)){
        QSettings settings("store_tracker","database");
        settings.setValue("dbname",ui->lineEdit->text());
        this->close();
        u->show();
    }
    else{
        this->close();
        w->show();
    }
}

