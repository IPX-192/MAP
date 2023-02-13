QT += quick core gui network websockets sql
CONFIG += c++11
CONFIG += resources_big

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        CWebSocketServer.cpp \
        MainFrame.cpp \
        main.cpp

RESOURCES += qml.qrc

OBJECTS_DIR   = ./tmp/Debug/$$TARGET        #指定obj中间文件生成目录
MOC_DIR       =  $$OBJECTS_DIR              #指定中间文件存放目录
RCC_DIR       =  $$OBJECTS_DIR              #指定中间文件存放目录
UI_DIR        =  $$OBJECTS_DIR              #指定中间文件存放目录

CONFIG(debug,debug|release){
#指定生成的应用程序放置的目录
    DESTDIR = ./bin/debug
}

CONFIG(release,debug|release){
    DESTDIR = ./bin/release
}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    CWebSocketServer.h \
    MainFrame.h
