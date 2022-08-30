QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets bluetooth

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/chargestatus.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/devicebatteryinfo.cpp

HEADERS += \
    src/airpodsspecs.h \
    src/chargestatus.h \
    src/mainwindow.h \
    src/devicebatteryinfo.h

FORMS += \
    ui/mainwindow.ui \
    ui/devicebatteryinfo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

