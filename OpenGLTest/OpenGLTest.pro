TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lglfw3\
        -Llglm \
        -lmingw32 \
        -lSDL2main \
        -lSDL2 \
        -lSDL2_image




HEADERS += glad\glad.h \
           KHR\khrplatform.h \
    library.h \
    shader.h

SOURCES += main.cpp \
           glad.c \
    library.cpp

DISTFILES += \
    ../build-OpenGLTest-msys2-Release/fragmentShaderCubeTex.fsl \
    ../build-OpenGLTest-msys2-Release/vertexShaderCubeTex.vsl \
    ../build-OpenGLTest-msys2-Release/shaderSingleColor.fsl \
    ../build-OpenGLTest-msys2-Release/shaderSingleColor.vsl
