QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
TARGET=Store_Tracker
SOURCES += \
    company_info.cpp \
    company_list.cpp \
    login.cpp \
    main.cpp \
    menu.cpp \
    messagebox.cpp \
    prtoducts.cpp \
    purchase.cpp \
    purchase_voucher.cpp \
    sales.cpp \
    seconddialog.cpp \
    user.cpp \
    widget.cpp

HEADERS += \
    company_info.h \
    company_list.h \
    login.h \
    menu.h \
    messagebox.h \
    prtoducts.h \
    purchase.h \
    purchase_voucher.h \
    sales.h \
    seconddialog.h \
    user.h \
    widget.h

FORMS += \
    company_info.ui \
    company_list.ui \
    login.ui \
    menu.ui \
    messagebox.ui \
    prtoducts.ui \
    purchase.ui \
    purchase_voucher.ui \
    sales.ui \
    seconddialog.ui \
    user.ui \
    widget.ui

RESOURCES += \
    My_Resources.qrc

    RC_ICONS=spidey.ico

DISTFILES +=




