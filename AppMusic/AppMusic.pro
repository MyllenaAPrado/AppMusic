QT       += core gui \
            network \
            networkauth \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    player.cpp \
    playerrequest.cpp \
    searchrequest.cpp \
    socketconnection.cpp \
    track.cpp \
    user.cpp \
    userrequest.cpp

HEADERS += \
    mainwindow.h \
    player.h \
    playerrequest.h \
    searchrequest.h \
    socketconnection.h \
    track.h \
    user.h \
    userrequest.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    AppMusic_en_150.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    resources
