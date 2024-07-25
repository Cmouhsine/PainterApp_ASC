QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    copypaste.cpp \
    dragbutton.cpp \
    filehandler.cpp \
    main.cpp \
    mainwindow.cpp \
    paintcanvas.cpp \
    redoundo.cpp

HEADERS += \
    copypaste.h \
    dragbutton.h \
    filehandler.h \
    mainwindow.h \
    paintcanvas.h \
    redoundo.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    images/about.png \
    images/aboutIcon.png \
    images/aboutQtIcon.png \
    images/circle.png \
    images/close.png \
    images/copyIcon.png \
    images/cutIcon.png \
    images/eraser.png \
    images/open.png \
    images/pasteIcon.png \
    images/pen.png \
    images/quitIcon.png \
    images/rectangle.png \
    images/redoIcon.png \
    images/save.png \
    images/star.png \
    images/undoIcon.png
