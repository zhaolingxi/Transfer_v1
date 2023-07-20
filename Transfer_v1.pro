QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about_me.cpp \
    database.cpp \
    database_add.cpp \
    database_in_out.cpp \
    database_manager.cpp \
    database_serach.cpp \
    editorpanel.cpp \
    eventserver.cpp \
    function_select.cpp \
    main.cpp \
    login.cpp \
    settingdata.cpp \
    settings.cpp \
    socketserver.cpp

HEADERS += \
    about_me.h \
    database.h \
    database_add.h \
    database_in_out.h \
    database_manager.h \
    database_serach.h \
    editorpanel.h \
    eventserver.h \
    function_select.h \
    include/read_files.h \
    include/sqlite3.h \
    login.h \
    settingdata.h \
    settings.h \
    socketserver.h

FORMS += \
    about_me.ui \
    database.ui \
    database_add.ui \
    database_in_out.ui \
    database_serach.ui \
    editorpanel.ui \
    function_select.ui \
    login.ui \
    settings.ui

TRANSLATIONS += \
    Transfer_v1_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res_static.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lfile_action
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lfile_action
else:unix: LIBS += -L$$PWD/lib/ -lread_file

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

UI_DIR   =./UI
RC_ICONS = title.ico
