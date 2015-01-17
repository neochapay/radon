TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp

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
    components/WorkPanel.qml
}

DISTFILES += \
    i18n/ru.ts
