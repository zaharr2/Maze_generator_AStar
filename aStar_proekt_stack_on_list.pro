TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -LD:/GoogleDrive/CSFML/lib

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += D:/GoogleDrive/CSFML/include
DEPENDPATH += D:/GoogleDrive/CSFML/include

SOURCES += \
    main.cpp

DISTFILES += \
    map1.txt \
    map2.txt \
    map3.txt \
    map4.txt

HEADERS += \
    functions.h \
    global_variables.h
