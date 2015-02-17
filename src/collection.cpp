#include "collection.h"
#include "audiofile.h"
#include "threadfilecopy.h"

#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QDebug>
#include <QThread>
#include <QtSql>

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


    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::homePath()+"/.radon/db.sql");
    if(!db.open())
    {
          qDebug() << db.lastError().text();
    }

    if(QFile(QDir::homePath()+"/.radon/db.sql").size() == 0)
    {
        initDB();
    }

    connect(this,SIGNAL(readyToCopy(QString)),this,SLOT(addFile(QString)));
    connect(this,SIGNAL(fileCopyTick()),this,SLOT(processTick()));
}

Collection::~Collection()
{
    thread->quit();
}

void Collection::initDB()
{
    qDebug() << "DB INIT";
    db.exec("CREATE TABLE `artist` (`id` INTEGER PRIMARY KEY AUTOINCREMENT,`name` TEXT )");
    db.exec("CREATE TABLE `songs` (`id`	INTEGER PRIMARY KEY AUTOINCREMENT,`artist_id` INTEGER NOT NULL,`title` TEXT NOT NULL,`album` TEXT,`comment` TEXT,`genere` TEXT,`track` INTEGER,`year` INTEGER");
    db.exec("CREATE TABLE `playlist` (`id`	INTEGER PRIMARY KEY AUTOINCREMENT,`song_id`	INTEGER NOT NULL,`time`	INTEGER NOT NULL)");
    rescan();
}

void Collection::addFiles(QVariant files)
{
    ThreadFileCopy* tCopy = new ThreadFileCopy();
    tCopy->setFileList(files.toList());

    thread = new QThread;

    connect(thread, SIGNAL(started()), tCopy, SLOT(proccess()));
    connect(tCopy,SIGNAL(fileCopied(QString)),this,SLOT(setStatus(QString)));

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
    QDirIterator it(collectionDirString, QStringList() << "*.mp3", QDir::Files, QDirIterator::Subdirectories);

    while (it.hasNext()) {
        qDebug() << it.next();
    }
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
