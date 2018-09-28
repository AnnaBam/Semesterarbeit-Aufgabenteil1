TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    language.cpp \
    membercountry.cpp \
    europa.cpp \
    token.cpp \
    atttoken.cpp \
    element.cpp

HEADERS += \
    language.h \
    membercountry.h \
    europa.h \
    token.h \
    atttoken.h \
    element.h
