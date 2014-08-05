TEMPLATE = app

TARGET = CQColorPaletteTest

DEPENDPATH += .

QT += widgets

#CONFIG += debug

# Input
SOURCES += \
CQColorPaletteTest.cpp \

HEADERS += \
CQColorPaletteTest.h \

DESTDIR     = .
OBJECTS_DIR = .

INCLUDEPATH += \
../include \
../../CQStyleWidget/include \
.

unix:LIBS += \
-L../lib -L../../CQStyleWidget/lib \
-lCQColorPalette -lCQStyleWidget
