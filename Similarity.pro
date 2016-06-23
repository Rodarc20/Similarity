#-------------------------------------------------
#
# Project created by QtCreator 2016-06-21T21:45:18
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Similarity
TEMPLATE = app


SOURCES += main.cpp\
        buscador.cpp \
    operaciones.cpp \
    resultmodel.cpp

HEADERS  += buscador.h \
    operaciones.h \
    resultmodel.h

FORMS    += buscador.ui

CONFIG += c++11 thread
