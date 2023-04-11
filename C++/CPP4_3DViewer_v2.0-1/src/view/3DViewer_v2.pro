QT       += core gui opengl openglwidgets widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../controller/controller.cc \
    ../model/dao/data_model.cc \
    ../model/facade.cc \
    ../model/kernel/optimal_scale_calculator.cc \
    ../model/kernel/parser.cc \
    ../model/kernel/strategy_transform/move.cc \
    ../model/kernel/strategy_transform/rotate.cc \
    ../model/kernel/strategy_transform/scale.cc \
    ../model/kernel/strategy_transform/transform_strategy.cc \
    QtGifImage-master/src/3rdParty/giflib/dgif_lib.c \
    QtGifImage-master/src/3rdParty/giflib/egif_lib.c \
    QtGifImage-master/src/3rdParty/giflib/gif_err.c \
    QtGifImage-master/src/3rdParty/giflib/gif_font.c \
    QtGifImage-master/src/3rdParty/giflib/gif_hash.c \
    QtGifImage-master/src/3rdParty/giflib/gifalloc.c \
    QtGifImage-master/src/3rdParty/giflib/quantize.c \
    QtGifImage-master/src/gifimage/qgifimage.cpp \
    gl_widget/glviewer.cpp \
    main.cpp \
    mainwindow.cpp \
    media_creator/media.cpp \
    settings/save_settings.cpp

HEADERS += \
    ../controller/controller.h \
    ../model/dao/data_model.h \
    ../model/facade.h \
    ../model/kernel/optimal_scale_calculator.h \
    ../model/kernel/parser.h \
    ../model/kernel/strategy_transform/move.h \
    ../model/kernel/strategy_transform/rotate.h \
    ../model/kernel/strategy_transform/scale.h \
    ../model/kernel/strategy_transform/transform_strategy.h \
    ../model/observer/observable.h \
    ../model/observer/observer.h \
    QtGifImage-master/src/3rdParty/giflib/gif_hash.h \
    QtGifImage-master/src/3rdParty/giflib/gif_lib.h \
    QtGifImage-master/src/3rdParty/giflib/gif_lib_private.h \
    QtGifImage-master/src/gifimage/qgifglobal.h \
    QtGifImage-master/src/gifimage/qgifimage.h \
    QtGifImage-master/src/gifimage/qgifimage_p.h \
    gl_widget/glviewer.h \
    mainwindow.h \
    media_creator/media.h \
    settings/save_settings.h

FORMS += \
    gl_widget/glviewer.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
