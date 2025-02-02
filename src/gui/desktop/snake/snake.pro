QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../../brick_game/snake/controller.cc \
    ../../../brick_game/snake/model.cc \
    ../../../brick_game/tetris/tetris.c \
    main.cc \
    snakeqt.cc \
    tetrisqt.cc

HEADERS += \
    ../../../brick_game/snake/controller.h \
    ../../../brick_game/snake/model.h \
    ../../../brick_game/tetris/tetris.h \
    snakeqt.h \
    tetrisqt.h

FORMS += \
    snakeqt.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES += \
    ../../../brick_game/snake/max_score \
    ../../../brick_game/tetris/max_score \
    images/android.png \
    images/apple.png \
    images/apple2.png \
    images/body.png \
    images/goL.png \
    images/goW.png \
    images/timeout.png
