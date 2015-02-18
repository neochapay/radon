#include "dbadapter.h"
#include "audiofile.h"

#include <QtSql>
#include <QDir>
#include <QDebug>

dbAdapter::dbAdapter(QObject *parent) : QObject(parent)
{
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
}

dbAdapter::~dbAdapter()
{
    db.close();
}

void dbAdapter::initDB()
{
    db.exec("CREATE TABLE `artist` (`id` INTEGER PRIMARY KEY AUTOINCREMENT,`name` TEXT )");
    db.exec("CREATE TABLE `songs` (`id` INTEGER PRIMARY KEY AUTOINCREMENT,`artist_id` INTEGER NOT NULL,`title` TEXT NOT NULL,`album` TEXT,`comment` TEXT,`genere` TEXT,`track` INTEGER,`year` INTEGER)");
    db.exec("CREATE TABLE `playlist` (`id`	INTEGER PRIMARY KEY AUTOINCREMENT,`song_id`	INTEGER NOT NULL,`time`	INTEGER NOT NULL)");
    db.exec("CREATE UNIQUE INDEX artist_idx ON artist(name)");
    db.exec("CREATE UNIQUE INDEX song_idx ON songs(artist_id,title,album,track,year)");
    emit baseCreate();
}


void dbAdapter::rescanCollection()
{
    QString collectionDirString = QString(QDir::homePath()+"/.radon/collection/");
    QDirIterator it(collectionDirString, QStringList() << "*.mp3", QDir::Files, QDirIterator::Subdirectories);

    while (it.hasNext()) {
        AudioFile *audioFile = new AudioFile(it.next());
        qDebug() << audioFile->artist << " - " << audioFile->title;
        QString str = QString("INSERT INTO artist (name) VALUES (%1)").arg(audioFile->artist);
        db.exec(str.toUtf8());
    }
}
