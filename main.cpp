#include <QApplication>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QQmlContext>
#include <QFile>

#include "src/qjack/client.h"
#include "src/jackprocessor.h"
#include "src/applicationsettings.h"
#include "src/collection.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("RadON");
    app.setApplicationVersion("0.1.0a");
    app.setOrganizationName("Open STUDiO");
    app.setOrganizationDomain("ostudio.org");

    ApplicationSettings *Settings = new ApplicationSettings();
    Collection *collection = new Collection();

    QJack::Client client;
    client.connectToServer("radon");
    JackProcessor *StreamProcessor = new JackProcessor(client, QString("stream"), true);
    JackProcessor *DjProcessor = new JackProcessor(client, QString("dj"), true);

    StreamProcessor->setupMp3Decoder();
    DjProcessor->setupMp3Decoder();

    QObject::connect(StreamProcessor->audioDecoder, SIGNAL(bufferReady()), StreamProcessor, SLOT(transferSamples()));
    QObject::connect(DjProcessor->audioDecoder, SIGNAL(bufferReady()), DjProcessor, SLOT(transferSamples()));


    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    engine.rootContext()->setContextProperty("Settings", Settings);
    engine.rootContext()->setContextProperty("Collection", collection);

    return app.exec();
}
