#-------------------------------------------------
#
# Project created by QtCreator 2020-09-04T13:08:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyStone
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

INCLUDEPATH += \
    ./Devices/ \
    ./Widgets/ \
    ./Windows/ \
    ./Enums/ \
    ./Programms/ \
    ./System/

SOURCES += \
        main.cpp \
    System/command.cpp \
    System/builder.cpp \
    Devices/alu.cpp \
    Devices/ram.cpp \
    Devices/controlunit.cpp \
    Devices/reg.cpp \
    Windows/MainWindow.cpp \
    Windows/resultwindow.cpp \
    Widgets/regsWidget.cpp \
    Widgets/ramWidget.cpp \
    Widgets/vmwidget.cpp \
    System/lexer.cpp \
    System/lexeme.cpp \
    Widgets/codeeditor.cpp \
    Widgets/linenumbers.cpp \
    System/highlighter.cpp



HEADERS += \
    System/cominfo.h \
    System/builder.h \
    System/comnames.h \
    System/command.h \
    Devices/alu.h \
    Devices/ram.h \
    Devices/controlunit.h \
    Devices/reg.h \
    Windows/MainWindow.h \
    Windows/resultwindow.h \
    Enums/comnames.h \
    Enums/RamType.h \
    Widgets/regsWidget.h \
    Widgets/ramWidget.h \
    Widgets/vmwidget.h \
    System/cpuconsts.h \
    System/lexer.h \
    System/lexeme.h \
    Widgets/codeeditor.h \
    Widgets/linenumbers.h \
    System/highlighter.h

OTHER_FILES += \
    Programms/ArrSumProg.txt \
    Programms/ArrSumMuxProg.txt
