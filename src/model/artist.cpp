#include "artist.h"
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
    query.prepare("SELECT name FROM arists WHERE id=?");
    query.addBindValue(artistId);

    bool ok = query.exec();
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
    }
    if(query.next())
    {
        Artist* artist;
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
    int id = -1;
    QSqlDatabase db = dbAdapter::instance().db;
    QSqlQuery query(db);
    query.prepare("SELECT id FROM arists WHERE name=?");
    query.addBindValue(name);
    bool ok = query.exec();
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
    query.prepare("INSERT INTO arists (name) VALUES (name)");
    query.addBindValue(name);
    bool ok = query.exec();
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
    }
}

void Artist::update()
{
    QSqlDatabase db = dbAdapter::instance().db;
    QSqlQuery query(db);
    query.prepare("UPDATE arists SET name=? WHEER if=?");
    query.addBindValue(name);
    query.addBindValue(id);
    bool ok = query.exec();
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
    }
}
