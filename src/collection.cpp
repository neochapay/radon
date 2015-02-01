#include "collection.h"
#include "audiofile.h"

#include <QFile>
#include <QDir>
#include <QDebug>

Collection::Collection(QObject *parent) : QObject(parent)
{
    collectionDir = QDir(QString(QDir::homePath()+"/.radon/collection/"));
    collectionDirString = QString(QDir::homePath()+"/.radon/collection/");
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
    QList<QString> tags = audioFile->getTags();
    if(tags[0].length() == 0 || tags[1].length() == 0)
    {
        emit notAllTags();
        if(tags[0].length() == 0)
        {
            tags[0] = "Unknow Artist";
        }

        if(tags[1].length() == 0)
        {
            tags[1] = "Unknow Track";
        }
    }
    collectionDir.mkpath(collectionDirString+"/"+tags[0]);
    file.copy(file.fileName(),collectionDirString+"/"+tags[0]+"/"+tags[1]+".mp3");
}

void Collection::removeFile(QFile &file)
{
    file.remove();
}

bool Collection::editTags(QFile &file, QList<QString> &tags)
{
    //Добавить фильтры
    if(tags.length() != 3)
    {
        return false;
    }

    file.copy(file.fileName(),collectionDirString+"/"+tags[0]+"/"+tags[1]+".mp3");
    file.remove(file.fileName());
    file.setFileName(collectionDirString+"/"+tags[0]+"/"+tags[1]+".mp3");
    return true;
}

void Collection::rescan()
{

}
