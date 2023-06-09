#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <company_info.h>
#include <purchase.h>
#include <seconddialog.h>
#include <sales.h>
#include <prtoducts.h>
#include <company_list.h>
#include <purchase_voucher.h>
namespace Ui {
class menu;
}

class menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();
signals:
    void setUi();
public slots:
    void uiChange();
    void uiChange1();
    void edited();

private slots:
    //void on_menu_windowTitleChanged(const QString &title);

    void on_actionUser_Management_triggered();

    void on_actionComapny_Details_triggered();

    void on_pushButton_clicked();

    void on_sales_clicked();

    void on_actionProducts_triggered();

    void on_actionCompany_triggered();

    void on_products_clicked();

private:
   Ui::menu *ui;
   company_info *comp,*comp1;
   purchase *p;
   Sales *s;
   Prtoducts *product;
   company_list *list;
   purchase_voucher *voucher,*voucher1;
   //purchase *pur;
};

#endif // MENU_H
