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

        QString artistName = track->artist->getName();
        track->fileName = QString(QDir::homePath()+"/.radon/collection/"+artistName+"/"+track->title+".mp3");
        AudioFile *trackFile = new AudioFile(track->fileName);
        track->length = trackFile->length;

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
    query.prepare("INSERT INTO songs (`artist_id`, `title`, `album`, `comment`, `genere`, `track`, `year`) VALUES (:artistid, :title, :album, :comment, :genere, :track, :year)");
    query.bindValue(":artistid",artist_id);
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
    query.prepare("UPDATE songs SET artist_id=:AID,title=:Title,track=:Track,album=:Album,comment=:Comment,genere=:Genere,year=:Year WHERE id=:rid");
    query.bindValue(":AID",this->artist_id);
    query.bindValue(":Title",this->title);
    query.bindValue(":Album",this->album);
    query.bindValue(":Comment",this->comment);
    query.bindValue(":Genere",this->genere);
    query.bindValue(":Track",this->number);
    query.bindValue(":Year",this->year);
    query.bindValue(":rid",this->id);

    bool ok = query.exec();
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
    }
    else
    {
        AudioFile audioFile(this->fileName);
        audioFile.artist = artist->getName();
        audioFile.title = this->title;
        audioFile.album = this->album;
        audioFile.comment = this->comment;
        audioFile.genre = this->genere;
        audioFile.track = this->number;
        audioFile.year = this->year;

        audioFile.sync();

        QString artistName = this->artist->getName();
        QString newFileName = QString(QDir::homePath()+"/.radon/collection/"+artistName+"/"+this->title+".mp3");
        if(this->fileName != newFileName)
        {
            QFile* oldFile = new QFile(this->fileName);
            oldFile->copy(this->fileName,newFileName);
            oldFile->remove();
            this->fileName = newFileName;
        }
    }
}

void Track::setArtistName(QString name)
{
    Artist* artist = new Artist();
    int a_id = artist->idFromName(name);
    if(a_id == 0)
    {
        artist->setName(name);
        artist->insert();
        a_id = artist->idFromName(name);
    }
    this->artist_id = a_id;
    this->artist = artist->toId(a_id);
}

void Track::setArtistId(int id)
{
    Artist* artist = new Artist();
    this->artist = artist->toId(id);
    this->artist_id = id;
}

void Track::remove()
{
    QSqlDatabase db = dbAdapter::instance().db;
    QSqlQuery query(db);
    query.prepare("DELETE FROM songs WHERE id=:id");
    query.bindValue(":id",this->id);

    bool ok = query.exec();

    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
    }
    else
    {
        QFile* file = new QFile(this->fileName);
        file->remove();

        if(this->artist->getTracks().length() == 0)
        {
            this->artist->remove();
        }
    }
}
