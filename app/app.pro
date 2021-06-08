include($$PWD/../include/allocation.prf)

TEMPLATE = app
TARGET = nginx

DESTDIR = $$PWD/../bin

CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.c \

unix:!macx: LIBS += -L$$PWD/../lib/ -lCoreData -lPlugins

QMAKE_RPATHDIR += $$PWD/../lib


