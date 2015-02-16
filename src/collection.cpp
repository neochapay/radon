#include "collection.h"
#include "audiofile.h"
#include "threadfilecopy.h"

#include <QFile>
#include <QDir>
#include <QDebug>
#include <QThread>

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
    thread->quit();
}

void Collection::addFiles(QVariant files)
{
    ThreadFileCopy* tCopy = new ThreadFileCopy();
    tCopy->setFileList(files.toList());

    thread = new QThread;
    connect(thread, SIGNAL(started()), tCopy, SLOT(proccess()));
    connect(tCopy,SIGNAL(fileCopied(QString)),this,SLOT(setStatus(QString)));
    connect(this,SIGNAL(fileCopyTick()),this,SLOT(processTick()));

    tCopy->moveToThread(thread);
    copyAll = files.toList().length();
    copyCount = 0;
    thread->start();
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

void Collection::setStatus(QString status)
{
    emit fileCopyTick();
    emit setStatusText(QVariant("Add to collection: "+status));
}

void Collection::processTick()
{
    copyCount++;
    setProcess();
}

void Collection::setProcess()
{
    QVariant prc = copyCount/copyAll*100;
    emit setStatusProcess(prc);
}
