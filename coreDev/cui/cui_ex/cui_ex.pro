#

QT += core gui

TEMPLATE = lib
# No shared library version
CONFIG += plugin

cg3300|cg3300_dbg {
    TARGET = customui
}


DESTDIR = ../lib

target.path=/mnt/mtd5/
INSTALLS += target

INCLUDEPATH += ../include ../../include

SOURCES += main.c \
    formmainwindow.cpp \
    formai.cpp \
    formao.cpp \
    formdata.cpp \
    formdi.cpp \
    formdo.cpp \
    formio.cpp \
    formjog.cpp \
    formmain.cpp \
    formrobotconf.cpp \
    formrun.cpp \
    formtest.cpp \
    formtesthome.cpp \
    formteststatus.cpp \
    formuserparams.cpp \
    cxwidget.cpp \
    dlgnumber.cpp \
    dlgprogram.cpp \
    dlgtextinput.cpp \
    dlgzeroing.cpp \
    formtestworldzone.cpp \
    formtestprogram.cpp \
    formtestvariable.cpp \
    formtestsdo.cpp \
    formtestsave.cpp \
    formtestinching.cpp


HEADERS  += formmainwindow.h \
    ../include/cuiapi.h \
    ../include/cuiecat.h\
    ../../include/cntype.h \
    formai.h \
    formao.h \
    formdata.h \
    formdi.h \
    formdo.h \
    formio.h \
    formjog.h \
    formmain.h \
    formrobotconf.h \
    formrun.h \
    formtest.h \
    formtesthome.h \
    formteststatus.h \
    formuserparams.h \
    cxwidget.h \
    dlgnumber.h \
    dlgprogram.h \
    dlgtextinput.h \
    dlgzeroing.h \
    cerror.h \
    formtestworldzone.h \
    formtestprogram.h \
    formtestvariable.h \
    formtestsdo.h \
    formtestsave.h \
    formtestinching.h


FORMS    += formmainwindow.ui \
    formai.ui \
    formao.ui \
    formdata.ui \
    formdi.ui \
    formdo.ui \
    formio.ui \
    formjog.ui \
    formmain.ui \
    formrobotconf.ui \
    formrun.ui \
    formtest.ui \
    formtesthome.ui \
    formteststatus.ui \
    formuserparams.ui \
    cxwidget.ui \
    dlgnumber.ui \
    dlgprogram.ui \
    dlgtextinput.ui \
    dlgzeroing.ui \
    formtestworldzone.ui \
    formtestprogram.ui \
    formtestvariable.ui \
    formtestsdo.ui \
    formtestsave.ui \
    formtestinching.ui

RESOURCES += \
    resources.qrc





