#include< QMessageBox>
QT       += core gui sql
CONFIG +=console
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
QT += printsupport
QT       += charts
QT       += serialport
QT       += axcontainer
QT += network

QT+=sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets




# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    achat.cpp \
    arduino.cpp \
    client.cpp \
    connection.cpp \
    connexion.cpp \
    dialog.cpp \
    employes.cpp \
    equipment.cpp \
    hamza.cpp \
    jawher.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    maissa.cpp \
    menu.cpp \
    qratingbar.cpp \
    qrcode.cpp \
    rating.cpp \
    rdv.cpp \
    reduction.cpp \
    rendez_vous.cpp \
    samar.cpp \
    secdialog.cpp \
    service.cpp \
    sessionuser.cpp \
    stat.cpp \
    type_service.cpp \
    vehicule.cpp

HEADERS += \
    achat.h \
    arduino.h \
    client.h \
    connection.h \
    connexion.h \
    dialog.h \
    employes.h \
    equipment.h \
    hamza.h \
    jawher.h \
    login.h \
    mainwindow.h \
    maissa.h \
    menu.h \
    qratingbar.h \
    qrcode.h \
    rating.h \
    rdv.h \
    reduction.h \
    rendez_vous.h \
    samar.h \
    secdialog.h \
    service.h \
    sessionuser.h \
    stat.h \
    type_service.h \
    vehicule.h

FORMS += \
    dialog.ui \
    hamza.ui \
    jawher.ui \
    mainwindow.ui \
    maissa.ui \
    menu.ui \
    rdv.ui \
    samar.ui \
    secdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../../../Downloads/untitled1/resources.qrc
