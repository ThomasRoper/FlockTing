#-------------------------------------------------
#
# Project created by QtCreator 2018-03-06T12:40:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FlockTing
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#The cpp files locations
SOURCES += \
        src/main.cpp \
    src/NGLScene.cpp \
    src/NGLSceneMouseControls.cpp \
    src/Flock.cpp


#The h files locations
HEADERS += \
    include/NGLScene.h \
    include/Boid.h \
    include/Flock.h \
    include/WindowParams.h

INCLUDEPATH += $$PWD/include
#The other files int Forms
FORMS += \
        ui/mainwindow.ui
OTHER_FILES+= shaders/*.glsl \
# were are going to default to a console app
CONFIG += console



NGLPATH=$$(NGLDIR)
isEmpty(NGLPATH){ # note brace must be here
        message("including $HOME/NGL")
        include($(HOME)/NGL/UseNGL.pri)
}
else{ # note brace must be here
        message("Using custom NGL location")
        include($(NGLDIR)/UseNGL.pri)
}


