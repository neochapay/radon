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

