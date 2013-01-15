TEMPLATE = app
CONFIG += console
CONFIG -= qt

MOC_DIR = moc
OBJECTS_DIR = obj
DESTDIR += bin
DEPENDPATH += dll
CONFIG += debug_and_release

win32 {
}

unix {
}

SOURCES += main.cpp \
    totdataread.cpp

HEADERS += \
    common.h \
    totdataread.h

