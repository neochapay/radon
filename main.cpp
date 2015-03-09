#include <QApplication>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QQmlContext>
#include <QFile>

#include "src/qjack/client.h"
#include "src/jackprocessor.h"
#include "src/applicationsettings.h"
#include "src/collection.h"

#include "src/model/artistsqlmodel.h"
#include "src/model/tracksqlmodel.h"
#include "src/model/artist.h"
#include "src/model/track.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("RadON");
    app.setApplicationVersion("0.1.0a");
    app.setOrganizationName("Open STUDiO");
    app.setOrganizationDomain("ostudio.org");

    QSettings *settings = new QSettings(QDir::homePath()+"/.radon/radon.conf",QSettings::NativeFormat);
    Collection *audioCollection = new Collection();

    //Load Jack client
    QJack::Client client;
    client.connectToServer("radon");
    JackProcessor *streamProcessor = new JackProcessor(client, QString("stream"), true);

    streamProcessor->setupMp3Decoder();
    client.activate();

    //LoadModels
    ArtistSqlModel *artistSqlModel = new ArtistSqlModel();
    TrackSqlModel *trackSqlModel = new TrackSqlModel();
    Artist* artistModel = new Artist();
    Track* trackModel = new Track();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    engine.rootContext()->setContextProperty("Settings", settings);
    engine.rootContext()->setContextProperty("Collection", audioCollection);
    engine.rootContext()->setContextProperty("streamProcessor", streamProcessor);

    engine.rootContext()->setContextProperty("artistSqlModel", artistSqlModel);
    engine.rootContext()->setContextProperty("trackSqlModel", trackSqlModel);

    engine.rootContext()->setContextProperty("artistModel", artistModel);
    engine.rootContext()->setContextProperty("trackModel", trackModel);

    QObject *object = engine.rootObjects().first();
    QObject *libraryView = object->findChild<QObject*>("libraryPageArea");
    QObject *statusBar = object->findChild<QObject*>("statusBar");

    QObject::connect(libraryView,SIGNAL(addFiles(QVariant)),audioCollection,SLOT(addFiles(QVariant)));
    QObject::connect(audioCollection,SIGNAL(setStatusText(QVariant)),statusBar,SLOT(setStatus(QVariant)));
    QObject::connect(audioCollection,SIGNAL(setStatusProcess(QVariant)),statusBar,SLOT(setProcess(QVariant)));

    QObject::connect(audioCollection,SIGNAL(baseCreate()),artistSqlModel,SLOT(refresh()));
    QObject::connect(audioCollection,SIGNAL(baseCreate()),trackSqlModel,SLOT(refresh()));

    return app.exec();
}
