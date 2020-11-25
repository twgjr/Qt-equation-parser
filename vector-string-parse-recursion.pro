QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        equationparser.cpp \
        expressionitem.cpp \
        main.cpp \
        regexlist.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    equationparser.h \
    expressionitem.h \
    regexlist.h

win32: LIBS += -L$$PWD/../libbuilds/z3/z3-z3-4.8.8-install/lib/ -llibz3

INCLUDEPATH += $$PWD/../libbuilds/z3/z3-z3-4.8.8-install/include
DEPENDPATH += $$PWD/../libbuilds/z3/z3-z3-4.8.8-install/include
