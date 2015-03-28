#ifndef ARTIST_H
#define ARTIST_H

#include <QtCore>
#include "item.h"

class Artist : public Item
{
    Q_OBJECT
public:
    Artist(QObject *parent = 0);

public slots:
    static Artist* toId(int artistId);
    QString getName() {return this->name;}
    void remove();
    void update();
    QList<Track*> getTracks();
    void insert();
    static int idFromName(QString name);
    bool setName(QString name);

private:
    QString name;
    QString oldname;
    int id;

    static QString getHash(const QString&);
    static QHash<int, Artist*> cache;

    int trackCount();
};

typedef QPointer<Artist> ArtistPointer;
Q_DECLARE_METATYPE(ArtistPointer)

#endif // ARTIST_H
