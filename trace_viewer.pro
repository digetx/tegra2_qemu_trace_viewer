#-------------------------------------------------
#
# Project created by QtCreator 2014-09-24T19:35:01
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = trace_viewer
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
    mainwindow.cpp \
    device.cpp \
    traceipc.cpp \
    tracecore.cpp \
    errorstablewidget.cpp \
    tracetabwidget.cpp \
    cdmatrace.cpp \
    tracedev.cpp

SOURCES += devices/apb_dmadev.cpp \
    devices/apb_miscdev.cpp \
    devices/cardev.cpp \
    devices/flowdev.cpp \
    devices/gpiodev.cpp \
    devices/pmcdev.cpp \
    devices/rtcdev.cpp \
    devices/sdhcidev.cpp \
    devices/timer_usdev.cpp \
    devices/timerdev.cpp \
    devices/uartdev.cpp \
    devices/emcdev.cpp \
    devices/mcdev.cpp \
    devices/gizmodev.cpp \
    devices/fusedev.cpp \
    devices/dcdev.cpp \
    devices/bsedev.cpp \
    devices/host1x_channeldev.cpp \
    devices/host1x_syncdev.cpp \
    devices/arb_semadev.cpp \
    devices/arb_gnt_ictlrdev.cpp \
    devices/evpdev.cpp \
    devices/ictlr_pridev.cpp \
    devices/ictlr_secdev.cpp \
    devices/ictlr_tridev.cpp \
    devices/ictlr_quaddev.cpp \
    devices/host1x_dev.cpp \
    devices/gr2ddev.cpp

HEADERS  += mainwindow.h \
    iomap.h \
    sizes.h \
    device.h \
    register.h \
    traceipc.h \
    tracecore.h \
    errorstablewidget.h \
    tracetabwidget.h \
    cdmatrace.h \
    tracedev.h

HEADERS  += devices/host1x_dev.h \
    devices/gr2ddev.h \
    devices/apb_dmadev.h \
    devices/apb_miscdev.h \
    devices/cardev.h \
    devices/flowdev.h \
    devices/gpiodev.h \
    devices/pmcdev.h \
    devices/rtcdev.h \
    devices/sdhcidev.h \
    devices/timer_usdev.h \
    devices/timerdev.h \
    devices/uartdev.h \
    devices/emcdev.h \
    devices/mcdev.h \
    devices/gizmodev.h \
    devices/fusedev.h \
    devices/dcdev.h \
    devices/bsedev.h \
    devices/host1x_channeldev.h \
    devices/host1x_cmd_processor.h \
    devices/host1x_syncdev.h \
    devices/arb_semadev.h \
    devices/arb_gnt_ictlrdev.h \
    devices/evpdev.h \
    devices/ictlr_pridev.h \
    devices/ictlr_secdev.h \
    devices/ictlr_tridev.h \
    devices/ictlr_quaddev.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    android/src/org/qtproject/qt5/android/bindings/QtActivity.java \
    android/src/org/qtproject/qt5/android/bindings/QtApplication.java \
    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl \
    android/AndroidManifest.xml \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android/res/layout/splash.xml \
    android/res/values-et/strings.xml \
    android/res/values-zh-rCN/strings.xml \
    android/res/values-zh-rTW/strings.xml \
    android/res/values-es/strings.xml \
    android/res/values-nb/strings.xml \
    android/res/values-ms/strings.xml \
    android/res/values-it/strings.xml \
    android/res/values-pl/strings.xml \
    android/res/values-id/strings.xml \
    android/res/values-pt-rBR/strings.xml \
    android/res/values-rs/strings.xml \
    android/res/values-fr/strings.xml \
    android/res/values-ro/strings.xml \
    android/res/values-nl/strings.xml \
    android/res/values-de/strings.xml \
    android/res/values-ja/strings.xml \
    android/res/values-ru/strings.xml \
    android/res/values-fa/strings.xml \
    android/res/values-el/strings.xml \
    android/version.xml
