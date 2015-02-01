#include <QApplication>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QQmlContext>

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
    JackProcessor *Processor = new JackProcessor(client);
    Processor->setupMp3Decoder();
    QObject::connect(Processor->audioDecoder, SIGNAL(bufferReady()), Processor, SLOT(transferSamples()));


    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    engine.rootContext()->setContextProperty("Settings", Settings);
    engine.rootContext()->setContextProperty("Collection", collection);

    return app.exec();
}
