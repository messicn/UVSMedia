QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

INCLUDEPATH += $$PWD/../UVS_Common

win32 {
    INCLUDEPATH += $$PWD/../../WindowsSDK/inc
    contains(QT_ARCH, x86_64) {
        LIBS += $$PWD/../../WindowsSDK/lib/x64/UVSMedia.lib
        DLLDIR = $$PWD/../../WindowsSDK/lib/x64/*.dll
    } else {
        LIBS += $$PWD/../../WindowsSDK/lib/win32/UVSMedia.lib
        DLLDIR = $$PWD/../../WindowsSDK/lib/win32/*.dll
    }

    UVSDLL = $$replace(DLLDIR, /, \\)
    OUTDIR = $$replace(OUT_PWD, /, \\)
    QMAKE_POST_LINK += copy /Y $$UVSDLL $$OUTDIR
}

unix:!macx {
    INCLUDEPATH += $$PWD/../../LinuxSDK/inc
    contains(QT_ARCH, x86_64) {
        UVSLIB = $$PWD/../../LinuxSDK/lib/x86_64
    } else {
        UVSLIB = $$PWD/../../LinuxSDK/lib/aarch64
    }
    LIBS += -L$$UVSLIB $$UVSLIB/UVSMedia.so
    QMAKE_LFLAGS += -lrt -Wl,-rpath-link=$$UVSLIB -Wl,-rpath=.
    QMAKE_POST_LINK += cp -fd $$UVSLIB/*.so* $$OUT_PWD
}

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../UVS_Common/DevManager.cpp \
    main.cpp \
    dialog.cpp

HEADERS += \
    dialog.h

FORMS += \
    dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
