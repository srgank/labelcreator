-------------------------------------------------
#
# Project created by QtCreator 2017-12-19T20:06:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = PLabel
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
#DESTDIR = ../release
#CONFIG += release
#INCLUDEPATH += ./GeneratedFiles \
#    ./GeneratedFiles/Release \

#DEPENDPATH += .
#MOC_DIR += ./GeneratedFiles/release
#OBJECTS_DIR += release
#UI_DIR += ./GeneratedFiles
#RCC_DIR += ./GeneratedFiles

#Header files
HEADERS += ./ean13.h \
    ./plabel.h \
    ./qabouts.h \
    ./qarticle.h \
    ./qgscene.h \
    ./qlab1picture.h \
    ./qlab1pixmapitem.h \
    ./qlabellicence.h \
    ./qmymenuleft.h \
    ./qsfind.h \
    ./qspagesettings.h \
    ./qstablewidget.h \
    ./qstablewidgetdelegate.h

#Source files
SOURCES += ./ean13.cpp \
    ./main.cpp \
    ./plabel.cpp \
    ./qabouts.cpp \
    ./qarticle.cpp \
    ./qgscene.cpp \
    ./qlab1picture.cpp \
    ./qlab1pixmapitem.cpp \
    ./qlabellicence.cpp \
    ./qmymenuleft.cpp \
    ./qsfind.cpp \
    ./qspagesettings.cpp \
    ./qstablewidget.cpp \
    ./qstablewidgetdelegate.cpp

#Forms
FORMS += ./plabel.ui \
    ./qabouts.ui \
    ./qarticle.ui \
    ./qlabellicence.ui \
    ./qmymenuleft.ui \
    ./qsfind.ui \
    ./qspagesettings.ui

#Resource file(s)
RESOURCES += ./plabel.qrc


