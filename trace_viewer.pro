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

SOURCES += apb_dmadev.cpp \
    apb_miscdev.cpp \
    cardev.cpp \
    flowdev.cpp \
    gpiodev.cpp \
    pmcdev.cpp \
    rtcdev.cpp \
    sdhcidev.cpp \
    timer_usdev.cpp \
    timerdev.cpp \
    uartdev.cpp \
    emcdev.cpp \
    mcdev.cpp \
    gizmodev.cpp \
    fusedev.cpp \
    dcdev.cpp \
    bsedev.cpp \
    host1x_channeldev.cpp \
    host1x_syncdev.cpp \
    arb_semadev.cpp \
    arb_gnt_ictlrdev.cpp \
    evpdev.cpp \
    ictlr_pridev.cpp \
    ictlr_secdev.cpp \
    ictlr_tridev.cpp \
    ictlr_quaddev.cpp \
    host1x_dev.cpp \
    gr2ddev.cpp

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
    tracedev.h \
    host1x_dev.h \
    gr2ddev.h \
    apb_dmadev.h \
    apb_miscdev.h \
    cardev.h \
    flowdev.h \
    gpiodev.h \
    pmcdev.h \
    rtcdev.h \
    sdhcidev.h \
    timer_usdev.h \
    timerdev.h \
    uartdev.h \
    emcdev.h \
    mcdev.h \
    gizmodev.h \
    fusedev.h \
    dcdev.h \
    bsedev.h \
    host1x_channeldev.h \
    host1x_cmd_processor.h \
    host1x_syncdev.h \
    arb_semadev.h \
    arb_gnt_ictlrdev.h \
    evpdev.h \
    ictlr_pridev.h \
    ictlr_secdev.h \
    ictlr_tridev.h \
    ictlr_quaddev.h

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
