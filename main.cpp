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

    QSettings *settings = new QSettings(QDir::homePath()+"/.radon/radon.conf",QSettings::NativeFormat);
    Collection *audioCollection = new Collection();

    QJack::Client client;
    client.connectToServer("radon");
    JackProcessor *streamProcessor = new JackProcessor(client, QString("stream"), true);

    streamProcessor->setupMp3Decoder();
    client.activate();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    engine.rootContext()->setContextProperty("Settings", settings);
    engine.rootContext()->setContextProperty("Collection", audioCollection);
    engine.rootContext()->setContextProperty("streamProcessor", streamProcessor);

    QObject *object = engine.rootObjects().first();
    QObject *libraryView = object->findChild<QObject*>("libraryPageArea");

    QObject::connect(libraryView,SIGNAL(addFiles(QVariant)),audioCollection,SLOT(addFiles(QVariant)));

    return app.exec();
}
