#-------------------------------------------------
#
# Project created by QtCreator 2017-04-20T14:07:10
#
#-------------------------------------------------

QT       -= gui

TARGET = CanLibrary
TEMPLATE = lib
CONFIG += staticlib

QMAKE_CXXFLAGS += -fpermissive

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES += canlibrary.cpp \
    candummy.cpp

HEADERS += canlibrary.h \
    candummy.h



__arm__ {

    target.path = /usr/lib
    INSTALLS += target

    SOURCES += arduPiCANBUS/arduPi.cpp \
    arduPiCANBUS/arduPiCAN.cpp \
    arduPiCANBUS/arduPiMultiprotocol.cpp \
    arduPiCANBUS/arduPiUART.cpp \
    arduPiCANBUS/arduPiUtils.cpp \
    arduPiCANBUS/bcm2835.c


    HEADERS += arduPiCANBUS/arduPi.h \
    arduPiCANBUS/arduPiCAN.h \
    arduPiCANBUS/arduPiClasses.h \
    arduPiCANBUS/arduPiMultiprotocol.h \
    arduPiCANBUS/arduPiUART.h \
    arduPiCANBUS/arduPiUtils.h \
    arduPiCANBUS/bcm2835.hs
}






