TEMPLATE = app
CONFIG += console c11 -Wall
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    deque.c \
    q1.c \
    q2.c \
    util.c

HEADERS += \
    deque.h \
    util.h \
    testcase.h
