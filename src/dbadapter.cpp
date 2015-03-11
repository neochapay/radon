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

/*Find files in collection directory*/
    while (it.hasNext()) {
        AudioFile *audioFile = new AudioFile(it.next());
        qDebug() << audioFile->artist << " - " << audioFile->title;
        int artist_id = addArtist(audioFile->artist);
        addSong(artist_id,audioFile->title,audioFile->album,audioFile->comment,audioFile->genre,audioFile->track,audioFile->year);
    }
/*Check missing files*/
    QSqlDatabase db = this->instance().db;
    QSqlQuery query(db);
    query.prepare("SELECT id FROM songs");
    query.exec();
    while (query.next()) {
        int song_id = query.value(0).toInt();
        Track* track = Track::toId(song_id);
        Artist* trackArtist = track->getArtist();
        QString artistName = trackArtist->getName();
        QFile* trackFile = new QFile(QDir::homePath()+"/.radon/collection/"+artistName+"/"+track->getTitle()+".mp3");
        if(!trackFile->exists())
        {
            track->remove();
        }
    }
/*Check 0-tracks artist*/
    query.prepare("SELECT id FROM artist");
    bool ok = query.exec();
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
    }
    else
    {
        while (query.next())
        {
            int artistId = query.value(0).toInt();
            Artist* artist = Artist::toId(artistId);
            if(artist->getTracks().length() == 0)
            {
                artist->remove();
            }
        }
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
    if(comment.length() < 1)
    {
        comment = QString("");
    }
    Track *nTrack = new Track();
    nTrack->setArtistId(artist_id);
    nTrack->setTitle(title);
    nTrack->setAlbum(album);
    nTrack->setComment(comment);
    nTrack->setGenere(genere);
    nTrack->setNum(track);
    nTrack->setYear(year);
    nTrack->insert();
}
