#-------------------------------------------------
#
# Project created by QtCreator 2013-11-22T00:29:02
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled1
TEMPLATE = app


SOURCES += main.cpp \
    widget.cpp \
    GeoEngine.cpp \
    Libs/model.cpp

HEADERS  += \
    widget.h \
    GeoEngine.h \
    Libs/model.h

FORMS    +=

OTHER_FILES += \
    shaders/PointLight.vert \
    shaders/PointLight.frag
