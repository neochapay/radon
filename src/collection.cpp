#include "collection.h"
#include "audiofile.h"

#include <QFile>
#include <QDir>
#include <QDebug>

Collection::Collection(QObject *parent) : QObject(parent)
{
    collectionDir = QDir(QString(QDir::homePath()+"/.radon/collection/"));
    if(!collectionDir.exists())
    {
        qDebug() << "Collection dir not exists";
        if(!collectionDir.mkpath(QString(QDir::homePath()+"/.radon/collection/")))
        {
            qDebug() << "Can`t create collection dir";
            emit erorrAcces();
        }
    }
}

Collection::~Collection()
{

}

void Collection::addFile(QFile &file)
{
    AudioFile *audioFile = new AudioFile(QString(file.fileName()));
    qDebug() << audioFile->getTags();
}

void Collection::removeFile(QFile &file)
{
    file.remove();
}

void Collection::rescan()
{

}
