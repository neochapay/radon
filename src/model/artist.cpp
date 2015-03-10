#include "artist.h"
#include "track.h"
#include "../dbadapter.h"

Artist::Artist(QObject *parent) : Item(parent)
{

}

QHash<int, Artist*> Artist::cache;

Artist* Artist::toId(int artistId)
{
    if(cache.contains(artistId))
    {
        return cache.value(artistId);
    }

    QSqlDatabase db = dbAdapter::instance().db;
    QSqlQuery query(db);
    query.prepare(QString("SELECT name FROM artist WHERE id=:id"));
    query.bindValue(":id",artistId);

    bool ok = query.exec();
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
    }
    if(query.next())
    {
        Artist* artist = new Artist();
        artist->setId(artistId);
        artist->setName(query.value(0).toString());

        cache.insert(artistId,artist);
        return artist;
    }
    cache.insert(artistId,0);
    return 0;
}

int Artist::idFromName(QString name)
{
    int id = 0;
    QSqlDatabase db = dbAdapter::instance().db;
    QSqlQuery query(db);
    QString str = QString("SELECT id FROM artist WHERE `name`='%1'").arg(name);

    bool ok = query.exec(str);
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
    }

    if(query.next())
    {
        id = query.value(0).toInt();
    }

    return id;
}

void Artist::insert()
{
    QSqlDatabase db = dbAdapter::instance().db;
    QSqlQuery query(db);
    QString str = QString("INSERT INTO artist (name) VALUES ('%1')").arg(name);

    bool ok = query.exec(str);
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
    }
}

bool Artist::setName(QString name)
{
    QSqlDatabase db = dbAdapter::instance().db;
    QSqlQuery query(db);
    QString str = QString("SELECT id FROM artist WHERE `name`='%1'").arg(name);

    bool ok = query.exec(str);
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
    }

    if(query.next())
    {
        qDebug() << "Name is not original";
        return false;
    }
    else
    {
        this->name = name;
        return true;
    }
}

void Artist::update()
{
    QSqlDatabase db = dbAdapter::instance().db;
    QSqlQuery query(db);
    query.prepare("UPDATE arists SET name=:name WHEER id=:id");
    query.bindValue(":name",name);
    query.bindValue(":id",id);

    bool ok = query.exec();
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
    }
    else
    {
        QDir artistDir = QDir();
        artistDir.mkpath(QString(QDir::homePath()+"/.radon/collection/"+this->name+"/"));
        QList<Track*> tracks = this->getTracks();
        for (int i = 0;i<tracks.count();i++)
        {
            tracks[i]->setArtistId(id);
        }
    }
}

QList<Track*> Artist::getTracks()
{
    QList<Track*> tracks;
    QSqlDatabase db = dbAdapter::instance().db;
    QSqlQuery query(db);
    query.prepare("SELECT id FROM songs WHERE artist_id = :id");
    query.bindValue(":id",id);

    bool ok = query.exec();
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
    }
    while (query.next())
    {
        int trackId = query.value(0).toInt();
        Track* track = Track::toId(trackId);
        tracks << track;
    }
    return tracks;
}
