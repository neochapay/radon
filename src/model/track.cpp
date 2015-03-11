#include "track.h"
#include "artist.h"
#include "../dbadapter.h"
#include "../audiofile.h"

Track::Track()
{
    artist_id = 0;
    number = 0;
    year = 0;
}

QHash<int, Track*> Track::cache;

Track* Track::toId(int trackId)
{
    if(cache.contains(trackId))
    {
        return cache.value(trackId);
    }

    QSqlDatabase db = dbAdapter::instance().db;
    QSqlQuery query(db);
    query.prepare("SELECT artist_id,title,album,comment,genere,track,year FROM songs WHERE id=:id");
    query.bindValue(":id",trackId);

    bool ok = query.exec();
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
    }

    if(query.next())
    {
        Track* track = new Track();
        track->id = trackId;
        track->artist_id = query.value(0).toInt();
        track->title = query.value(1).toString();
        track->album = query.value(2).toString();
        track->genere = query.value(3).toString();
        track->comment = query.value(4).toString();
        track->number = query.value(5).toInt();
        track->year = query.value(6).toInt();

        Artist* artist = new Artist();
        track->artist = artist->toId(track->artist_id);

        cache.insert(trackId,track);
        return track;
    }
    cache.insert(trackId,0);
    return 0;
}

void Track::insert()
{
    QSqlDatabase db = dbAdapter::instance().db;
    QSqlQuery query(db);
    query.prepare("INSERT INTO songs (`artist_id`, `title`, `album`, `comment`, `genere`, `track`, `year`) VALUES (:artist_id,:title,:album,:comment,:genere,:track,:year)");
    query.bindValue(":artist_id",artist_id);
    query.bindValue(":title",title);
    query.bindValue(":album",album);
    query.bindValue(":comment",comment);
    query.bindValue(":genere",genere);
    query.bindValue(":track",number);
    query.bindValue(":year",year);

    bool ok = query.exec();
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
    }
}

void Track::update()
{
    QSqlDatabase db = dbAdapter::instance().db;
    QSqlQuery query(db);
    query.prepare("UPADTE songs SET `artist_id`=:artist_id, `title`=:title, `album`=:album, `comment`=:comment, `genere`=:genere, `track`=:track, `year`=:year WHERE id=:id");
    query.bindValue(":artist_id",this->artist_id);
    query.bindValue(":title",this->title);
    query.bindValue(":album",this->album);
    query.bindValue(":comment",this->comment);
    query.bindValue(":genere",this->genere);
    query.bindValue(":track",this->number);
    query.bindValue(":year",this->year);
    query.bindValue(":id",this->id);

    bool ok = query.exec();
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
    }
    else
    {
        Artist* artist = new Artist();
        artist->toId(artist_id);
        QString fileName = QString(QDir::homePath()+"/.radon/collection/"+artist->getName()+"/"+title+".mp3");

        AudioFile audioFile(fileName);
        audioFile.artist = artist->getName();
        audioFile.title = title;
        audioFile.album = album;
        audioFile.comment = comment;
        audioFile.genre = genere;
        audioFile.track = number;
        audioFile.year = year;

        qDebug() << this->title;

        audioFile.sync();
    }
}

bool Track::setTitle(QString title)
{
    QString artistName = this->artist->getName();
    QString oldFileName = QString(QDir::homePath()+"/.radon/collection/"+artistName+"/"+this->title+".mp3");
    QString newFileName = QString(QDir::homePath()+"/.radon/collection/"+artistName+"/"+title+".mp3");

    QFile* oldFile = new QFile(oldFileName);
    QFile* newFile = new QFile(newFileName);

    if(newFile->exists())
    {
        qDebug() << "Track is exists";
        return false;
    }
    else
    {
        QSqlDatabase db = dbAdapter::instance().db;
        QSqlQuery query(db);

        query.prepare("UPDATE songs SET title=:title WHERE id=:id");
        query.bindValue(":id",this->id);
        query.bindValue(":title",title);

        bool ok = query.exec();
        if(ok)
        {
            oldFile->copy(oldFileName,newFileName);
            oldFile->remove();

            AudioFile audioFile(newFileName);
            audioFile.title = title;
            audioFile.sync();

            this->title = title;
            return true;
        }
        else
        {
            qDebug() << query.lastQuery() << query.lastError().text();
            return false;
        }
    }
}


bool Track::setArtistId(int artist_id)
{
    Artist* artist = new Artist();
    artist->toId(artist_id);

    QString oldFileName = QString(QDir::homePath()+"/.radon/collection/"+artist->getName()+"/"+this->title+".mp3");
    QString newFileName = QString(QDir::homePath()+"/.radon/collection/"+artist->getName()+"/"+this->title+".mp3");

    QFile* oldFile = new QFile(oldFileName);
    QFile* newFile = new QFile(newFileName);

    if(newFile->exists())
    {
        qDebug() << "Track is exists";
        return false;
    }
    else
    {
        oldFile->copy(oldFileName,newFileName);
        oldFile->remove();

        AudioFile audioFile(newFileName);
        audioFile.artist = artist->getName();
        audioFile.sync();

        this->artist_id = artist_id;
        return true;
    }
}
