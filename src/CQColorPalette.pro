TEMPLATE = lib

TARGET = CQColorPalette

DEPENDPATH += .

QT += widgets

CONFIG += staticlib

# Input
HEADERS += \
../include/CColorPalette.h \
../include/CQColorPalette.h \
../include/CQColorPaletteDialog.h \
../include/CQColorPaletteSet.h \
../include/CQPalettePreview.h \

SOURCES += \
CColorPalette.cpp \
CQColorPalette.cpp \
CQColorPaletteDialog.cpp \
CQColorPaletteSet.cpp \
CQPalettePreview.cpp \

OBJECTS_DIR = ../obj

DESTDIR = ../lib

INCLUDEPATH += \
. \
../include \
../../CQStyleWidget/include \
