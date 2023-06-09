#ifndef SECONDDIALOG_H
#define SECONDDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QFileInfo>
namespace Ui {
class SecondDialog;
}

class SecondDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecondDialog(QWidget *parent = nullptr);
    ~SecondDialog();



private slots:
    void on_pushButton_clicked();

    void on_view_clicked();

    void on_delete_2_clicked();

private:
    Ui::SecondDialog *ui;

    QSqlDatabase database;
    QString dbname;
};

#endif // SECONDDIALOG_H
