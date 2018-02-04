#-------------------------------------------------
#
# Project created by QtCreator 2018-01-29T11:18:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QCameraTool
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cameratool.cpp \
    displayer.cpp \
    imageprocessor.cpp

HEADERS  += mainwindow.h \
    cameratool.h \
    displayer.h \
    imageprocessor.h

FORMS    += mainwindow.ui



    INCLUDEPATH += C:\opencvmingw\install\include\


    LIBS +=C:\opencvmingw\install\x86\mingw\bin\libopencv_core310.dll
    LIBS +=C:\opencvmingw\install\x86\mingw\bin\libopencv_highgui310.dll
    LIBS +=C:\opencvmingw\install\x86\mingw\bin\libopencv_imgcodecs310.dll
    LIBS +=C:\opencvmingw\install\x86\mingw\bin\libopencv_videoio310.dll
    LIBS +=C:\opencvmingw\install\x86\mingw\bin\libopencv_imgproc310.dll
    LIBS +=C:\opencvmingw\install\x86\mingw\bin\libopencv_objdetect310.dll

    LIBS +=C:\opencvmingw\install\x86\mingw\lib\libopencv_core310.dll.a
    LIBS +=C:\opencvmingw\install\x86\mingw\lib\libopencv_highgui310.dll.a
    LIBS +=C:\opencvmingw\install\x86\mingw\lib\libopencv_imgcodecs310.dll.a
    LIBS +=C:\opencvmingw\install\x86\mingw\lib\libopencv_videoio310.dll.a
    LIBS +=C:\opencvmingw\install\x86\mingw\lib\libopencv_imgproc310.dll.a
    LIBS +=C:\opencvmingw\install\x86\mingw\lib\libopencv_objdetect310.dll.a


static { # everything below takes effect with CONFIG ''= static
 CONFIG+= static
 CONFIG += staticlib # this is needed if you create a static library, not a static executable
 DEFINES+= STATIC
 message("~~~ static build ~~~") # this is for information, that the static build is done
 mac: TARGET = $$join(TARGET,,,_static) #this adds an _static in the end, so you can seperate static build
#from non static build
 win32: TARGET = $$join(TARGET,,,s) #this adds an s in the end, so you can seperate static build from
#non static build
}

QMAKE_LFLAGS_RELEASE += -static -static-libgcc
