#-------------------------------------------------
#
# Project created by QtCreator 2013-03-07T11:07:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RncAcqGui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialogmarco.cpp \
    dialogfecharsb.cpp \
    dialogabrirsb.cpp \
    dialogdefinidousuario.cpp

HEADERS  += \
    mainwindow.h \
    dialogmarco.h \
    dialogfecharsb.h \
    dialogabrirsb.h \
    dialogdefinidousuario.h

FORMS    += mainwindow.ui \
    dialogmarco.ui \
    dialogfecharsb.ui \
    dialogabrirsb.ui \
    dialogdefinidousuario.ui \
    dialogabrirsb.ui

RESOURCES += \
    Gauge.qrc

OTHER_FILES +=
