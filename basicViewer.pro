TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += NOMINMAX

include($$(ADEV_DIR)/cots/prifiles/glew.pri)
include($$(ADEV_DIR)/cots/prifiles/glfw.pri)
include($$(ADEV_DIR)/cots/prifiles/glm.pri)

win32 {
    LIBS += -lsetupapi -lAdvapi32 -lShell32 -lwbemuuid
}

HEADERS += \
    acontroller.h \
    core/aiprocessor.h \
    helpers/ahelpers.h \
    helpers/acmdlineparser.h \
    renderer/arenderer.h \
    window/awindow.h \
    renderer/mesh.h \
    renderer/shader.h \
    renderer/stb_image.h \
    renderer/texture.h

SOURCES += \
    acontroller.cpp \
    core/aiprocessor.cpp \
    helpers/ahelpers.cpp \
    helpers/acmdlineparser.cpp \
    renderer/arenderer.cpp \
    window/awindow.cpp \
    main.cpp \
    renderer/mesh.cpp \
    renderer/shader.cpp \
    renderer/texture.cpp

#add to path bin
#$(ADEV_DIR)/cots/glfw/lib-vc2017;$(ADEV_DIR)/cots/glew/bin/Release/x64;$(ADEV_DIR)/cots/zlib/win32/msvc2017_64/bin

DISTFILES += \
    renderer/camshader.frag \
    renderer/camshader.vert
