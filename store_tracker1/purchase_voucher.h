#ifndef PURCHASE_VOUCHER_H
#define PURCHASE_VOUCHER_H

#include "qsqldatabase.h"
#include "qtablewidget.h"
#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QFileInfo>
#include <QSettings>
#include <messagebox.h>
#include <purchase.h>

namespace Ui {
class purchase_voucher;
}

class purchase_voucher : public QWidget
{
    Q_OBJECT

public:
    explicit purchase_voucher(QWidget *parent = nullptr);
    ~purchase_voucher();
signals:
    void call();
    void call1();
public slots:
    void callMessage(int num);

private slots:
    void on_table_cellChanged(int row, int column);



    void on_create_clicked();


    void on_company_editingFinished();

    void on_save_clicked();

    void on_alter_clicked();

private:
    Ui::purchase_voucher *ui;
    QString dbname;
    QSqlDatabase database;
    double total=0.0;
    int id_no=0;
    int unit=0;
    Messagebox *m;
    QSqlQueryModel *model;
    purchase *p;
    int count=0;
    company_info *c;

};

#endif // PURCHASE_VOUCHER_H
