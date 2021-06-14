include($$PWD/../include/allocation.prf)

QT -= gui

TEMPLATE = lib

DESTDIR = $$PWD/../lib

CONFIG += c++11 console
DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
    cJSON.c \
    datapacket.cpp \
    pluginsHttp.cpp \
    threadPool.cpp \
    treeNode.cpp \
    businessRequest.cpp


HEADERS += \
    cJSON.h \
    datapacket.h \
    pluginsHttp.h \
    threadPool.h \
    businessRequest.h

