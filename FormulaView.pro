#-------------------------------------------------
#
# Project created by QtCreator 2018-04-21T13:10:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FormulaView
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    functionParser/ast.cpp \
    functionParser/astGraphics.cpp \
    functionParser/tokenizer.cpp \
    functionParser/utilities.cpp \
        main.cpp \
        widget.cpp \
    FormulaWidget.cpp

HEADERS += \
    functionParser/ast.h \
    functionParser/astGraphics.h \
    functionParser/tokenizer.h \
    functionParser/utilities.h \
        widget.h \
    FormulaWidget.h

FORMS += \
        widget.ui

DISTFILES +=

INCLUDEPATH += $$PWD/functionParser

INCLUDEPATH += $$_PRO_FILE_PWD_
