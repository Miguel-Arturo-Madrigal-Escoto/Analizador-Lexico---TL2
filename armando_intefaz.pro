#-------------------------------------------------
#
# Project created by QtCreator 2022-01-29T21:52:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = armando_intefaz
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    token.cpp \
    lexer.cpp

HEADERS  += mainwindow.h \
    token.h \
    lexer.h

FORMS    += mainwindow.ui
