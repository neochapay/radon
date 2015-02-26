#include "track.h"
#include "artist.h"
#include "../dbadapter.h"

Track::Track()
{
    artist_id = 0;
    track = 0;
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
        track->setId(trackId);
        track->setArtistId(query.value(0).toInt());
        track->setTitle(query.value(1).toString());
        track->setAlbum(query.value(2).toString());
        track->setGenere(query.value(3).toString());
        track->setComment(query.value(4).toString());
        track->setTrack(query.value(5).toInt());
        track->setYear(query.value(6).toInt());

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
    query.bindValue(":track",track);
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
    query.prepare("UPADTE songs SET `artist_id`=':artist_id', `title`=':title', `album`=':album', `comment`=':comment', `genere`=':genere', `track`=':track', `year`=':year' WHERE id=:id");
    query.bindValue(":artist_id",artist_id);
    query.bindValue(":title",title);
    query.bindValue(":album",album);
    query.bindValue(":comment",comment);
    query.bindValue(":genere",genere);
    query.bindValue(":track",track);
    query.bindValue(":year",year);
    query.bindValue(":id",id);

    bool ok = query.exec();
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
    }
}
