#include <QSettings>
#include <QDir>
#include "applicationsettings.h"

ApplicationSettings::ApplicationSettings(QObject *parent) : QObject(parent)
{
    settings = new QSettings(QDir::homePath()+"/.radon/radon.conf",QSettings::NativeFormat);
}

ApplicationSettings::~ApplicationSettings()
{

}

void ApplicationSettings::setValue(const QString &key, const QVariant &value)
{
    settings->setValue(key, value);
}

QVariant ApplicationSettings::value(const QString &key, const QVariant &defaultValue)
{
    return settings->value(key, defaultValue);
}

void ApplicationSettings::sync()
{
    settings->sync();
}
