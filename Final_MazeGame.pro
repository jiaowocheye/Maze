#-------------------------------------------------
#
# Project created by QtCreator 2018-12-25T15:03:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Final_MazeGame
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

CONFIG += c++14

QMAKE_CXXFLAGS += -std=c++14

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    protagonistview.cpp \
    enemyview.cpp \
    myscene.cpp \
    controller.cpp \
    model.cpp \
    healthpackview.cpp \
    pathfinding.cpp \
    node.cpp \
    healthpack.cpp \
    strategy.cpp \
    penemyview.cpp \
    maptile.cpp \
    maptileview.cpp \
    gameoverdialog.cpp \
    congratsdialog.cpp \
    noenemydialog.cpp \
    mainwindow_terminal.cpp \
    gamesettingdialog.cpp

HEADERS += \
        mainwindow.h \
    protagonistview.h \
    enemyview.h \
    myscene.h \
    controller.h \
    model.h \
    world.h \
    world_global.h \
    healthpackview.h \
    pathfinding.h \
    node.h \
    healthpack.h \
    strategy.h \
    penemyview.h \
    maptile.h \
    maptileview.h \
    gameoverdialog.h \
    congratsdialog.h \
    noenemydialog.h \
    mainwindow_terminal.h \
    gamesettingdialog.h

FORMS += \
        mainwindow.ui \
    mainwindow_terminal.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc


unix: LIBS += -L$$PWD/lib/ -lworld

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
