TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    attribution.cpp \
    metadatamanager.cpp \
    tablemetadata.cpp

SUBDIRS += \
    MetaManager.pro

DISTFILES += \
    MetaManager.pro.user

HEADERS += \
    attribution.h \
    global.h \
    metadatamanager.h \
    tableMetadata.h

LIBS +=  -L /usr/local/lib/ -lconfig++
