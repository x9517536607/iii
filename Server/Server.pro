#-------------------------------------------------
#
# Project created by QtCreator 2015-06-08T15:49:13
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    envthread.cpp \
    sockethandler.cpp \
    tcpserver.cpp \
    servicesingleton.cpp \
    udpserver.cpp \
    scheduler.cpp \
    GoogleGCMSender.cpp

HEADERS  += mainwindow.h \
    envthread.h \
    sockethandler.h \
    tcpserver.h \
    servicesingleton.h \
    udpserver.h \
    dbModel.h \
    scheduler.h \
    constantString.h \
    GoogleGCMSender.h

FORMS    += mainwindow.ui

LIBS     += /usr/lib/live/liveMedia/libliveMedia.a \
            /usr/lib/live/BasicUsageEnvironment/libBasicUsageEnvironment.a \
            /usr/lib/live/UsageEnvironment/libUsageEnvironment.a \
            /usr/lib/live/groupsock/libgroupsock.a \

INCLUDEPATH += /usr/lib/live/liveMedia/include \
               /usr/lib/live/BasicUsageEnvironment/include \
               /usr/lib/live/UsageEnvironment/include \
               /usr/lib/live/groupsock/include \
