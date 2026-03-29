QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MD5.cpp \
    SHA256.cpp \
    main.cpp \
    mainwindow.cpp
    SHA256.cpp
    md5/MD5.cpp


HEADERS += \
    MD5.h \
    SHA256.h \
    mainwindow.h
    SHA256.h
    MD5.h
    md5/MD5.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
