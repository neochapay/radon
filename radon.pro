TEMPLATE = app

QT += qml quick widgets

LIBS += -ljack

SOURCES += main.cpp \
    src/qjack/client.cpp \
    src/qjack/audioport.cpp \
    src/qjack/midiport.cpp \
    src/qjack/port.cpp \
    src/qjack/audiobuffer.cpp \
    src/qjack/buffer.cpp \
    src/qjack/midibuffer.cpp

RESOURCES += qml.qrc

TRANSLATIONS = i18n/ru.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

evil_hack {
    SOURCES += main.qml\
    components/MainContent.qml \
    components/MasterPanel.qml \
    components/MasterPanel/AirButtons.qml \
    components/MasterPanel/CurrentShow.qml \
    components/MasterPanel/NowPlaying.qml \
    components/NavigationPanel.qml \
    components/NavigationPanel/NavigationItem.qml \
    components/WorkPanel.qml \
    components/WorkPanel/WorkItem.qml
}

ICON = images/logo.png

DISTFILES += \
    i18n/ru.ts \
    images/logo.png \
    images/logo.svg

HEADERS += \
    src/qjack/client.h \
    src/qjack/processor.h \
    src/qjack/processor.h \
    src/qjack/global.h \
    src/qjack/audioport.h \
    src/qjack/midiport.h \
    src/qjack/port.h \
    src/qjack/audiobuffer.h \
    src/qjack/buffer.h \
    src/qjack/ringbuffer.h \
    src/qjack/midibuffer.h

