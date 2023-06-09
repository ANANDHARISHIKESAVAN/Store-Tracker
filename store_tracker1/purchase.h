#ifndef PURCHASE_H
#define PURCHASE_H

#include <QDialog>
#include <company_info.h>
#include "qsqldatabase.h"
#include "ui_purchase.h"
namespace Ui {
class purchase;
}

class purchase : public QDialog
{
    Q_OBJECT

public:
    explicit purchase(QWidget *parent = nullptr);
    ~purchase();
signals:
    void uiSet();

public slots:

    void setData(QString s);

private slots:

    void on_add_clicked();

    void on_back_clicked();

    void on_cancel_clicked();

    void on_tax_currentTextChanged(const QString &arg1);


    void on_alter_clicked();


    void on_pushButton_clicked();

    void on_purchase_table_clicked(const QModelIndex &index);

private:
    Ui::purchase *ui;
    QSqlQueryModel *model;
    QSqlDatabase database;
    QString dbname;
};

#endif // PURCHASE_H
