TARGET = qvat
OBJECTS_DIR = .obj
MOC_DIR = .moc
QT += xml \

DEFINES += QT_OPENGL_SUPPORT
QT += opengl

RESOURCES = qvat.qrc

HEADERS = QtEx/private/system.h \
          QtEx/private/scene.h \
          QtEx/private/itemloader.h \
          QtEx/private/itemanimation.h \
          QtEx/qmainscene.h \
          QtEx/item.h \
          QtEx/imageitem.h \
          QtEx/itembutton.h \
          QtEx/itemtext.h \
          mainwindow.h \
          viewcar.h \
 QtEx/ButtonItem.h
SOURCES = QtEx/private/system.cpp \
          QtEx/private/scene.cpp \
          QtEx/private/itemloader.cpp \
          QtEx/private/itemanimation.cpp \
          QtEx/qmainscene.cpp \
          QtEx/item.cpp \
          QtEx/imageitem.cpp \
          QtEx/itembutton.cpp \
          QtEx/itemtext.cpp \
          main.cpp \
          mainwindow.cpp \
          viewcar.cpp \
 QtEx/ButtonItem.cpp
win32 : RC_FILE = qvat.rc
TEMPLATE = app


CONFIG += debug
SOURCES -= QtEx/private/player.cpp

HEADERS -= QtEx/private/player.h

