QT       += core network gui widgets

CONFIG += qt c++11

TARGET = adtools-winclient
TEMPLATE = app


SOURCES += \
    main.cpp \
    netclient.cpp \
    clientnotifierthread.cpp

HEADERS += \
    netclient.h \
    clientnotifierthread.h
