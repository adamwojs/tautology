#-------------------------------------------------
#
# Project created by QtCreator 2011-10-23T11:47:07
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = tautoliogia
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cc \
    scanner.cc \
    expression.cc \
    binarycombination.cc

HEADERS += \
    scanner.h \
    expression.h \
    binarycombination.h
