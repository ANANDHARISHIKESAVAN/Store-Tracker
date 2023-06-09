#ifndef SALES_H
#define SALES_H

#include "qsqldatabase.h"
#include <QWidget>
#include <QtSql>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QFileInfo>

namespace Ui {
class Sales;
}

class Sales : public QWidget
{
    Q_OBJECT

public:
    explicit Sales(QWidget *parent = nullptr);
    ~Sales();

private slots:
    void on_save_clicked();

    void on_gst_currentTextChanged(const QString &arg1);

    void on_customer_clicked();

    void on_Regular_clicked();

private:
    Ui::Sales *ui;
    QString dbname;
    QSqlDatabase database;
};

#endif // SALES_H
