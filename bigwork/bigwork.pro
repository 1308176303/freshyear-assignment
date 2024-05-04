QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bullet.cpp \
    enemy.cpp \
    gamecontrol.cpp \
    gamedefine.cpp \
    gameobjectpool.cpp \
    main.cpp \
    plane.cpp \
    player.cpp \
    widget.cpp

HEADERS += \
    bullet.h \
    enemy.h \
    gamecontrol.h \
    gamedefine.h \
    gameobjectpool.h \
    plane.h \
    player.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc
