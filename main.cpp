#include <QApplication>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QQmlContext>

#include "src/qjack/client.h"
#include "src/jackprocessor.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSettings *Settings = new QSettings("radion.conf",QSettings::NativeFormat);

    QJack::Client client;
    client.connectToServer("radon");
    JackProcessor *Processor = new JackProcessor(client);
    Processor->setupMp3Decoder();
    Processor->loadFile(QString("/home/neochapay/Музыка/001_7Б - Молодые Ветра.mp3"));
    QObject::connect(Processor->audioDecoder, SIGNAL(bufferReady()), Processor, SLOT(transferSamples()));


    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    engine.rootContext()->setContextProperty("Settings", Settings);

    return app.exec();
}
