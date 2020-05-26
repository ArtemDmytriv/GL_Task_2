QT       += charts qml quick

greaterThan(QT_MAJOR_VERSION, 4):

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/UtilClass.cpp \
    src/cpuinfo.cpp \
    src/main.cpp \
    src/networkinfo.cpp \
    src/raminfo.cpp

INCLUDEPATH += \
    include

HEADERS += \
    include/UtilClass.h \
    include/cpuinfo.h \
    include/head.h \
    include/linuxutil.h \
    include/networkinfo.h \
    include/raminfo.h \
    include/winutils.h

FORMS +=

win32:{
    SOURCES += src/winutils.cpp
} else {
    SOURCES += src/linuxutils.cpp
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    qml/main.qml

RESOURCES += \
    resources.qrc
