#ifndef ARTIST_H
#define ARTIST_H

#include <QtCore>
#include "item.h"

class Artist : public Item
{
    Q_OBJECT
public:
    Artist(QObject *parent = 0);
    static Artist* toId(int artistId);
    static int idFromName(QString name);
    void setName(QString name) {this->name = name;}

    void insert();
    void update();

private:
    QString name;
    int id;

    static QString getHash(const QString&);
    static QHash<int, Artist*> cache;
};

#endif // ARTIST_H
