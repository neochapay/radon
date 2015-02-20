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

    query = QSqlQuery(db);

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
        addArtist(audioFile->artist);
        addSong(getArtistID(audioFile->artist),audioFile->title,audioFile->album,audioFile->comment,audioFile->genre,audioFile->track,audioFile->year);
    }
}

void dbAdapter::addArtist(QString name)
{
    QString str = QString("INSERT INTO artist (name) VALUES ('%1')").arg(name);
    query.exec(str);
}

int dbAdapter::getArtistID(QString name)
{
    QString str = QString("SELECT id FROM artist WHERE `name` = '%1'").arg(name);
    query.exec(str);
    while(query.next())
    {
        return query.value("id").toInt();
    }
    return 0;
}

QList<int> dbAdapter::getArtistSong(int artist_id)
{
    QList<int> songList;
    QString str = QString("SELECT id FROM song WHERE `artist_id` = '%1'").arg(artist_id);
    query.exec(str);
    while(query.next())
    {
        songList.append(query.value("id").toInt());
    }
    return songList;
}

void dbAdapter::addSong(int artist_id, QString title, QString album, QString comment, QString genere, int track, int year)
{
    query.prepare("INSERT INTO songs (`artist_id`, `title`, `album`, `comment`, `genere`, `track`, `year`) VALUES (:artist_id,:title,:album,:comment,:genere,:track,:year)");
    query.bindValue(":artist_id",artist_id);
    query.bindValue(":title",title);
    query.bindValue(":album",album);
    query.bindValue(":comment",comment);
    query.bindValue(":genere",genere);
    query.bindValue(":track",track);
    query.bindValue(":year",year);
    query.exec();
}
