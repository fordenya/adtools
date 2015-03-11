QT       += core network widgets

CONFIG += qt c++11

TARGET = adtools-winclient
TEMPLATE = app


SOURCES += \
    main.cpp \
    clientnotifierthread.cpp \
    hostinfo.cpp

HEADERS += \
    clientnotifierthread.h \
    hostinfo.h
