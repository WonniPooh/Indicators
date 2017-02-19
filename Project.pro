QT += core
QT += network
QT += gui
QT += widgets
QT += sql

CONFIG += c++11

TARGET = Project
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    requestsender.cpp \
    replyhandler.cpp \
    mainwindow.cpp

HEADERS += \
    requestsender.h \
    replyhandler.h \
    mainwindow.h
