include($$PWD/../include/allocation.prf)

QT -= gui

TEMPLATE = lib

DESTDIR = $$PWD/../lib

CONFIG += c++11 console
DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
    cJSON.c \
    database.cpp \
    datapacket.cpp \
    pluginsHttp.cpp \
    CustomThreadPool.cpp \
    TreeNode.cpp


HEADERS += \
    cJSON.h \
    database.h \
    datapacket.h \
    pluginsHttp.h \
    CustomThreadPool.h

