QT       += core gui widgets network
TARGET    = StendControl
TEMPLATE  = app
CONFIG   += c++17

SOURCES += \
    main.cpp \
    mainwindow.cpp 

HEADERS += \
    mainwindow.h 

FORMS += \
    mainwindow.ui

RESOURCES += \
    resources.qrc

# Настройки для Windows
win32 {
    RC_ICONS = icons/app_icon.ico
    LIBS += -L"$$PWD/libs" -lserialport
}

# Настройки для Linux
unix {
    LIBS += -L/usr/local/lib -lserial
}