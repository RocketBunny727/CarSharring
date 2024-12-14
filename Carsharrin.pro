QT       += core gui
QT       += multimedia
QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    autotableinsertwindow.cpp \
    autotablewidget.cpp \
    main.cpp \
    mainwindow.cpp \
    optionswidget.cpp \
    partnertableinsertwindow.cpp \
    partnertablewidget.cpp \
    rentwindow.cpp \
    slide.cpp \
    stafftableinsertwindow.cpp \
    stafftablewidget.cpp \
    usertableinsertwindow.cpp \
    usertablewidget.cpp

HEADERS += \
    autotableinsertwindow.h \
    autotablewidget.h \
    mainwindow.h \
    optionswidget.h \
    partnertableinsertwindow.h \
    partnertablewidget.h \
    rentwindow.h \
    slide.h \
    stafftableinsertwindow.h \
    stafftablewidget.h \
    usertableinsertwindow.h \
    usertablewidget.h

FORMS += \
    autotableinsertwindow.ui \
    autotablewidget.ui \
    mainwindow.ui \
    optionswidget.ui \
    partnertableinsertwindow.ui \
    partnertablewidget.ui \
    rentwindow.ui \
    slide.ui \
    stafftableinsertwindow.ui \
    stafftablewidget.ui \
    usertableinsertwindow.ui \
    usertablewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resourses.qrc
