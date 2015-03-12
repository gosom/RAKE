TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    rake.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    rake.h \
    utils.h

QMAKE_CXXFLAGS += -std=c++11

OTHER_FILES += \
    stopwords.txt

LIBS += -lboost_regex
