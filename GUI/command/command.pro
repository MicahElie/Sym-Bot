QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    Comm/Controlmessage.cpp \
    Commandwindow.cpp \
    Comm/Accumulator.cpp \
    Comm/DataFrame.cpp \
    test/TestAccumulator.cpp \
    test/TestApp.cpp \
    test/TestDataFrame.cpp \
    test/Testcontrolmessage.cpp

HEADERS += \
    Comm/Controlmessage.h \
    Commandwindow.h \
    Comm/Accumulator.h \
    Comm/DataFrame.h \
    test/TestAccumulator.h \
    test/TestApp.h \
    test/TestDataFrame.h \
    test/Testcontrolmessage.h


FORMS += \
    Commandwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    testUI.txt
