TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

macx: LIBS += -L/usr/local/lib -lboost_filesystem -lboost_system -lboost_thread -lrt -pthread
linux: LIBS += -L/usr/local/lib -lboost_filesystem -lboost_system -lboost_thread -lrt -pthread

SOURCES += \
    src/server.cpp \
    src/client.cpp \
    src/TestSerializable.cpp \
    src/IBinarySerializable.cpp \
    src/testsuite.cpp \
    src/SerializableRealVector.cpp \
    src/Request.cpp \
    src/Response.cpp \
    src/Utils.cpp \
    src/FifoCommunicator.cpp

DISTFILES += \
    Makefile

HEADERS += \
    inc/IBinarySerializable.h \
    inc/TestSerializable.h \
    inc/SerializableRealVector.h \
    inc/Request.h \
    inc/Response.h \
    inc/Utils.h \
    inc/FifoCommunicator.h

INCLUDEPATH += inc/
