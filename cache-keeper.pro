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
    src/FifoCommunicator.cpp \
    src/Exceptions.cpp \
    src/DummyAlgorithm.cpp \
    src/DependencyListBase.cpp \
    src/CacheableBase.cpp \
    src/Parameter.cpp \
    src/BinaryBlob.cpp

DISTFILES += \
    Makefile

HEADERS += \
    inc/IBinarySerializable.h \
    inc/TestSerializable.h \
    inc/SerializableRealVector.h \
    inc/Request.h \
    inc/Response.h \
    inc/Utils.h \
    inc/FifoCommunicator.h \
    inc/Exceptions.h \
    inc/IAlgorithm.h \
    inc/DummyAlgorithm.h \
    inc/IIdentifiable.h \
    inc/DependencyListBase.h \
    inc/IComparable.h \
    inc/Parameter.h \
    inc/CacheableBase.h \
    inc/BinaryBlob.h

INCLUDEPATH += inc/
