#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QFileInfo>
#include <QSettings>

namespace Ui {
class Messagebox;
}

class Messagebox : public QDialog
{
    Q_OBJECT

public:
    explicit Messagebox(QWidget *parent = nullptr);
    ~Messagebox();
signals:
    void message1(int number);

private slots:
    void on_pushButton_clicked();

    void on_name_editingFinished();


private:
    Ui::Messagebox *ui;
    QString dbname;
    QSqlDatabase database;
};

#endif // MESSAGEBOX_H
