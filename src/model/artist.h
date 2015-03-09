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
    QString getName() {return name;}
    QList<Track*> getTracks();
    void insert();
    void update();

private:
    QString name;
    int id;

    static QString getHash(const QString&);
    static QHash<int, Artist*> cache;

    int trackCount();
};

typedef QPointer<Artist> ArtistPointer;
Q_DECLARE_METATYPE(ArtistPointer)

#endif // ARTIST_H
