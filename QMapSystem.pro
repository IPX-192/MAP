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

RESOURCES += qml.qrc

OBJECTS_DIR   = ./tmp/Debug/$$TARGET        #指定obj中间文件生成目录
MOC_DIR       =  $$OBJECTS_DIR              #指定中间文件存放目录
RCC_DIR       =  $$OBJECTS_DIR              #指定中间文件存放目录
UI_DIR        =  $$OBJECTS_DIR              #指定中间文件存放目录

INCLUDEPATH +=  $$PWD/thirdparty/libLitesql/include

CONFIG(debug,debug|release){
#指定生成的应用程序放置的目录
    DESTDIR = ./bin/debug
}

CONFIG(release,debug|release){
    DESTDIR = ./bin/release
}

CONFIG(debug, debug|release){
    contains(QT_ARCH, i386) {
    } else {
        LIBS += -L$$PWD/thirdparty/libLitesql/lib/x64   -llitesqld
    }
} else {
    contains(QT_ARCH, i386) {
    } else {
        LIBS += -L$$PWD/thirdparty/libLitesql/lib/x64   -llitesql
    }
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
    CClientSystem.h \
    CDataParseThread.h \
    CUserCoordView.h \
    CWebSocketServer.h \
    MainFrame.h \
    database/CAbstractConfigInfo.h \
    database/CDatabaseManage.h \
    database/CDevInfoConfig.h \
    database/CDevInfoTable.h \
    database/CMapOriginConfig.h \
    database/CTagDataTable.h \
    database/CTagInfoTable.h \
    database/CUserInfoTable.h \
    database/CVersionInfoTable.h \
    database/mapsysdatabase.hpp \
    datamanager/CDevInfo.h \
    datamanager/CMapOriginInfo.h \
    datamanager/COnlineTagInfo.h \
    datamanager/CTagData.h \
    datamanager/CTagInfo.h \
    datamanager/CUserInfo.h \
    datamodel/CDevInfoModel.h \
    datamodel/COnlineTagModel.h \
    datamodel/CTagDataModel.h \
    datamodel/CTagInfoModel.h \
    datamodel/CUserInfoModel.h

SOURCES += \
        CClientSystem.cpp \
        CDataParseThread.cpp \
        CUserCoordView.cpp \
        CWebSocketServer.cpp \
        MainFrame.cpp \
        database/CAbstractConfigInfo.cpp \
        database/CDatabaseManage.cpp \
        database/CDevInfoConfig.cpp \
        database/CDevInfoTable.cpp \
        database/CMapOriginConfig.cpp \
        database/CTagDataTable.cpp \
        database/CTagInfoTable.cpp \
        database/CUserInfoTable.cpp \
        database/CVersionInfoTable.cpp \
        database/mapsysdatabase.cpp \
        datamanager/CDevInfo.cpp \
        datamanager/CMapOriginInfo.cpp \
        datamanager/COnlineTagInfo.cpp \
        datamanager/CTagData.cpp \
        datamanager/CTagInfo.cpp \
        datamanager/CUserInfo.cpp \
        datamodel/CDevInfoModel.cpp \
        datamodel/COnlineTagModel.cpp \
        datamodel/CTagDataModel.cpp \
        datamodel/CTagInfoModel.cpp \
        datamodel/CUserInfoModel.cpp \
        main.cpp
