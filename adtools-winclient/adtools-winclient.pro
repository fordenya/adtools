QT       += core network widgets

CONFIG += qt c++11

TARGET = adtools-winclient
TEMPLATE = app


SOURCES += \
    main.cpp \
    clientnotifierthread.cpp \
    hostinfo.cpp \
    #commandmonitor.cpp \
    #datareceiver.cpp
    systemtray.cpp \
    settings.cpp \
    mainthread.cpp

HEADERS += \
    clientnotifierthread.h \
    hostinfo.h \
    #commandmonitor.h \
    #datareceiver.h
    systemtray.h \
    settings.h \
    settings_dialog.h \
    mainthread.h \
    settingsdata.h


RESOURCES += \
    resources.qrc

FORMS += \
    settings_dialog.ui
