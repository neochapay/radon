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
    QObject::connect(this,SIGNAL(readyToCopy(QString)),this,SLOT(addFile(QString)));
}

Collection::~Collection()
{

}

void Collection::addFiles(QVariant files)
{
    QList<QVariant> fileUrls = files.toList();
    for(int i=0; i<fileUrls.length(); i++)
    {
       emit readyToCopy(fileUrls[i].toString());
    }
}

void Collection::addFile(QString fileName)
{
    AudioFile audioFile(fileName);
    QFile file;
    if(audioFile.artist.length() == 0 || audioFile.title.length() == 0)
    {
        emit notAllTags();
        if(audioFile.artist.length() == 0)
        {
            audioFile.artist = QString("Unknow Artist");
        }

        if(audioFile.title.length() == 0)
        {
            audioFile.title = QString("Unknow Track");
        }
        audioFile.sync();
    }
    collectionDir.mkpath(collectionDirString+QString("/"+audioFile.artist.toUtf8()));
    file.copy(fileName,collectionDirString+"/"+audioFile.artist.toUtf8()+"/"+audioFile.title.toUtf8()+".mp3");
}

void Collection::removeFile(QFile &file)
{
    file.remove();
}

void Collection::rescan()
{

}
