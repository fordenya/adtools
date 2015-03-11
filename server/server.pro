QT += core network

CONFIG += qt c++11

TARGET = adtools-server

SOURCES += \
    main.cpp \
    clientnotifymonitor.cpp \
    datagramreceivethread.cpp

HEADERS += \
    clientnotifymonitor.h \
    datagramreceivethread.h
