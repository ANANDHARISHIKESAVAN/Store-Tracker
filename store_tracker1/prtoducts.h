#ifndef PRTODUCTS_H
#define PRTODUCTS_H

#include "qsqldatabase.h"
#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QFileInfo>
namespace Ui {
class Prtoducts;
}

class Prtoducts : public QWidget
{
    Q_OBJECT

public:
    explicit Prtoducts(QWidget *parent = nullptr);
    ~Prtoducts();

private slots:
    void on_show_clicked();

private:
    Ui::Prtoducts *ui;
    QString dbname;
    QSqlDatabase database;
    QSqlQueryModel *model;
};

#endif // PRTODUCTS_H
