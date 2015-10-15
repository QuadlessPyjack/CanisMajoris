TEMPLATE = app

QT += qml quick

SOURCES += \
    src/Procyon/main.cpp \
    src/Logger/DebugLog.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

INCLUDEPATH += include \
               "../../auxiliaries/boost-1.57.0/include"
LIBS += ../../auxiliaries/boost-1.57.0/lib/x64/libboost_date_time-vc120-mt-gd-1_57.lib

VPATH += \
    Logger

HEADERS += \
    Logger/DebugLog.h \
    Logger/ProcyonConstants.h
