#ifndef COMPANY_INFO_H
#define COMPANY_INFO_H

#include "qsqldatabase.h"
#include "ui_company_info.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QFileInfo>

namespace Ui {
class company_info;
}

class company_info : public QDialog
{
    Q_OBJECT

public:
    explicit company_info(QWidget *parent = nullptr);
    ~company_info();

signals:
    void setDataSig(QString name);


public slots:
    void uiChange();

private slots:

    void on_save_clicked();

//    void on_from_activated(int index);

//    void on_to_activated(int index);

//    void on_to_currentIndexChanged(int index);

    void on_from_currentTextChanged(const QString &arg1);

private:

    Ui::company_info *ui;
    QSqlDatabase database;


     QString name;
     QString dbname;
};

#endif // COMPANY_INFO_H
