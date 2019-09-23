#-------------------------------------------------
#
# Project created by QtCreator 2015-10-19T12:56:17
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = coreCUI
TEMPLATE = app

DESTDIR = ../lib


target.path=/home/app
INSTALLS += target

INCLUDEPATH += .. ../include
DEPENDPATH +=  ../lib

# cnrobo library name
CONFIG(debug, release | debug) {
    BUILD_TYPE = "DEBUG"
    LCNROBO=cnrobo_d
    LCNINTERFACE=cnInterface_d
}else{
    LCNROBO=cnrobo
    LCNINTERFACE=cnInterface
    BUILD_TYPE = "RELEASE"
}

# cnrobo library folder :
CNROBO_LIB_ROOT_DIR = $$_PRO_FILE_PWD_/../lib   #$$_PRO_FILE_PWD_/../lib


# local lib directory

win32 {

    DEFINES += DEV_TYPE=DEV_PCWIN

    msvc{
        message("coreCUI for MSVC.")

        CNROBO_LIB_DIR = $$shell_path($${CNROBO_LIB_ROOT_DIR}/msvc)

        LIBS += -L$$CNROBO_LIB_DIR $${LCNROBO}.lib $${LCNINTERFACE}.lib ws2_32.lib
    }
    gcc{
        message("coreCUI for MinGW.")

        CNROBO_LIB_DIR = $${CNROBO_LIB_ROOT_DIR}/mingw

        LIBS += -L$$CNROBO_LIB_DIR -l$${LCNROBO} -l$${LCNINTERFACE} -lws2_32

    }

}

unix {

    cg3300 | cg3300_dbg {
        message("coreCUI : " $$BUILD_TYPE " build for DTP7L.")
        DEFINES += DEV_TYPE=DEV_DTP7
        CNROBO_LIB_DIR = $${CNROBO_LIB_ROOT_DIR}/linuxarm
    }
    else:cg4300 {
        message("coreCUI : " $$BUILD_TYPE " build for DTP7H.")
        DEFINES += DEV_TYPE=DEV_DTP7
        CNROBO_LIB_DIR = $${CNROBO_LIB_ROOT_DIR}/linuxarm_poky

    }else{
        message("coreCUI : " $$BUILD_TYPE " build for PC-Linux.")
        DEFINES += DEV_TYPE=DEV_PCLINUX
        CNROBO_LIB_DIR = $${CNROBO_LIB_ROOT_DIR}/linux86
    }

        LIBS += -L$$CNROBO_LIB_DIR -l$${LCNROBO} -l$${LCNINTERFACE}
}

android {
        message("coreCUI for Android.")
        CNROBO_LIB_DIR = $${CNROBO_LIB_ROOT_DIR}/android

        DEFINES += DEV_TYPE=DEV_ANDROID

        LIBS += -L$$CNROBO_LIB_DIR -l$${LCNROBO} -l$${LCNINTERFACE}

}

# deploy css file
mypackage.files = styles/
mypackage.path = /home/app
INSTALLS += mypackage

win32{
    CONFIG(debug, debug|release) {
        message("$$shell_path($$OUT_PWD/debug)")
        copydata.commands = $(COPY_FILE) "$$shell_path($$PWD/styles/defstyle.css)" "$$shell_path($$OUT_PWD/debug)"
    } else {
        message("$$shell_path($$OUT_PWD/release)")
        copydata.commands = $(COPY_FILE) "$$shell_path($$PWD/styles/defstyle.css)" "$$shell_path($$OUT_PWD/release)"
    }
}
unix{
    copydata.commands = $(COPY_FILE) $$PWD/styles/defstyle.css $$OUT_PWD
}

first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)

QMAKE_EXTRA_TARGETS += first copydata


SOURCES += main.cpp\
        mainwindow.cpp \
    dlgprogram.cpp \
    dlgtextinput.cpp \
    formmain.cpp \
    formjog.cpp \
    formdata.cpp \
    formio.cpp \
    cxwidget.cpp \
    formrun.cpp \
    dlgnumber.cpp \
    formdo.cpp \
    formdi.cpp \
    formtest.cpp \
    formteststatus.cpp \
    formuserparams.cpp \
    formtesthome.cpp \
    formrobotconf.cpp \
    dlgzeroing.cpp \
    formai.cpp \
    formao.cpp \
    formtestdatabase.cpp \
    formtestworldzone.cpp

HEADERS  += mainwindow.h \
    ../include/cnrobo.h \
    ../include/cnerror.h \
    ../include/cnhelper.h \
    ../include/cntype.h \
    ../include/appconf.h \
    ../include/robotconf.h \
    ../include/cnconftype.h \
    dlgprogram.h \
    dlgtextinput.h \
    formmain.h \
    formjog.h \
    formdata.h \
    formio.h \
    cxwidget.h \
    formrun.h \
    dlgnumber.h \
    devtype.h \
    formdo.h \
    formdi.h \
    formtest.h \
    formteststatus.h \
    formuserparams.h \
    cerror.h \
    formtesthome.h \
    formrobotconf.h \
    dlgzeroing.h \
    formai.h \
    formao.h \
    formtestdatabase.h \
    formtestworldzone.h


FORMS    += mainwindow.ui \
    dlgprogram.ui \
    dlgtextinput.ui \
    formmain.ui \
    formjog.ui \
    formdata.ui \
    formio.ui \
    formrun.ui \
    dlgnumber.ui \
    formdo.ui \
    formdi.ui \
    formtest.ui \
    formteststatus.ui \
    formuserparams.ui \
    formtesthome.ui \
    formrobotconf.ui \
    dlgzeroing.ui \
    formai.ui \
    formao.ui \
    formtestdatabase.ui \
    formtestworldzone.ui

RESOURCES += \
    resource.qrc

DISTFILES += \
    styles/defstyle.css

