#-------------------------------------------------
#
# Project created by QtCreator 2020-06-03T11:07:35
#
#-------------------------------------------------
include(src/modules/Modules.pri)
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sudoku-qt
TEMPLATE = app


SOURCES += main.cpp\
    src/widgets/mainwindow.cpp \
    src/widgets/uiboard.cpp \
    src/widgets/uicell.cpp

HEADERS  += mainwindow.h \
    src/modules/board.h \
    src/modules/cell.h \
    src/widgets/mainwindow.h \
    src/widgets/uicell.h \
    src/widgets/uiboard.h \
    src/widgets/styles/cell.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
