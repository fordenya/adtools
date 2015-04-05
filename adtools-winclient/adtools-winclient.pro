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
    systemtray.cpp

HEADERS += \
    clientnotifierthread.h \
    hostinfo.h \
    #commandmonitor.h \
    #datareceiver.h
    systemtray.h

RESOURCES += \
    resources.qrc
