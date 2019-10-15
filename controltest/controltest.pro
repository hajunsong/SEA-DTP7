#-------------------------------------------------
#
# Project created by QtCreator 2019-08-22T14:07:42
#
#-------------------------------------------------

QT += core gui

TEMPLATE = lib
CONFIG += plugin

TARGET = controltest

DESTDIR = ../lib

target.path = /mnt/mtd5/robots
INSTALLS += target

CRBLIB_DIR = $$_PRO_FILE_PWD_/../coreDev/crobot

INCLUDEPATH += $${CRBLIB_DIR}/include


LIBS += -L$$CRBLIB_DIR/lib -lcrobot_poky -lm

INCLUDEPATH += ../coreDev/cui/include/ \
            ../coreDev/include/

SOURCES += \
    form.cpp \
    connectmain.cpp \
    robotarm.cpp

HEADERS +=\
        ../coreDev/crobot/include/crbtype.h\
        ../coreDev/cui/include/cuiapi.h\
        form.h \
        robotarm.h \
        functions.h \
        variables.h

FORMS += \
    form.ui
