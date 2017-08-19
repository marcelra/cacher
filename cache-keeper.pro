TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

macx: LIBS += -L/usr/local/lib -lboost_filesystem -lboost_system -lboost_thread -lrt -pthread
linux: LIBS += -L/usr/local/lib -lboost_filesystem -lboost_system -lboost_thread -lrt -pthread

SOURCES += src/main.cpp \
    src/keeper.cpp \
    src/user.cpp \
    src/server.cpp \
    src/client.cpp

DISTFILES += \
    Makefile
