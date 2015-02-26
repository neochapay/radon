#include "dbadapter.h"
#include "audiofile.h"

#include "model/artist.h"
#include "model/track.h"

#include <QtSql>
#include <QSqlQueryModel>
#include <QDir>
#include <QDebug>

static dbAdapter *dbAdapterInstance = 0;

dbAdapter::dbAdapter(QObject *parent) : QObject(parent)
{
    QMutexLocker locker(&lock);
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


dbAdapter& dbAdapter::instance(){
    static QMutex mutex;
    QMutexLocker locker(&mutex);
    if(!dbAdapterInstance) dbAdapterInstance = new dbAdapter();
    return *dbAdapterInstance;
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
        int artist_id = addArtist(audioFile->artist);
        addSong(artist_id,audioFile->title,audioFile->album,audioFile->comment,audioFile->genre,audioFile->track,audioFile->year);
    }
    emit dbRescanEnd();
}

int dbAdapter::addArtist(QString name)
{
    Artist* artist = new Artist();
    int a_id = artist->idFromName(name);
    if(a_id == 0)
    {
        artist->setName(name);
        artist->insert();
        a_id = artist->idFromName(name);
    }
    return a_id;
}

void dbAdapter::addSong(int artist_id, QString title, QString album, QString comment, QString genere, int track, int year)
{
    Track *nTrack = new Track();
    nTrack->setArtistId(artist_id);
    nTrack->setTitle(title);
    nTrack->setAlbum(album);
    nTrack->setComment(comment);
    nTrack->setGenere(genere);
    nTrack->setTrack(track);
    nTrack->setYear(year);
    nTrack->insert();
}
