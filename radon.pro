TEMPLATE = app

QT += qml quick widgets multimedia network sql

LIBS += -ljack -ltag -lfftw3

SOURCES += main.cpp \
    src/qjack/client.cpp \
    src/qjack/audioport.cpp \
    src/qjack/midiport.cpp \
    src/qjack/port.cpp \
    src/qjack/audiobuffer.cpp \
    src/qjack/buffer.cpp \
    src/qjack/midibuffer.cpp \
    src/jackprocessor.cpp \
    src/applicationsettings.cpp \
    src/collection.cpp \
    src/audiofile.cpp \
    src/networkconnection.cpp \
    src/dsp/qfftw.cpp \
    src/dsp/qunits.cpp \
    src/threadfilecopy.cpp \
    src/dbadapter.cpp \
    src/model/artist.cpp \
    src/model/track.cpp \
    src/model/artistsqlmodel.cpp \
    src/model/tracksqlmodel.cpp \
    src/model/playlist.cpp

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
    components/VolumeSlider \
    pages/CalendarPage.qml \
    pages/Dialogs/EditTrackDialog.qml \
    pages/InformationPage.qml \
    pages/Library/LibraryArtistItem.qml \
    pages/Library/LibraryTrackItem.qml \
    pages/LibraryPage.qml \
    pages/PlayList/PlayListItem.qml \
    pages/PlayList/PlayListItemIcon.qml \
    pages/PlaylistPage.qml \
    pages/SettingsPage.qml
}

ICON = images/logo.png

DISTFILES += \
    i18n/ru.ts \
    images/logo.png \
    images/logo.svg \
    js/FontAwesome.js \
    fonts/fontawesome-webfont.ttf

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
    src/qjack/midibuffer.h \
    src/jackprocessor.h \
    src/applicationsettings.h \
    src/collection.h \
    src/audiofile.h \
    src/networkconnection.h \
    src/dsp/qfftw.h \
    src/dsp/qunits.h \
    src/threadfilecopy.h \
    src/dbadapter.h \
    src/model/item.h \
    src/model/artist.h \
    src/model/track.h \
    src/model/artistsqlmodel.h \
    src/model/tracksqlmodel.h \
    src/model/playlist.h

