#-------------------------------------------------
#
# Project created by QtCreator 2018-02-20T16:19:15
#
#-------------------------------------------------

QT       += sql core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = app2
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
        main.cpp \
        mainwindow.cpp \
    enc.cpp \
    writecard.cpp

HEADERS += \
        mainwindow.h \
    dcrf32.h \
    enc.h \
    writecard.h

FORMS += \
    mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./ -ldcrf32
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./ -ldcrf32d

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

DISTFILES += \
    dcrf32.lib \
    dcrf32.dll \
    ../build-app2-Desktop_Qt_5_10_1_MinGW_32bit-Release/log.txt

INCLUDEPATH += $$PWD/../build-app2-Desktop_Qt_5_10_1_MinGW_32bit-Release
DEPENDPATH += $$PWD/../build-app2-Desktop_Qt_5_10_1_MinGW_32bit-Release
