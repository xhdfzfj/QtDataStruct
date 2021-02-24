QT += quick

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Class/drawelementclass.cpp \
        Common.cpp \
        Control/guicontrolclass.cpp \
        Control/memorydisplayclass.cpp \
        c_language/cjson/CommonFun.c \
        c_language/cjson/JsonAnalyse.c \
        c_language/cjsoninterface.cpp \
        main.cpp

RESOURCES += qml.qrc

TRANSLATIONS += \
    DataStruct_zh_CN.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Class/drawelementclass.h \
    Common.h \
    Control/guicontrolclass.h \
    Control/memorydisplayclass.h \
    XhdDefine.h \
    c_language/cjson/CommonFun.h \
    c_language/cjson/JsonAnalyse.h \
    c_language/cjson/JsonParamDef.h \
    c_language/cjsoninterface.h
