QT += core network widgets

CONFIG += qt c++11

TARGET = adtools-server

SOURCES += \
    main.cpp \
    clientnotifymonitor.cpp \
    datagramreceiver.cpp

HEADERS += \
    clientnotifymonitor.h \
    datagramreceiver.h
