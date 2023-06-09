#ifndef COMPANY_LIST_H
#define COMPANY_LIST_H

#include <QWidget>
#include <QSettings>
#include <QtSql>
namespace Ui {
class company_list;
}

class company_list : public QWidget
{
    Q_OBJECT

public:
    explicit company_list(QWidget *parent = nullptr);
    ~company_list();

private slots:
    void on_show_clicked();

private:
    Ui::company_list *ui;
    QString dbname;
    QSqlDatabase database;
    QSqlQueryModel *model;
};

#endif // COMPANY_LIST_H
