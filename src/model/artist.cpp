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
    query.prepare("SELECT name FROM artist WHERE id=:id");
    query.bindValue(":id",artistId);

    bool ok = query.exec();
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
    }
    if(query.next())
    {
        Artist* artist = new Artist();
        artist->id = artistId;
        artist->name = query.value(0).toString();
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
    else
    {
        QDir artistDir = QDir();
        artistDir.mkpath(QString(QDir::homePath()+"/.radon/collection/"+name));
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
        this->oldname = this->name;
        this->name = name;
        return true;
    }
}

void Artist::update()
{
    QSqlDatabase db = dbAdapter::instance().db;
    QSqlQuery query(db);
    query.prepare("UPDATE artist SET name=:name WHERE id=:id");
    query.bindValue(":name",name);
    query.bindValue(":id",id);

    bool ok = query.exec();
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
    }
    else
    {
        QDir artistDir = QDir(QString(QDir::homePath()+"/.radon/collection/"+this->name+"/"));
        if(!artistDir.exists())
        {
            artistDir.mkpath(QString(QDir::homePath()+"/.radon/collection/"+this->name+"/"));
        }

        QList<Track*> tracks = this->getTracks();
        for (int i = 0;i<tracks.count();i++)
        {
            QFile *aFile = new QFile();
            aFile->copy(QDir::homePath()+"/.radon/collection/"+this->oldname+"/"+tracks[i]->getTitle()+".mp3", QDir::homePath()+"/.radon/collection/"+this->name+"/"+tracks[i]->getTitle()+".mp3");
            aFile->remove(QDir::homePath()+"/.radon/collection/"+this->oldname+"/"+tracks[i]->getTitle()+".mp3");
            tracks[i]->setArtistId(id);
            tracks[i]->update();
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


void Artist::remove()
{
    QSqlDatabase db = dbAdapter::instance().db;
    QSqlQuery query(db);
    query.prepare("DELETE FROM artist WHERE id=:id");
    query.bindValue(":id",this->id);

    bool ok = query.exec();

    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
    }
    else
    {
        QDir artistDir = QDir();
        artistDir.remove(QString(QDir::homePath()+"/.radon/collection/"+this->name));
    }
}
