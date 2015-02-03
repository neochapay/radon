#include "networkconnection.h"

#include <QDir>

NetworkConnection::NetworkConnection(QObject *parent) : QObject(parent)
{
    settings    = new QSettings(QDir::homePath()+"/.radon/radon.conf",QSettings::NativeFormat);
    appKey      = QString(settings->value("appKey").toString().toUtf8());
    serverKey   = QString(settings->value("serverKey").toString().toUtf8());
    baseUrl     = QString(settings->value("baseUrl").toString().toUtf8());

    if(appKey.length() != 8 && serverKey.length() != 32)
    {
        emit needConfig();
    }
}

NetworkConnection::~NetworkConnection()
{

}

