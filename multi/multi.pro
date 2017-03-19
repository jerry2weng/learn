#-------------------------------------------------
#
# Project created by QtCreator 2017-03-14T10:18:05
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += testlib
QT       += serialport
QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = multi
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    usb/usb_hid.cpp \
    Tcp/my_tcp.cpp \
    Com/my_serialport.cpp \
    mainwindow/mainwindow.cpp \
    UDP/udp.cpp

HEADERS  += \
    usb/usb_hid.h \
    Tcp/my_tcp.h \
    Com/my_serialport.h \
    mainwindow/mainwindow.h \
    UDP/udp.h
    usb/usb_hid_lib/hidapi.h

FORMS    += \
    usb/usb_hid.ui \
    Tcp/my_tcp.ui \
    Com/my_serialport.ui \
    mainwindow/mainwindow.ui \
    UDP/udp.ui



LIBS     += -LC:/Users/Administrator/Desktop/QT_upmachine_multi/multi/usb/usb_hid_lib -lhidapi
