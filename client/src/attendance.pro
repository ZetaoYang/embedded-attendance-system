#-------------------------------------------------
#
# Project created by QtCreator 2017-07-04T10:59:42
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = attendance
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
#For ARM S3c2410
DEFINES += ARM

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp\
        widget.cpp \
    keyboard.c \
    get_key.c \
    sqlite.cpp \
    mythread.cpp \
    cglobal.cpp \
    dialog.cpp \
    utils.c

HEADERS  += widget.h \
    kbd_types.h \
    keyboard.h \
    keyboard/get_key.h \
    keyboard/kbd_types.h \
    keyboard/keyboard.h \
    sqlite/sqlite.h \
    mythread.h \
    cglobal.h \
    dialog.h \
    utils/utils.h

FORMS    += widget.ui \
    dialog.ui

RESOURCES += \
    attendance.qrc
# open debug window
#CONFIG += console
